#include <fstream>
#include <iostream>

int main() {
    std::ifstream inputFile("input.txt"); // input.txt 파일을 읽기 위해 엽니다

    if (inputFile.is_open()) { // 파일이 정상적으로 열렸는지 확인
        std::string line;
        while (std::getline(inputFile, line)) { // 파일에서 한 줄씩 읽어옴
            std::cout << line << std::endl; // 읽은 데이터를 화면에 출력
        }
        inputFile.close(); // 파일 닫기
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return 0;
}
