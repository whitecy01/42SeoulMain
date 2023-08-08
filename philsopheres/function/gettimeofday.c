
#include "get.h"

// int main()
// {
//     struct timevala mytime;

//     // 현재 시간을 얻어온다.
//     gettimeofday(&mytime, NULL);
//     printf("%ld:%ld\n", mytime.tv_sec, mytime.tv_usec);

//     // 시간을 1시간 뒤로 되돌려서 설정한다.
//    // mytime.tv_sec -= 3600;
//    // settimeofday(&mytime, NULL);
//     return 0;
// }


#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct timeval mytime;

    // 현재 시간을 얻어온다.
    gettimeofday(&mytime, NULL);
    printf("%ld:%d\n", mytime.tv_sec, mytime.tv_usec);

    // 시간을 1시간 뒤로 되돌려서 설정한다.
    mytime.tv_sec -= 3600;
    settimeofday(&mytime, NULL);
    return 0;
}
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
