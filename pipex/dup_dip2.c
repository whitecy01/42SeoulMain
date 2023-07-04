#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

# define BUFFER_SIZE 1024
//dup
// int main()
// {
// 	int fd1, fd2;
// 	char message[32]={"message via fd2\n"};

// 	fd1 = open("made_by_fd1",O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
// 	if (fd1 < 0)
// 	{
// 		printf("fuck\n");
// 		exit(0);
// 	}
// 	fd2 = dup(fd1);
// 	write(fd2, message, strlen(message));
// 	printf("fd1 :%d, fd2:%d\n",fd1,fd2);
//     close(fd1);
//     close(fd2);
// }


//dup2
// int main()
// {
//         int fd1, ret;
//         char message[32]={"STDERR from fd1\n"};

//         //그림 1번
//         fd1=open("made_by_fd1",O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
//         if(fd1<0){
//                 printf("file open error\n");
//                 exit(0);
//         }
//         //표준 입출력으로 print됨
//         printf("file open\n");

//         //fd1의 파일 디스크립터가 명시한 STDOUT_FILENO의 파일 디스크립터로
//         //복제됨,
//         //그림 2번
//         ret=dup2(fd1,STDOUT_FILENO);

//         //fd1으로 출력됨
//         printf("fd1 :%d, ret:%d\n",fd1,ret);

//         //STDERR_FILENO 디스크립터가 명시된 fd1으로 복제됨
//         //그림 3번
//         ret=dup2(STDERR_FILENO,fd1);

//         //fd1은 에러로 출력됨
//         write(fd1,message,strlen(message));

//         //stdout이 file로 써짐
//         printf("printf를 썼지만 파일에 기록됨 \n");

//         close(fd1);
// }


int main(void)
{
    int fd1[2];
    int fd2[2];
    char buffer[BUFFER_SIZE];
    pid_t pid;

    if(pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        printf("pipe error");
        exit(1);
    }

    pid = fork();

    if (pid == -1)
    {
        printf("fork() error");
        exit(1);
    }
    if (pid == 0)
    {
		//printf("fd1[1] : %d\n", fd1[0]);
		//printf("fd1[1] : %d\n", fd1[1]);
        write(fd1[1], "(자식에서 입력)\n", 25);
		//sleep(2);
        read(fd2[0], buffer, 25);
        printf("\n자식출력: %s\n", buffer);
    }
    else
    {
       write(fd2[1], "(부모에서 입력)", 25);
        read(fd1[0], buffer, BUFFER_SIZE);
        printf("\n부모출력: %s\n", buffer);
    }
    return (0);
}