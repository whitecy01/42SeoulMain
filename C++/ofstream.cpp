#include <fstream>
#include <iostream>

int main() {
    std::ofstream outputFile("output.txt"); // output.txt 파일을 쓰기 위해 엽니다

    if (outputFile.is_open()) { // 파일이 정상적으로 열렸는지 확인
        outputFile << "Hello, World!" << std::endl; // 파일에 데이터 쓰기
        outputFile.close(); // 파일 닫기
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return 0;
}
