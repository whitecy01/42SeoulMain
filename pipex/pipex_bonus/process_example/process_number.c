#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/wait.h>

int main() {
    int i;
    
    printf("부모 프로세스 %d\n", getpid());
    for (i = 0; i < 3; i++) {
        pid_t pid = fork();
        
        if (pid == 0) {
            // 자식 프로세스의 동작
            printf("자식 프로세스 %d\n", getpid());
            // 추가적인 작업을 수행할 수 있습니다.
            return 0;
        } else if (pid < 0) {
            // fork() 호출이 실패한 경우
            printf("fork() 호출이 실패하였습니다.\n");
            return 1;
        }
		else
		{
			waitpid(pid, NULL,  WNOHANG);
		}
    }

    return 0;
}
