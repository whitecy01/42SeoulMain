#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	error(char *tmp)
{
	while(*tmp)
		write(2, tmp++, 1);
	return (1);
}

int	cd(char **argv, int i)
{
	if (i != 2)
		return error("error: cd: bad arguments\n");
	if (chdir(argv[1]) == -1)
		return error("error: cd: cannot change directory to "), error(argv[1]), error("\n");
	return 0;
}

int	exec(char **argv, int i, char **envp)
{
	int fd[2];
	int	status;
	int has_pipe = argv[i] && !strcmp(argv[i], "|");

	if (has_pipe && pipe(fd) == -1)
		return error("error : fatal\n");
	
	int pid = fork();

	if (!pid)
	{
		argv[i] = 0;
		if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return error("error: fatal\n");
		if (execve(*argv, argv, envp) == -1)
		    return error("error: cannot execute "), error(*argv), error("\n");
	}
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[1]) == -1 || close(fd[0]) == -1))
		 return error("error: fatal\n");
	return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **envp)
{
	int status = 0;
	int i = 0;
	if (argc > 1)
	{
		while (argv[i] && argv[++i])
		{
			argv += i;
			i = 0;
			while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			{
				i++;
			}
			if (!strcmp(argv[i], "cd"))
				status = cd(argv, i);
			else if(i)
				status = exec(argv, i, envp);
		}
	}
	return status;
}
