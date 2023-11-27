#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

void ft_err(const char *msg)
{
    wrtie(2, msg, strlen(msg));
    exit(1);
}

typedef struct s_client{
    int id;
    char msg[1024];
} t_client;

t_client clients[1024 * 4];
int next_fd = 0; max_fd = 0;
fd_set sockets, write_sock, read_sock;
char buffer_read[120000], buffer_write[120000];

void send_all(int not)
{
    for (int  i = 0; i <= max_fd; i++)
    {
        if (FD_ISSET(i, &write_sock) && i != not)
            send(i, buffer_write, strlen(buffer_write), 0);
    }
    
}

int main(int argc, char **argv)
{
    if (argc != 2)
        ft_err("Wrong number arguments\n");
    int sockfd;
    struct sockaddr_in servaddr, cli;
    socklen_t len;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        ft_err("Fatal error\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    servaddr.sin_port = htons(atoi(argv[1]));
//servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); : INADDR_LOOPBACK은 로컬 호스트(127.0.0.1)를 나타내는 매크로 상수입니다. 
//htonl 함수를 사용하여 호스트 바이트 순서에서 네트워크 바이트 순서로 로컬 호스트의 IP 주소를 설정합니다.
//servaddr.sin_port = htons(atoi(argv[1])); : argv[1]에 있는 포트 번호를 정수로 변환한 후 htons 함수를 사용하여 호스트 바이트 순서에서 네트워크 바이트 순서로 변환하여 sin_port에 설정합니다. 
//주로 TCP/IP 소켓 프로그래밍에서 사용하는 포트 번호를 설정할 때 사용됩니다.
    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        ft_err("Fatal error\n");
    if (listen(sockfd, 10) != 0)
        ft_err("Fatal error\n");
    len = sizeof(cli);
    max_fd = sockfd;
    FD_ZERO(&sockfd);
    FD_SET(sockfd, &sockfd);
    bzero(clients, sizeof(clients));

    

}
