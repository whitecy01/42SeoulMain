# C++ Module 01 — 요구사항 정리

> 42Seoul Circle 4 · *Memory allocation, pointers to members, references and switch statements* (Subject Version 11.0)
> 본 문서는 `CPP Module 01.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

C++의 **메모리 할당(new/delete)**, **멤버 함수 포인터**, **참조(reference)**, **switch 문**을 학습한다.

## 2. 공통 규칙 (요약)

CPP 모듈 공통 규칙 적용 (자세한 내용은 [Module 00 README](../../CPP_Module_00/subject/README.md) 참고):
- `c++` + `-Wall -Wextra -Werror`, `-std=c++98` 호환.
- 클래스명 UpperCamelCase, 파일명 일치. include guard 필수.
- `using namespace`/`friend` 금지(-42), STL은 Module 08·09에서만(-42), `printf`/`alloc`/`free` 금지(0점).
- 메모리 누수 금지. 헤더에 함수 구현(템플릿 제외) 시 0점.

## 3. Exercises

### ex00 — BraiiiiiiinnnzzzZ
- 파일: `Makefile`, `main.cpp`, `Zombie.{h,hpp}`, `Zombie.cpp`, `newZombie.cpp`, `randomChump.cpp`
- `Zombie` 클래스(private `name`)와 `announce()` 멤버 함수(`<name>: BraiiiiiiinnnzzzZ...` 출력).
- `Zombie* newZombie(std::string name)`: 좀비 생성·명명 후 반환(함수 밖에서 사용).
- `void randomChump(std::string name)`: 좀비 생성·명명 후 스스로 announce.
- **stack vs heap 할당**을 어느 경우에 쓸지 판단. 소멸자는 디버깅용으로 이름 출력.

### ex01 — Moar brainz!
- 파일: `Makefile`, `main.cpp`, `Zombie.{h,hpp}`, `Zombie.cpp`, `zombieHorde.cpp`
- `Zombie* zombieHorde(int N, std::string name)`: **단일 할당으로 N개** 좀비 생성·초기화 후 첫 좀비 포인터 반환. `delete`로 해제, 메모리 누수 확인.

### ex02 — HI THIS IS BRAIN
- 파일: `Makefile`, `main.cpp`
- `"HI THIS IS BRAIN"` 문자열, `stringPTR`(포인터), `stringREF`(참조)를 만들고 세 가지의 **주소**와 **값**을 각각 출력. 참조(reference) 개념 이해가 목적.

### ex03 — Unnecessary violence
- 파일: `Makefile`, `main.cpp`, `Weapon.{h,hpp}`, `Weapon.cpp`, `HumanA.{h,hpp}`, `HumanA.cpp`, `HumanB.{h,hpp}`, `HumanB.cpp`
- `Weapon`: private `type`(string), `getType()`(const 참조 반환), `setType()`.
- `HumanA`/`HumanB`: Weapon과 name 보유, `attack()` → `<name> attacks with their <weapon type>`.
  - HumanA는 생성자에서 Weapon을 받고 **항상 무장**. HumanB는 생성자에서 안 받고 **무기가 없을 수도** 있음.
- 포인터 참조 vs 참조(reference)를 언제 쓸지 고민. 메모리 누수 확인.

### ex04 — Sed is for losers
- 파일: `Makefile`, `main.cpp`, `*.cpp`, `*.{h,hpp}` / 금지: `std::string::replace`
- 인자: filename, s1, s2. `<filename>`을 열어 내용을 `<filename>.replace`로 복사하며 **s1을 s2로 모두 치환**.
- **C 파일 함수 사용 금지**(부정행위). `std::string`의 멤버 함수는 `replace` 제외 허용. 에러 처리 + 본인 테스트 제출.

### ex05 — Harl 2.0
- 파일: `Makefile`, `main.cpp`, `Harl.{h,hpp}`, `Harl.cpp`
- `Harl` 클래스: private `debug()`, `info()`, `warning()`, `error()` + public `complain(std::string level)`.
- **멤버 함수 포인터** 사용 필수 — if/else if 더미 없이 레벨에 따라 호출.

### ex06 — Harl filter
- 파일: `Makefile`, `main.cpp`, `Harl.{h,hpp}`, `Harl.cpp` / 실행파일명 `harlFilter`
- 인자로 받은 레벨 **이상**의 모든 메시지 출력. **switch 문** 사용 필수. (이 연습 없이도 모듈 통과 가능)

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
