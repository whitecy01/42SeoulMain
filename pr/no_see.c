#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

void ft_err(const char *msg)
{
    write(2, msg, strlen(msg));
    exit(1);
}

typedef struct s_client{
    int id;
    char msg[1024];
} t_client;

t_client clients[1024 * 4];
int next_fd = 0, max_fd = 0;
fd_set sockets, write_sock, read_sock;
char buffer_write[120000], buffer_read[120000];

void send_all(int not)
{
    for (int i = 0; i <= max_fd; i++)
    {
        if (FD_ISSET(i, &write_sock) && i != not)
            send(i, buffer_write, strlen(buffer_write), 0);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        ft_err();
    int sockfd;
    struct sockaddr_in servaddr, cli;
    socklen_t len;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        ft_err();
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    servaddr.sin_port = htons(atoi(argv[1]));

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0))
        ft_err();
    if (listen(sockfd, 10) != 0)
        ft_err();
    
    len = sizeof(cli);
    max_fd = sockfd;
    FD_ZERO(&sockets);
    FD_SET(sockfd, &sockets);
    bzero(clients, sizeof(clients));

    while (1)
    {
        read_sock = write_sock = sockets;
        if (select(sockfd, &read_sock, &write_sock, NULL, NULL) < 0)
            continue;
        for (int fd = 0; fd <= max_fd; fd++)
        {
            if (FD_ISSET(fd, &read_sock) && fd == sockfd)
            {
                int connfd = accept(sockfd, (struct sockaddr *)&cli, (socklen_t *)&len);
                if (connfd < 0)
                    continue;
                clients[connfd].id = next_fd++;
                max_fd = connfd > max_fd ? connfd : max_fd;
                FD_SET(connfd, &sockets);
                sprintf(buffer_write, "");
                send_all(connfd);
                break ;
            }
            if (FD_ISSET(fd, &read_sock) && fd != sockfd)
            {
                int res = recv(fd, buffer_read, 65536, 0);
                if (res <= 0)
                {
                    sprintf();
                    send_all(fd);
                    FD_CLR(fd, &sockets);
                    close(fd);
                    break ;
                }
                else
                {
                    for (int i = 0, j = strlen(clients[fd].msg); i < res; i++, j++)
                    {
                        clients[fd].msg[j] = buffer_read[i];
                        if (clients[fd].msg[j] == '\n')
                        {
                            clients[fd].msg[j] = '\0';
                            sprintf();
                            send_all(fd);
                            bzero(&clients[fd].msg, sizeof(clients[fd].msg));
                            j = -1;
                        }
                    }
                    break ;
                }
            }
        }
        
    }
    
}