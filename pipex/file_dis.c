#include <unistd.h>
#include <stdio.h>
#include <limits.h>

// int main(int argc, char **argv, char **envp)
// {
// 	printf("argc : %d\n", argc);
// 	printf("argv[1] : %s\n", argv[1]);
// 	printf("argv[1] : %s\n", argv[2]);
// 	printf("argv[1] : %s\n", argv[3]);
// 	printf("argv[1] : %s\n", argv[4]);
// 	// printf("envp[1] : %s\n", envp[1]);
// 	 for (int i = 0; envp[i] != NULL; i++) {
//         printf("%s\n", envp[i]);
//     }
    

// 	// printf("first : %u\n", STDIN_FILENO);
// 	// printf("second : %u\n", STDOUT_FILENO);
// 	// printf("third : %u\n", STDERR_FILENO);
// 	// printf("first : %u\n", FOPEN_MAX);
// }


#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("인자 개수: %d\n", argc);
    
    for (int i = 0; i < argc; i++) {
        printf("인자 %d: %s\n", i, argv[i]);
    }
    
    printf("\n환경 변수:\n");
    
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    
    return 0;
}