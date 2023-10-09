#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int         main(void)
{
    int     errno = 0;
    char    *error_message;

    for (errno = 0; errno < 107; errno++)
    {
        error_message = strerror(errno);
        printf("%d. %s\n", errno, error_message);
    }
    return (0);
}
