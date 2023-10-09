// #include <iostream>
// #include <cmath>

// int main() {
//     float positive_infinity = std::numeric_limits<float>::infinity(); // 양의 무한대
//     float negative_infinity = -std::numeric_limits<float>::infinity(); // 음의 무한대

//     std::cout << "양의 무한대: " << positive_infinity << std::endl;
//     std::cout << "음의 무한대: " << negative_infinity << std::endl;

//     return 0;
// }

// #include <iostream>
// #include <cmath>
// #include <math.h>

// int main() {
//     float positive_infinity = inff; // 양의 무한대를 나타내는 리터럴 상수

//     std::cout << "양의 무한대: " << positive_infinity << std::endl;

//     return 0;
// }

// #include <iostream>
// #include <cmath>

// int main() {
//     double positive_infinity_double = INFINITY; // 기본적으로 double 형식의 양의 무한대
//     float positive_infinity_float = INFINITY;   // 명시적으로 float 형식의 양의 무한대

//     std::cout << "양의 무한대 (double): " << positive_infinity_double << std::endl;
//     std::cout << "양의 무한대 (float): " << positive_infinity_float << std::endl;

//     return 0;
// }

#include <iostream>
#include <cmath>

int main() {
    double nanValue = NAN; // 부동 소수점 NaN 값을 나타내는 표준 상수

    if (std::isnan(nanValue)) {
        std::cout << "nanValue는 NaN입니다." << std::endl;
    } else {
        std::cout << "nanValue는 NaN이 아닙니다." << std::endl;
    }

    return 0;
}

