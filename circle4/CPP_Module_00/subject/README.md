# C++ Module 00 — 요구사항 정리

> 42Seoul Circle 4 · *Namespaces, classes, member functions, stdio streams, initialization lists, static, const* (Subject Version 11.0)
> 본 문서는 `CPP Module 00.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**객체지향 프로그래밍(OOP)** 입문. C에서 파생된 **C++**를 **C++98 표준**으로 학습한다. 네임스페이스, 클래스, 멤버 함수, stdio 스트림, 초기화 리스트, static, const 등 기초.

## 2. C++ 모듈 공통 일반 규칙 (General Rules)

> 이 규칙은 CPP Module 00~09 전체에 공통 적용된다.

**컴파일**
- `c++` + `-Wall -Wextra -Werror`로 컴파일, `-std=c++98`을 추가해도 컴파일되어야 함.

**형식/명명 규칙**
- 연습 디렉터리: `ex00`, `ex01`, ... `exN`.
- 클래스명은 **UpperCamelCase**, 파일명은 클래스명과 일치(`ClassName.hpp/.cpp/.tpp`).
- 별도 명시가 없으면 모든 출력 메시지는 **개행으로 끝나고 표준 출력**으로.
- **Norminette 없음** — 코딩 스타일 강제 없으나 가독성 있게.

**허용/금지**
- 표준 라이브러리는 거의 다 사용 가능 (C 함수 대신 C++식 사용 권장).
- **외부 라이브러리 금지** (C++11 이상, Boost 금지). `*printf()`, `*alloc()`, `free()` 사용 시 **0점**.
- 명시되지 않으면 `using namespace`, `friend` 키워드 금지 → 위반 시 **-42점**.
- **STL은 Module 08, 09에서만** 허용 (Container, `<algorithm>` 등) → 위반 시 **-42점**.

**설계 요구**
- `new`로 할당한 메모리 누수 금지.
- **Module 02~09는 Orthodox Canonical Form** 필수(명시 예외 제외).
- 헤더 파일에 함수 구현(함수 템플릿 제외) 시 해당 연습 **0점**.
- 헤더는 독립적으로 사용 가능해야 하고 **include guard** 필수 → 없으면 **0점**.

## 3. Exercises

### ex00 — Megaphone
- 파일: `Makefile`, `megaphone.cpp`
- 인자로 받은 문자열을 **전부 대문자로** 출력. 인자가 없으면 `* LOUD AND UNBEARABLE FEEDBACK NOISE *` 출력. C++스럽게 풀 것.

### ex01 — My Awesome PhoneBook
- 파일: `Makefile`, `*.cpp`, `*.{h,hpp}`
- 두 클래스 구현:
  - **PhoneBook**: 연락처 배열 보유, 최대 **8개** 저장(9번째 추가 시 가장 오래된 것 교체). **동적 할당 금지**.
  - **Contact**: 연락처 1건.
- 명령은 `ADD`, `SEARCH`, `EXIT`만 허용(그 외 무시).
  - **ADD**: 필드(first name, last name, nickname, phone number, darkest secret) 입력. 빈 필드 불가.
  - **SEARCH**: 4열(index, first name, last name, nickname) 목록 출력. 각 열 **10자 폭**, `|` 구분, 우측 정렬, 넘치면 잘라서 마지막 표시 문자를 `.`로. 이후 인덱스 입력받아 상세 출력. 잘못된 인덱스는 적절히 처리.
  - **EXIT**: 종료(연락처 소멸).

### ex02 — The Job Of Your Dreams
- 파일: `Makefile`, `Account.cpp`, `Account.hpp`, `tests.cpp`
- 인트라넷에서 제공되는 `Account.hpp`, `tests.cpp`, 로그 파일을 바탕으로 **삭제된 `Account.cpp`를 복원**. 출력이 로그 파일과 일치해야 함(타임스탬프 제외).
- 소멸자 호출 순서는 컴파일러/OS에 따라 다를 수 있음. **이 연습은 모듈 통과 필수 아님.**

## 4. 제출 및 평가

- Git 저장소에 제출, 파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
