#include <stdio.h>
#include <unistd.h>

int main() {
    char *argv[] = {"ls", "-l", NULL};
    char *envp[] = {NULL};

    if (execve("/bin/ls", argv, envp) == -1) {
        perror("execve");
        return 1;
    }

    return 0;
}
