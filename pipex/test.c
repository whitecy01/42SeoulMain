// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char *argv[])
// {
//    if (1 < argc)  printf( "환경변수 %s는 %s\n", argv[1], getenv( argv[1]));
//    else           printf( "실행방법: show_envp [환경변수]\n");
// }

// #include <stdio.h>
// #include <unistd.h>

// int main() {
//     printf("부모 프로세스 시작\n");

//     // execv() 함수를 사용하여 "ls" 명령어를 실행
//     char *args[] = {"ls", "-l", NULL};
//     execv("/bin/ls", args);

//     // execv() 함수가 성공적으로 실행되면 아래의 코드는 실행되지 않음
//     printf("부모 프로세스 종료\n");

//     return 0;
// }


#include <stdio.h>
#include <unistd.h>

// int main() {
//     printf("부모 프로세스 시작\n");

//     // 실행할 프로그램의 경로
//     char *path = "/bin/ls";

//     // 실행할 프로그램에 전달할 명령행 인수
//     char *args[] = {"find", ".", NULL};

//     // 실행할 프로그램에 전달할 환경 변수
//     // char *envp[] = {"HOME=/home/user", "PATH=/bin:/usr/bin", NULL};
// 	char *envp[] = {"HOME=/home/user", "PATH=/bin:/usr/bin", NULL};
//     // execve() 함수를 사용하여 프로그램 실행
//     execve(path, args, envp);

//     // execve() 함수가 성공적으로 실행되면 아래의 코드는 실행되지 않음
//     printf("부모 프로세스 종료\n");

//     return 0;
// }

int main() {
    printf("부모 프로세스 시작\n");

    // 실행할 프로그램의 경로
    char *path = "/bin/echo";

    // 실행할 프로그램에 전달할 명령행 인수
    char *args[] = {"echo", "$PATH", NULL};

    // 실행할 프로그램에 전달할 환경 변수
    // char *envp[] = {"HOME=/home/user", "PATH=/bin:/usr/bin", NULL};
	char *envp[] = {"HOME=/home/user", "PATH=/bin:/usr/bin", NULL};
    // execve() 함수를 사용하여 프로그램 실행
    execve(path, args, envp);

    // execve() 함수가 성공적으로 실행되면 아래의 코드는 실행되지 않음
    printf("부모 프로세스 종료\n");

    return 0;
}