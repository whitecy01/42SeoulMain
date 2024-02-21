#include "../inc/Server.hpp"

Server::Server() {}

bool Server::password_checker(const std::string &str)
{
    if (str.empty())
    {
        return (true);
    }
    /* 공백 문자 또는 출력 가능하지 않은 문자 포함하는지 확인.*/
    for (size_t i = 0; i < str.length(); i++)
    {
        if ((std::isspace(str[i])) || !std::isprint(str[i]))
            return (true);
    }
    return (false);
}

Server::Server(int portNumber, std::string password)
{
    this->portNumber = portNumber;
    this->password = password;

    if (password_checker(this->password))
    {
        std::cout << "input password invaild" << std::endl;
        std::exit(1);
    }

    if (!(portNumber >= 0 && 65535 >= portNumber))
    {
        std::cout << "input port invaild" << std::endl;
        std::exit(1);
    }
    this->kque = kqueue(); // kque 생성
    if (this->kque == -1)
        throw std::runtime_error("kqueue error");

    Client::setServerPtr(this);
    Channel::setServerPtr(this);
}

void Server::openSocket()
{
    sockaddr_in serverAddr;

    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0); // TCP socket 생성
    if (this->serverSocket == -1)
        throw std::runtime_error("socket error");

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr =
        htonl(INADDR_ANY); // 임시로 일단은 모든 주소 받음
    serverAddr.sin_port = htons(this->portNumber);

    // port 재사용시 bind error 없애는 옵션 추가.
    int option = 1;
    setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR, &option,
               sizeof(option));

    // bind 를 통해 socket이랑 각 설정이랑 연결
    if (bind(this->serverSocket,
             reinterpret_cast<const sockaddr *>(&serverAddr),
             sizeof(serverAddr)) == -1)
        throw std::runtime_error("bind error");
    listen(this->serverSocket, LISTEN_BACKLOG_NUM); // 수신하도록 listen
                                                    // tcp 연결 완료.
}

void Server::init()
{
    struct kevent event;

    EV_SET(&event, this->serverSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
    if (kevent(this->kque, &event, 1, NULL, 0, NULL) == -1)
        throw std::runtime_error("kevent attach error");
}

Server::~Server()
{
    close(serverSocket);
    close(kque);
}

void Server::run()
{
    while (true)
    {
        struct kevent events[32];
        int triggered = kevent(this->kque, NULL, 0, events, 32, NULL);
        try
        {
            if (triggered == -1)
                throw std::runtime_error("kevent event error");
            for (int i = 0; i < triggered; i++)
            {
                if ((int)events[i].ident ==
                    this->serverSocket) // 소켓에서 이벤트 발생
                {
                    handleNewConnection(events[i].ident);
                }
                else
                { // 기존 접속
                    if (events[i].filter == EVFILT_READ)
                    {
                        handleExistingConnection(events[i].ident, events[i]);
                    }
                    else if (events[i].filter == EVFILT_WRITE)
                    {
                        // 서버가 클라이언트로 패킷을 보낼 경우
                        handleExistingConnection_send_client(events[i].ident);
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

void Server::handleNewConnection(int sockFd)
{
    struct sockaddr_in client_addr;
    struct kevent event;
    int client_addr_size = sizeof(client_addr);

    int newFd = accept(sockFd, (sockaddr *)&client_addr,
                       (socklen_t *)&client_addr_size);

    if (newFd == -1)
        throw std::runtime_error("accept error");
    fcntl(newFd, F_SETFL, O_NONBLOCK); // non-block 설정
    EV_SET(&event, newFd, EVFILT_READ, EV_ADD, NULL, 0, NULL);
    kevent(this->kque, &event, 1, NULL, 0, NULL);

    EV_SET(&event, newFd, EVFILT_WRITE, EV_ADD | EV_DISABLE, NULL, 0, NULL);
    kevent(this->kque, &event, 1, NULL, 0, NULL);

    Client client(newFd);
    client.setIpaddress(inet_ntoa(client_addr.sin_addr));
    socketFdToClient.insert(std::make_pair(newFd, client));

    std::cout << newFd << " : new connect!" << std::endl;
}
/* 서버가 클라이언트한테 소켓을 보낼 때*/
void Server::handleExistingConnection_send_client(int fd)
{
    socketFdToClient[fd].sendData();
}

#define RED "\e[0;31m"
#define NC "\e[0m"

void Server::handleExistingConnection(int sockFd, struct kevent event)
{
    if (isConnected(event) == false)
    {
        this->terminateConnection(sockFd);
        return;
    }

    std::cout << "--------" << sockFd << ": "
              << socketFdToClient[sockFd].getNickname() << "--------"
              << std::endl;

    std::vector<Message> messages = this->socketFdToClient[sockFd].readData();
    for (size_t i = 0; i < messages.size(); i++)
    {
        try
        {
            execCommand(messages[i]);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

bool Server::isConnected(struct kevent event)
{
    if (event.flags & EV_EOF)
    {
        return false;
    }
    return true;
}

void Server::terminateConnection(int fd)
{
    std::map<std::string, Channel>::iterator iterCh = this->channel.begin();
    std::string &nickname = socketFdToClient[fd].getNickname();
    std::vector<std::string> channelNamestoDelete;
    for (; iterCh != channel.end(); iterCh++)
    {
        Channel &mini_channel = iterCh->second;
        std::map<std::string, int> &members = mini_channel.getMembers();
        if (members.find(nickname) != members.end())
        {
            members.erase(members.find(nickname));
            if (mini_channel.isNoOperator())
                channelNamestoDelete.push_back(iterCh->first);
        }
    }
    for (size_t i = 0; i < channelNamestoDelete.size(); i++)
    {
        this->channel[channelNamestoDelete[i]].partAll();
        this->channel.erase(channelNamestoDelete[i]);
    }

    // socket, kqueue 관련 연결 끊음
    struct kevent temp_event;
    EV_SET(&temp_event, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    kevent(kque, &temp_event, 1, NULL, 0, NULL);
    close(fd);
    std::cout << fd << " : close!" << std::endl;

    // server Client 관련 데이터 제거
    this->socketFdToClient.erase(fd);
    this->nicknameToSocketFd.erase(nickname);
}

void Server::execCommand(Message message)
{
    Command &command = Command::getInstance(*this);
    Client &client = socketFdToClient[message.getSocket()];

    if (message.getCommand() == "PASS")
        command.pass(message);
    else if (client.getIsAuthenticated() == false)
        terminateConnection(message.getSocket());
    else if (message.getCommand() == "NICK")
        command.nick(message);
    else if (client.getNickname() == "")
    {
        std::cout<<"No Nick!"<<std::endl;
        return ;
    }
    else if (message.getCommand() == "USER")
        command.user(message);
    else if (client.getUsername() == "" || client.getIpaddress() == "")
    {
        std::cout<<"No User!"<<std::endl;
        return ;
    }
    else if (message.getCommand() == "PRIVMSG")
        command.privmsg(message);
    else if (message.getCommand() == "PING")
        command.ping(message);
    else if (message.getCommand() == "JOIN")
        command.join(message);
    else if (message.getCommand() == "PART")
        command.part(message);
    else if (message.getCommand() == "KICK")
        command.kick(message);
    else if (message.getCommand() == "TOPIC")
        command.topic(message);
    else if (message.getCommand() == "INVITE")
        command.invite(message);
    else if (message.getCommand() == "MODE")
        command.mode(message);
    else if (message.getCommand() == "QUIT")
        command.quit(message);
}

int Server::getKque() const { return kque; }

Client &Server::getClientByNickname(const std::string &nickname)
{
    std::map<std::string, int>::iterator iter =
        nicknameToSocketFd.find(nickname);

    return socketFdToClient[iter->second];
}

std::map<std::string, int> &Server::getNicknameToSocketFd()
{
    return nicknameToSocketFd;
}

std::map<int, Client> &Server::getSocketFdToClient()
{
    return socketFdToClient;
}

std::map<std::string, Channel> &Server::getChannel() { return channel; }

std::string &Server::getPassWord() { return password; }