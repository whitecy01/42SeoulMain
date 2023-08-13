
#include "get.h"
// #include <stdio.h>
// #include <sys/time.h>

// int main() {
//     struct timeval tv; // timeval 구조체 선언

//     // gettimeofday 함수로 현재 시간 정보를 얻어옴
//     if (gettimeofday(&tv, NULL) == -1) {
//         perror("gettimeofday");
//         return 1;
//     }

//     // 초와 마이크로초로 시간 정보 출력
//     printf("Seconds: %ld\n", tv.tv_sec);       // 초 (1970년 1월 1일부터의 초)
//     printf("Microseconds: %ld\n", tv.tv_usec); // 마이크로초 (1000000분의 1초)

//     return 0;
// }

#include <stdio.h>
#include <sys/time.h>

int main()
{
    struct timeval startTime, endTime;
    double diffTime;

    gettimeofday(&startTime, NULL);
      // 특정 작업 수행
      sleep(1);
    gettimeofday(&endTime, NULL);

    printf("Seconds: %ld\n", startTime.tv_sec);       // 초 (1970년 1월 1일부터의 초)
    printf("Microseconds: %ld\n", startTime.tv_usec); // 마이크로초 (1000000분의 1초)

        printf("entTime : Seconds: %ld\n", endTime.tv_sec);       // 초 (1970년 1월 1일부터의 초)
    printf("entTime : Microseconds: %ld\n", endTime.tv_usec); // 마이크로초 (1000000분의 1초)
    diffTime = ( endTime.tv_sec - startTime.tv_sec ) + (( endTime.tv_usec - startTime.tv_usec ) / 1000000);
    printf("%f s\n", diffTime);
    return 0;
}