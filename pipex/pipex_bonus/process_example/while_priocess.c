
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/wait.h>

int main()
{
    pid_t pid;

    int time = 0;
    while(time < 2)
    {
		if (pid != 0 && time != 1)
       		pid = fork();

        if (pid == 0)
        {
            printf("자식 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송\n", getpid(), pid);
            //printf("자식 프로세스에서 %d P\n", getpid());
            printf("자식 프로세스 입니다\n");
        }
        else
        { 
            printf("부모 프로세스 %d에서 자식 프로세스 %d로 파일 목록 전송\n", getpid(), pid);
            //printf("자식 프로세스 PID:%d\n", getpid());
            printf("부모 프로세스 입니다\n");
        }
		time++;
    }

}
