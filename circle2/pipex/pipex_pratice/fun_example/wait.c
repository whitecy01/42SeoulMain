// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int main() {
//     printf("시작\n");
//     pid_t pid = fork();

//     if (pid == 0) {
//         // 자식 프로세스
//         printf("자식 프로세스 시작\n");
//         printf("자식 프로세스 ID: %d\n", getpid());
//         printf("부모 프로세스 ID: %d\n", getppid());
//         printf("자식 프로세스 종료\n");
//         return 0;
//     } else {
//         // 부모 프로세스
//         printf("부모 프로세스 시작\n");
//         printf("부모 프로세스 ID: %d\n", getpid());
//         printf("부모 프로세스 대기 중...\n");

//         int child_status;
//         wait(&child_status);

//         printf("부모 프로세스: 자식 프로세스 종료\n");
//         printf("부모 프로세스 ID: %d\n", getpid());
//         printf("부모 프로세스 종료\n");
//     }

//     printf("종료\n");

//     return 0;
// }

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("시작\n");
    pid_t pid = fork();

    if (pid == 0) {
        // 자식 프로세스
        printf("자식 프로세스 시작\n");
        printf("자식 프로세스 ID: %d\n", getpid());
        printf("부모 프로세스 ID: %d\n", getppid());
        printf("자식 프로세스 종료\n");
        return 42;
    } else {
        // 부모 프로세스
        printf("부모 프로세스 시작\n");
        printf("부모 프로세스 ID: %d\n", getpid());
        printf("부모 프로세스 대기 중...\n");

        int child_status;
        pid_t terminated_pid = wait(&child_status);

        if (terminated_pid == -1) {
            printf("자식 프로세스 대기 실패\n");
        } else {
            if (WIFEXITED(child_status)) {
                printf("자식 프로세스 정상 종료\n");
                printf("자식 프로세스 종료 상태: %d\n", WEXITSTATUS(child_status));
            } else if (WIFSIGNALED(child_status)) {
                printf("자식 프로세스 시그널에 의해 종료\n");
                printf("자식 프로세스 종료 시그널: %d\n", WTERMSIG(child_status));
            }
        }

        printf("부모 프로세스 ID: %d\n", getpid());
        printf("부모 프로세스 종료\n");
    }

    printf("종료\n");

    return 0;
}
