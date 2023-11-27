#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

void ft_err(const char *msg){
    write(2, msg, strlen(msg));
    exit(1);
}

typedef struct s_client {
    int id;
    char msg[1024];
} t_client;

t_client clients[1024 * 4];
//  해당 선언인 t_client clients[1024 * 4];는 실제로 4개의 클라이언트만을 저장할 수 있는 것이 아니라, 1024 * 4 (4096) 개의 t_client 구조체를 갖는 배열을 선언합니다.
// 이 배열은 4096개의 t_client 구조체를 저장할 수 있는 공간을 할당합니다. 각 t_client 구조체는 하나의 클라이언트 정보를 나타냅니다. 이 배열을 통해 여러 클라이언트의 정보를 저장하고 관리할 수 있습니다.
// 따라서 해당 배열은 최대 4096개의 클라이언트 정보를 저장할 수 있습니다. 이는 클라이언트가 4개만 가능한 것이 아니라, 그보다 훨씬 많은 클라이언트 정보를 저장할 수 있다는 것을 의미합니다.
int next_id = 0, max_fd = 0;
fd_set sockets, write_sock, read_sock;
// fd_set은 파일 디스크립터를 관리하기 위한 데이터 구조입니다.
// sockets: 클라이언트 소켓의 파일 디스크립터를 저장하는 fd_set 구조체 변수입니다.
// write_sock: 쓰기 가능한 소켓의 파일 디스크립터를 저장하는 fd_set 구조체 변수입니다.
// read_sock: 읽을 수 있는 소켓의 파일 디스크립터를 저장하는 fd_set 구조체 변수입니다.
char buffer_read[120000], buffer_write[120000];

void send_all(int not)
{
    for (int i = 0; i <= max_fd; i++)
        if (FD_ISSET(i, &write_sock) && i != not)
            send(i, buffer_write, strlen(buffer_write), 0);
    
// FD_ISSET은 파일 디스크립터의 상태를 확인하기 위한 매크로 함수입니다. 이 매크로 함수는 주어진 파일 디스크립터가 특정한 소켓 세트에서 설정되었는지 여부를 확인하는 데 사용됩니다.
// 일반적으로 네트워크 프로그래밍에서 select() 함수와 함께 사용됩니다. select() 함수는 여러 소켓의 I/O 상태를 모니터링하고, 읽기 또는 쓰기 작업이 가능한지를 확인하는 데 사용됩니다. 이때 FD_ISSET은 select() 함수에 전달된 소켓 세트의 상태를 확인하는 데에 사용됩니다.
//FD_ISSET 함수는 주어진 파일 디스크립터의 상태를 확인하며, 해당 파일 디스크립터가 주어진 소켓 세트 안에 있고 설정되어 있는지를 확인합니다.
}

int main(int argc, char **argv) 
{
     if (ac != 2)
        ft_err("Wrong number arguments\n");
    int sockfd;
    struct sockaddr_in servaddr, cli; // 소켓 프로그래밍에서 네트워크 주소 정보를 저장하기 위한 구조체입니다. 주로 IPv4 주소 체계를 사용하는 네트워크 프로그래밍에서 사용됩니다.
    socklen_t len; //  소켓 관련 함수들에서 사용되는 데이터 타입으로, 일반적으로 size_t와 동일하거나 비슷한 의미를 갖습니다. 이 데이터 타입은 주로 주소 구조체의 크기를 저장하는 데에 쓰이며, 네트워크 함수들이 주로 주소 구조체의 크기를 인자로 필요로 하기 때문에 중요한 역할을 합니다.
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // IPv4 주소 지정 및 TCP 프로토콜을 사용하여 소켓 만들기, Create a socket with IPv4 addressing and TCP protocol
// AF_INET: 주소 체계(Address Family)를 나타내며, IPv4 주소 체계를 사용하겠다는 것을 의미합니다.
// SOCK_STREAM: 소켓 유형을 나타내며, 여기서는 TCP 소켓을 사용하기 위해 SOCK_STREAM을 사용했습니다. TCP는 연결 지향 프로토콜이므로, 데이터를 신뢰성 있게 전송하고 연결을 유지하기 위해 SOCK_STREAM을 선택했습니다.
// 0: 프로토콜을 나타냅니다. 주로 0을 사용하여 시스템이 기본 프로토콜을 선택하도록 합니다. SOCK_STREAM을 사용하는 경우 일반적으로 TCP 프로토콜을 의미하므로 보통 0을 사용합니다.
    if (sockfd == -1)
        ft_err("Fatal error\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;        // 주소 계열을 IPv4로 설정 Set address family to IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // IP 주소를 localhost로 설정 Set the IP address to localhost
    servaddr.sin_port = htons(atoi(argv[1]));  // 명령줄 인수에서 포트 번호 설정 Set the port number from the command line argument

    // 서버 소켓을 지정된 주소에 바인딩 Bind the server socket to the specified address
    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        ft_err("Fatal error\n");
//bind(): 소켓에 IP 주소와 포트 번호를 할당하는 함수입니다. 이 함수는 생성한 소켓에 특정 주소 정보를 연결하여 해당 주소와 포트에서 들어오는 패킷을 받을 수 있도록 설정합니다.
//sockfd: 소켓 디스크립터로, socket() 함수로 생성된 소켓을 나타냅니다.
// (const struct sockaddr *)&servaddr: struct sockaddr 형식의 주소 정보를 포함하는 변수 servaddr를 소켓에 바인딩합니다. struct sockaddr는 여러 종류의 네트워크 주소를 담을 수 있는 범용적인 구조체입니다. servaddr은 이전에 정의된 struct sockaddr_in 구조체인데, IPv4 주소와 포트 정보를 저장하는 구조체입니다. 이를 (const struct sockaddr *)로 형변환하여 bind() 함수에 전달합니다.
// sizeof(servaddr): servaddr 구조체의 크기를 나타냅니다. 이를 통해 함수는 주어진 주소 정보의 크기를 알 수 있습니다.
// bind() 함수는 소켓에 주소를 할당하는데, 주로 서버 소켓의 경우 포트 번호와 IP 주소를 바인딩하여 클라이언트로부터 오는 연결 요청을 받아들일 준비를 합니다. 함수가 정상적으로 수행되면 0을 반환하고, 실패하면 -1을 반환합니다. 위 코드는 bind() 함수가 0이 아닌 값을 반환할 경우, 즉 바인딩이 실패한 경우에 if 문을 통해 처리하는 것으로 보입니다. 실패 시 일반적으로 오류 처리 루틴이 수행될 수 있습니다.

    // Listen for incoming connections
    if (listen(sockfd, 10) != 0)
        ft_err("Fatal error\n");
// listen(): 소켓이 연결을 받아들일 수 있도록 설정하는 함수입니다. 이 함수는 TCP 서버 소켓에서만 사용됩니다.
// 첫 번째 인자 sockfd: 연결을 기다리는 소켓의 파일 디스크립터입니다. 이 소켓은 socket() 함수로 생성된 소켓이어야 합니다.
// 두 번째 인자 10: 연결 대기 큐의 최대 길이를 지정합니다. 연결 요청이 도착했을 때 대기열에 유지되는 최대 연결 요청 수를 나타냅니다. 이 값은 시스템에 따라 다르지만 보통 10으로 지정됩니다.
// listen() 함수는 소켓을 '수동'으로 만들어 연결을 수신할 수 있도록 하며, 연결 대기열을 생성하여 클라이언트의 연결 요청을 받아들일 수 있도록 준비합니다. 이후 accept() 함수를 사용하여 실제로 클라이언트의 연결을 수락할 수 있게 됩니다.
    
    len = sizeof(cli);
    max_fd = sockfd;
    FD_ZERO(&sockets);
    FD_SET(sockfd, &sockets);
    bzero(clients, sizeof(clients));
    while (1) 
    {
        read_sock = write_sock = sockets; // 소켓 모니터링을 위해 select를 위한 소켓 세트를 초기화합니다.
        if (select(max_fd + 1, &read_sock, &write_sock, NULL, NULL) < 0) // select 함수를 이용하여 I/O 이벤트를 감지합니다.
            continue ; // select 함수에서 에러가 발생하면 다시 반복합니다.
        for (int fd = 0; fd <= max_fd; fd++) 
        { // 모든 소켓에 대해 루프를 수행합니다.
            if (FD_ISSET(fd, &read_sock) && fd == sockfd) // 새로운 클라이언트의 연결을 처리합니다.
            { 
                int connfd = accept(sockfd, (struct sockaddr *)&cli, (socklen_t *)&len); // 클라이언트의 연결을 수락합니다.
                if (connfd < 0)
                    continue ; // 클라이언트의 연결 수락에 실패하면 다시 반복합니다.
                
                clients[connfd].id = next_id++; // 클라이언트의 ID를 저장합니다.
                max_fd = connfd > max_fd ? connfd : max_fd; // 최대 소켓 번호를 갱신합니다.
                FD_SET(connfd, &sockets); // 소켓 세트에 클라이언트 소켓을 추가합니다.
                sprintf(buffer_write, "server: client %d just arrived\n", clients[connfd].id); // 클라이언트가 도착했음을 알리는 메시지를 작성합니다.
                send_all(connfd); // 모든 클라이언트에게 메시지를 전송합니다.
                break; // 반복문을 종료합니다.
            }
            if (FD_ISSET(fd, &read_sock) && fd != sockfd) // 클라이언트로부터의 메시지를 처리합니다.
            { 
                int res = recv(fd, buffer_read, 65536, 0); // 클라이언트로부터 데이터를 수신합니다.
                if (res <= 0) // 클라이언트가 연결을 끊었을 때의 처리입니다.
                { 
                    sprintf(buffer_write, "server: client %d just left\n", clients[fd].id); // 클라이언트가 나갔음을 알리는 메시지를 작성합니다.
                    send_all(fd); // 모든 클라이언트에게 메시지를 전송합니다.
                    FD_CLR(fd, &sockets); // 소켓 세트에서 클라이언트 소켓을 제거합니다.
                    close(fd); // 클라이언트 소켓을 닫습니다.
                    break; // 반복문을 종료합니다.
                } 
                else // 클라이언트로부터 메시지를 받은 경우의 처리입니다.
                { 
                    for (int i = 0, j = strlen(clients[fd].msg); i < res; i++, j++) // 받은 메시지를 클라이언트의 메시지에 추가합니다.
                    { 
                        clients[fd].msg[j] = buffer_read[i];
                        if (clients[fd].msg[j] == '\n') // 메시지가 완료되었을 때의 처리입니다.
                        { 
                            clients[fd].msg[j] = '\0';
                            sprintf(buffer_write, "client %d: %s\n", clients[fd].id, clients[fd].msg); // 클라이언트의 메시지를 서버에 출력합니다.
                            send_all(fd); // 모든 클라이언트에게 메시지를 전송합니다.
                            bzero(&clients[fd].msg, sizeof(clients[fd].msg)); // 클라이언트의 메시지를 초기화합니다.
                            j = -1; // 반복문에서 j가 0으로 되도록 설정합니다.
                        }
                    }
                    break; // 반복문을 종료합니다.
                }
            }
        }
    }
    return 0;


    // while (1)
    // {
    //     read_sock = write_sock = sockets;
    //     if (select(max_fd + 1, &read_sock, &write_sock, NULL, NULL) < 0)
    //         continue ;
    //     for (int fd = 0; fd <= max_fd; fd++)
    //     {
    //         if (FD_ISSET(fd, &read_sock) && fd == sockfd)
    //         {
    //             int connfd = accept(sockfd, (struct sockaddr *)&cli, (socklen_t *)&len);
    //             if (connfd < 0)
    //                 continue ;
    //             clients[connfd].id = next_id++;
    //             max_fd = connfd > max_fd ? connfd : max_fd;
    //             FD_SET(connfd, &sockets);
    //             sprintf(buffer_write, "server: client %d just arrived\n", clients[connfd].id);
    //             send_all(connfd);
    //             break;
    //         }
    //         if(FD_ISSET(fd, &read_sock) && fd != sockfd)
    //         {
    //             int res = recv(fd, buffer_read, 65536, 0);
    //             if(res <= 0)
    //             {
    //                 sprintf(buffer_write, "server: client %d just left\n", clients[fd].id);
    //                 send_all(fd);
    //                 FD_CLR(fd, &sockets);
    //                 close(fd);
    //                 break;
    //             }
    //             else
    //             {
    //                 for(int i = 0, j = strlen(clients[fd].msg); i < res; i++, j++)
    //                 {
    //                     clients[fd].msg[j] = buffer_read[i];
    //                     if(clients[fd].msg[j] == '\n')
    //                     {
    //                         clients[fd].msg[j] = '\0';
    //                         sprintf(buffer_write, "client %d: %s\n", clients[fd].id, clients[fd].msg);
    //                         send_all(fd);
    //                         bzero(&clients[fd].msg, sizeof(clients[fd].msg));
    //                         j = -1;
    //                     }
    //                 }
    //                 break;
    //             }
    //         }
    //     }
    // }
    // return 0;

    // int clientSockets[MAX_CLIENTS];           // 클라이언트 소켓 설명자를 저장하는 배열
    // int next_id = 0;                          // 다음 클라이언트 연결을 위한 식별자

    // // File descriptor sets
    // fd_set activeSockets, readySockets;        // 소켓 활동을 추적하기 위한 파일 설명자 세트(File descriptor sets for tracking socket activity)
    // char buffer[BUFFER_SIZE];                  // 수신된 메시지를 저장하기 위한 버퍼 Buffer for storing received messages

    // // Create the server socket
    // int serverSocket = socket(AF_INET, SOCK_STREAM, 0);  // IPv4 주소 지정 및 TCP 프로토콜을 사용하여 소켓 만들기, Create a socket with IPv4 addressing and TCP protocol
    // if (serverSocket < 0)  // Check if socket creation failed
    // {                    
    //     perror("Error creating server socket"); // Print an error message with a description of the error
    //     exit(1);                              // Terminate the program with a non-zero status code
    // }

    // // Set up the server address
    // struct sockaddr_in serverAddress = {0};    // 서버 주소를 보유하는 구조 Structure to hold the server address
    // serverAddress.sin_family = AF_INET;        // 주소 계열을 IPv4로 설정 Set address family to IPv4
    // serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // IP 주소를 localhost로 설정 Set the IP address to localhost
    // serverAddress.sin_port = htons(atoi(argv[1]));  // 명령줄 인수에서 포트 번호 설정 Set the port number from the command line argument


    // // Initialise the active sockets set
    // FD_ZERO(&activeSockets);                   // 활성 소켓 세트 지우기 , Clear the set of active sockets
    // FD_SET(serverSocket, &activeSockets);      // 세트에 서버 소켓 추가 Add the server socket to the set
    // int maxSocket = serverSocket;              // 최대 소켓 설명자를 추적하는 변수 Variable to track the maximum socket descriptor

    // while (1) 
    // {
    //     // Wait for activity on the sockets
    //     readySockets = activeSockets;           // select()와 함께 사용할 활성 소켓 세트를 복사합니다. Copy the active sockets set for use with select()
    //     if (select(maxSocket + 1, &readySockets, NULL, NULL, NULL) < 0) 
    //     {
    //         perror("Error in select");         // Print an error message if select() fails
    //         exit(1);                          // Terminate the program with a non-zero status code
    //     }

    //     // Check each socket for activity
    //     for (int socketId = 0; socketId <= maxSocket; socketId++) 
    //     {
    //         if (FD_ISSET(socketId, &readySockets)) 
    //         {
    //             // New client connection
    //             if (socketId == serverSocket)  // 활동이 서버 소켓에 있는지 확인하십시오. Check if the activity is on the server socket
    //             {
    //                 int clientSocket = accept(serverSocket, NULL, NULL);  // Accept a new client connection
    //                 if (clientSocket < 0) 
    //                 {
    //                     perror("Error accepting client connection");  // Print an error message if accepting fails
    //                     exit(1);                          // Terminate the program with a non-zero status code
    //                 }

    //                 // 활성 세트에 새 클라이언트 소켓 추가 Add the new client socket to the active set
    //                 FD_SET(clientSocket, &activeSockets);     //활성 소켓 세트에 클라이언트 소켓 추가  Add the client socket to the set of active sockets
    //                 maxSocket = (clientSocket > maxSocket) ? clientSocket : maxSocket;  //최대 소켓 설명자 업데이트  Update the maximum socket descriptor

    //                 // Send a welcome message to the client
    //                 sprintf(buffer, "server: client %d just arrived\n", next_id);  // 환영 메시지를 준비하세요 Prepare the welcome message
    //                 send(clientSocket, buffer, strlen(buffer), 0);  // 고객에게 환영 메시지 보내기 Send the welcome message to the client

    //                 // 나중에 참조할 수 있도록 클라이언트 소켓을 저장합니다. Store the client socket for future reference
    //                 clientSockets[next_id++] = clientSocket;  //배열에 클라이언트 소켓 추가  Add the client socket to the array
    //             } 
    //             else 
    //             {
    //                 //클라이언트로부터 받은 데이터 Data received from a client
    //                 int bytesRead = recv(socketId, buffer, sizeof(buffer) - 1, 0);  //클라이언트로부터 데이터 수신 Receive data from the client

    //                 if (bytesRead <= 0) 
    //                 {
    //                     // Client disconnected
    //                     sprintf(buffer, "server: client %d just left\n", socketId);  //연결 끊김 메시지 준비 Prepare the disconnection message

    //                     //연결이 끊긴 클라이언트에 대해 나머지 클라이언트에게 알립니다. Notify remaining clients about the disconnected client
    //                     for (int i = 0; i < next_id; i++) 
    //                     {
    //                         if (clientSockets[i] != socketId) 
    //                         {
    //                             send(clientSockets[i], buffer, strlen(buffer), 0); //다른 클라이언트에게 연결 해제 메시지 보내기 Send the disconnection message to other clients
    //                         }
    //                     }

    //                     //소켓을 닫고 활성 세트에서 제거합니다. Close the socket and remove it from the active set
    //                     close(socketId);                          // Close the client socket
    //                     FD_CLR(socketId, &activeSockets);         // Remove the client socket from the set of active sockets
    //                 } 
    //                 else 
    //                 {
    //                     //수신된 메시지를 다른 모든 클라이언트에게 브로드캐스트 Broadcast the received message to all other clients
    //                     buffer[bytesRead] = '\0';                  // Null-terminate the received message
    //                     sprintf(buffer, "client %d: %s\n", socketId, buffer);  //메시지에 클라이언트 식별자 추가 Add client identifier to the message

    //                     for (int i = 0; i < next_id; i++) 
    //                     {
    //                         if (clientSockets[i] != socketId) 
    //                         {
    //                             send(clientSockets[i], buffer, strlen(buffer), 0);  //다른 클라이언트에게 메시지 보내기 Send the message to other clients
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // return 0;
}