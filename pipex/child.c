
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/stat.h>
// #include <string.h>
// #include <fcntl.h>

// int main()
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid > 0)
// 	{
// 		printf("부모\n");
// 	}
// 	else
// 		printf("자식\n");
// }


// #include <stdio.h>
// #include <unistd.h>
// #include <sys/types.h>

// int main() {
    
//     pid_t pid;
    
//     int x;
//     x = 0;
    
//     pid = fork();
    
//     // if(pid > 0) {  // 부모 코드
//     //     x = 1;
//     //     printf("부모 PID : %ld,  x : %d , pid : %d\n",(long)getpid(), x, pid);
//     // }
//     // else if(pid == 0){  // 자식 코드
//     //     x = 2;
//     //     printf("자식 PID : %ld,  x : %d\n",(long)getpid(), x);
//     // }
// 	if(pid == 0){  // 자식 코드
//         x = 2;
//         printf("자식 PID : %ld,  x : %d\n",(long)getpid(), x);
//     }
// 	else if(pid > 0) {  // 부모 코드
//         x = 1;
//         printf("부모 PID : %ld,  x : %d , pid : %d\n",(long)getpid(), x, pid);
//     }
//     else {  // fork 실패
//         printf("fork Fail! \n");
//         return -1;
//     }
    
//     return 0;

// }

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// int main() {
//     int pipefd[2];
//     //char message[] = "Hello, child process!";
//     char buffer[100];

//     // 파이프 생성
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         return 1;
//     }

//     // 자식 프로세스 생성
//     pid_t pid = fork();
//     if (pid == -1) {
//         perror("fork");
//         return 1;
//     }

//     if (pid == 0) {
//         // 자식 프로세스는 파이프의 읽기 단을 닫음
//         close(pipefd[0]);

//         // 파이프의 쓰기 단에 메시지를 씀
//         //write(pipefd[1], message, strlen(message) + 1);

//         // 자식 프로세스 종료
//         return 0;
//     } else {
//         // 부모 프로세스는 파이프의 쓰기 단을 닫음
//         close(pipefd[1]);

//         // 파이프의 읽기 단에서 데이터를 읽음
//         read(pipefd[0], buffer, sizeof(buffer));

//         printf("Received message in parent: %s\n", buffer);

//         // 부모 프로세스 종료
//         return 0;
//     }

// }

// #include <stdio.h>
// #include <unistd.h>

// int main() {
//     pid_t pid = fork();

//     if (pid > 0) {
//         // 부모 프로세스
//         printf("부모 프로세스입니다. 자식 프로세스 ID: %d\n", pid);
//     } else if (pid == 0) {
//         // 자식 프로세스
//         printf("자식 프로세스입니다.\n");
//     } else {
//         // fork() 호출 실패
//         printf("fork() 함수 호출에 실패하였습니다.\n");
//         return 1;
//     }

//     // 부모 프로세스와 자식 프로세스에서 공통으로 실행되는 코드
//     printf("Hello, world!\n");

//     return 0;
// }


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Standard output\n");  // 기존의 표준 출력

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    printf("Redirected output\n");  // 파일로 재지정된 출력

    close(fd);
    return 0;
}