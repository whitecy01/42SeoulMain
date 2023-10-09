#include <stdio.h>
#include <unistd.h>

int main() {
    printf("부모 프로세스 시작\n");

    // execl() 함수를 사용하여 "/bin/ls" 명령어 실행
    execl("/bin/ls", "ls", "-l", NULL);

    // execl() 함수가 성공적으로 실행되면 아래의 코드는 실행되지 않음
    printf("부모 프로세스 종료\n");

    return 0;
}