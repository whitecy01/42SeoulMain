# C++ Module 02 — 요구사항 정리

> 42Seoul Circle 4 · *Ad-hoc polymorphism, operator overloading and the Orthodox Canonical class form* (Subject Version 9.0)
> 본 문서는 `CPP Module 02.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**임시 다형성(ad-hoc polymorphism)**, **연산자 오버로딩**, **정준 형식(Orthodox Canonical Form)** 을 학습한다. 고정소수점(fixed-point) 숫자 클래스를 단계적으로 구축.

## 2. 공통 규칙 & New Rules

CPP 모듈 공통 규칙 적용 ([Module 00 README](../../CPP_Module_00/subject/README.md) 참고).

**New rules — Orthodox Canonical Form (이번 모듈부터 모든 클래스에 필수)**:
- **기본 생성자(Default constructor)**
- **복사 생성자(Copy constructor)**
- **복사 대입 연산자(Copy assignment operator)**
- **소멸자(Destructor)**

클래스는 헤더(.hpp, 정의)와 소스(.cpp, 구현)로 분리.

## 3. Exercises (모두 `Fixed` 클래스 단계적 확장)

### ex00 — My First Class in Orthodox Canonical Form
- 파일: `Makefile`, `main.cpp`, `Fixed.{h,hpp}`, `Fixed.cpp`
- 고정소수점 숫자 `Fixed` 클래스를 OCF로 구현.
  - private: 값 저장용 `int`, 소수부 비트 수용 `static const int`(항상 **8**).
  - public: 기본 생성자(값 0 초기화), 복사 생성자, 복사 대입 연산자, 소멸자, `int getRawBits() const`, `void setRawBits(int const raw)`.
- 각 생성자/소멸자 호출 시 메시지 출력(예시 출력 참고).

### ex01 — Towards a more useful fixed-point number class
- 파일: 동일 / 허용: `roundf` (`<cmath>`)
- 추가:
  - `int`를 받는 생성자(고정소수점으로 변환), `float`를 받는 생성자(변환). 소수부 비트=8.
  - `float toFloat() const`, `int toInt() const`.
  - 삽입 연산자 `<<` 오버로드(부동소수점 표현을 출력 스트림에 삽입).

### ex02 — Now we're talking
- 파일: 동일 / 허용: `roundf`
- 연산자 오버로딩 추가:
  - 비교 6개: `>`, `<`, `>=`, `<=`, `==`, `!=`.
  - 산술 4개: `+`, `-`, `*`, `/`.
  - 증감 4개: 전위/후위 `++`, `--` (최소 표현 가능 ε 단위).
- static 멤버 함수 4개: `min`/`max` 각각 (참조 버전, const 참조 버전) — 더 작은/큰 쪽 참조 반환.
- 0으로 나누면 크래시 허용.

### ex03 — BSP (Binary Space Partitioning)
- 파일: `Makefile`, `main.cpp`, `Fixed.{h,hpp}`, `Fixed.cpp`, `Point.{h,hpp}`, `Point.cpp`, `bsp.cpp` / 허용: `roundf`
- `Point` 클래스(OCF, 2D 점): private `Fixed const x`, `Fixed const y`. 기본 생성자(x,y=0), float 2개 받는 생성자, 복사 생성자/대입/소멸자.
- `bool bsp(Point const a, Point const b, Point const c, Point const point)`: 점이 삼각형 **내부**면 true, 아니면 false(꼭짓점/변 위면 false).
- (이 연습 없이도 모듈 통과 가능)

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
