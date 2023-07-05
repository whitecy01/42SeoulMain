#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int old_fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("Old file descriptor: %d\n", old_fd);

    // dup() 함수를 사용하여 새로운 파일 디스크립터 생성
    int new_fd = dup(old_fd);
    printf("New file descriptor (dup): %d\n", new_fd);

    // 파일에 데이터를 쓰기
    char data[] = "Hello, World!";
    write(new_fd, data, sizeof(data) - 1);

    close(old_fd);
    close(new_fd);

    return 0;
}
