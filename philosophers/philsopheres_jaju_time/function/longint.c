#include <stdio.h>
#include <limits.h>

int main() {
    printf("Size of long int: %zu bytes\n", sizeof(long int));
    printf("Minimum value of long int: %ld\n", LONG_MIN);
    printf("Maximum value of long int: %ld\n", LONG_MAX);

    return 0;
}