// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>

// void child_process() {
//     printf("자식 프로세스 시작\n");
//     printf("자식 프로세스 ID: %d\n", getpid());
//     printf("부모 프로세스 ID: %d\n", getppid());
//     printf("자식 프로세스 종료\n");
// }

// void parent_process() {
//     printf("부모 프로세스 시작\n");
//     printf("부모 프로세스 ID: %d\n", getpid());
//     printf("부모 프로세스 종료\n");
// }

// int main() {
//     printf("시작\n");
//     pid_t pid = fork();

// 	//printf("pid : %d\n", pid);
//     if (pid == 0) {
//         // 자식 프로세스
//         child_process();
//     } else {
//         // 부모 프로세스
// 		//printf("pid : %d\n", pid);
//         parent_process();
//     }

//     printf("종료\n");

//     return 0;
// }

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // 자식 프로세스
        printf("자식 프로세스 실행\n");
        printf("자식 프로세스 ID: %d\n", getpid());
	    printf("자식 프로세스 ID: %d\n", pid);
    } else if (pid > 0) {
        // 부모 프로세스
        printf("부모 프로세스 실행\n");
        printf("부모 프로세스 ID: %d\n", getpid());
        printf("자식 프로세스 ID: %d\n", pid);
    } else {
        // fork() 실패
        printf("fork() 함수 호출 실패\n");
        return 1;
    }

    return 0;
}
