

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


void error(char *error)
{
    int i;

    i = 0;
    while (error[i])
    {
        write(1, &error[i], 1);
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_info loc;

    //infile open
    loc.infile = open(argv[1], O_RDONLY);
	if (loc.infile == -1)
		error("infile error");
	loc.outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (loc.outfile == -1)
		error("outfile error");
}