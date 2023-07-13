#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int         main(void)
{
    int     errno = 0;
    char    *error_message;

    printf("< errno와 에러메세지 목록 >\n");
    for (errno = 0; errno < 130; errno++)
    {
        error_message = strerror(errno);
        printf("%d. %s\n", errno, error_message);
    }
	error_message = strerror(127);
	printf("%s", error_message);
    return (0);
}