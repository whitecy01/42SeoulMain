#include <stdio.h>
#include <unistd.h>

int main() {
    char *filename = "example.txt";
    
    if (access(filename, F_OK) == 0) {
        printf("File exists\n");
    } else {
        printf("File does not exist\n");
    }
    
    return 0;
}