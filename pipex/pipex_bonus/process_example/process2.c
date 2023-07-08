// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main() {
//     int i;
//     for (i = 0; i < 3; i++) {
//         pid_t pid = fork(); // 자식 프로세스 생성

//         if (pid < 0) {
//             // fork()가 실패한 경우
//             fprintf(stderr, "자식 프로세스 생성 실패\n");
//             return 1;
//         } else if (pid == 0) {
//             // 자식 프로세스인 경우
//             printf("자식 프로세스 %d\n", getpid());
//             // 자식 프로세스에서 수행할 작업 추가
//             exit(0);
//         } else {
//             // 부모 프로세스인 경우
//             printf("부모 프로세스 %d에서 자식 프로세스 %d 생성\n", getpid(), pid);
//         }
//     }

//     // 부모 프로세스에서 수행할 작업 추가
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    for (i = 0; i < 3; i++) {
        pid_t pid = fork(); // 자식 프로세스 생성

        if (pid < 0) {
            // fork()가 실패한 경우
            fprintf(stderr, "자식 프로세스 생성 실패\n");
            return 1;
        } else if (pid == 0) {
            // 자식 프로세스인 경우
            char *args[] = { "ls", "-l", NULL }; // 실행할 프로그램과 인자 배열
            char *envp[] = { NULL }; // 환경 변수 배열 (필요에 따라 설정 가능)
            execve("/bin/ls", args, envp); // 자식 프로세스를 다른 프로그램으로 대체
            fprintf(stderr, "execve 실행 실패\n"); // execve() 함수가 실패한 경우에만 실행
            return 1;
        } else {
            // 부모 프로세스인 경우
            printf("부모 프로세스 %d에서 자식 프로세스 %d 생성\n", getpid(), pid);
        }
    }

    // 부모 프로세스에서 수행할 작업 추가
    return 0;
}
