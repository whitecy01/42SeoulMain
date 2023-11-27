#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void ft_err(const char *msg)
{
    write(2, msg, strlen(msg));
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
        if (FD_ISSET(i, &write_sock) && not != i)
            send(i, buffer_write, strlen(buffer_write), 0);
    }
}

int main(int argc, char **argv)
{

}