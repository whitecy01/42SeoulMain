#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int old_fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("Old file descriptor: %d\n", old_fd);

    // dup2() 함수를 사용하여 표준 출력을 파일 디스크립터로 변경
    int stdout_fd = dup(STDOUT_FILENO);
	 printf("stdout_fd: %d\n", stdout_fd);
    dup2(old_fd, STDOUT_FILENO);
    printf("This will be written to the file.\n");

    // 표준 출력을 원래의 파일 디스크립터로 복구
    dup2(stdout_fd, STDOUT_FILENO);
    printf("This will be displayed on the terminal.\n");

    close(old_fd);
    close(stdout_fd);

    return 0;
}