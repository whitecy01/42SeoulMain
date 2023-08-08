#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		puts("자식 프로세스");
		sleep(5);
		//exit(0);
	}
	else
	{
		while(waitpid(pid, NULL, WNOHANG) == 0)
		{
			puts("부모 프로세스 ");
			sleep(1);
		}
	
	}
}

//자식 프로세스가 살아있을 동안 waitpid를 걸어주면 그게 그만큼 실행된다.