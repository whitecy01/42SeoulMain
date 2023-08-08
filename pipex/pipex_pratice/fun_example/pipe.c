
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define BUFSIZE 100

// int main()
// {
// 	int fd[2];
// 	char buffer[BUFSIZE];
// 	pid_t pid;
// 	int state;

// 	state = pipe(fd);
// 	if (state == -1)
// 	{
// 		puts("fuck");
// 		exit(1);
// 	}
// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		puts("err");
// 		exit( 1);
// 	}
// 	else if(pid == 0)
// 	{
// 		write(fd[1], "연결성공!!", 25);

// 	}
// 	else
// 	{
// 		read(fd[0], buffer, BUFSIZE);
// 		puts(buffer);
// 	}
// }


// int main()
// {
// 	int fd[2];
// 	char buffer[BUFSIZE];
// 	pid_t pid;
// 	int state;

// 	state = pipe(fd);
// 	if (state == -1)
// 	{
// 		puts("fuck");
// 		exit(1);
// 	}
// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		puts("err");
// 		exit( 1);
// 	}
// 	else if(pid == 0)
// 	{
// 		read(fd[0], buffer, BUFSIZE);
// 		puts(buffer);

// 	}
// 	else
// 	{
// 		write(fd[1], "연결성공!!", 25);
	
// 	}
// }

//파이프 1개 예제
int main()
{
	int fd[2];
	char buffer[BUFSIZE];
	pid_t pid;
	int state;

	state = pipe(fd);
	if (state == -1)
	{
		puts("error");
		exit(1);
	}
	pid = fork();

	if (pid == -1)
	{
		puts("err");
		exit( 1);
	}
	else if(pid == 0)
	{
		write(fd[1], "연결성공!!", 25);
		sleep(2);
		read(fd[0], buffer, BUFSIZE);
		printf("Output of child process : %s \n", buffer);

	}
	else
	{
		read(fd[0], buffer, BUFSIZE);
		printf("Output of parent process : %s \n", buffer);
		write(fd[1], "정말 좋아!", 25);
		sleep(2);
		
	}
}


//pipe 2개
// int main()
// {
// 	int fd1[2], fd2[2];
// 	char buffer[BUFSIZE];
// 	pid_t pid;

// 	if (pipe(fd1) == -1 || pipe (fd2) == -1)
// 	{
// 		puts("error");
// 		exit(1);
// 	}
// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		puts("err");
// 		exit( 1);
// 	}
// 	else if(pid == 0)
// 	{
// 		write(fd1[1], "연결성공!!", 25);
// 		read(fd2[0], buffer, BUFSIZE);
// 		printf("Output of child process : %s \n", buffer);

// 	}
// 	else
// 	{
// 		read(fd1[0], buffer, BUFSIZE);
// 		printf("Output of parent process : %s \n", buffer);
// 		write(fd2[1], "정말 좋아!", 25);
// 		sleep(1);
// 	}
// }

