# C++ Module 06 — 요구사항 정리

> 42Seoul Circle 5 · *C++ casts* (Subject Version 8.0)
> 본 문서는 `CPP Module 06.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

C++의 **캐스팅(casts)** 을 학습한다. 스칼라 타입 변환, 직렬화(serialization), 런타임 타입 식별을 다룬다.

## 2. 공통 규칙 (요약)

CPP 모듈 공통 규칙 적용 ([Module 00 README](../../../circle4/CPP_Module_00/subject/README.md) 참고). Module 02~09 모든 클래스 **Orthodox Canonical Form**(명시 예외 제외).

**추가 규칙(모듈 전체 필수)**: 각 연습의 타입 변환은 **적절한 종류의 캐스트**(static_cast / reinterpret_cast / dynamic_cast / const_cast)로 처리해야 함. 선택 이유는 디펜스에서 검토됨.

## 3. Exercises

### ex00 — Conversion of scalar types
- 파일: `Makefile`, `*.cpp`, `*.{h,hpp}` / 허용: string→int/float/double 변환 함수
- `ScalarConverter` 클래스: **static 메서드 `convert(std::string)` 하나만**. 인스턴스화 불가(저장할 것 없음).
- 입력 리터럴의 타입을 먼저 감지 → 실제 타입으로 변환 → 나머지 세 타입으로 **명시적 변환** → 출력:
  - `char`, `int`, `float`, `double` 순으로.
- char 외에는 10진 표기만. 표시 불가능한 char로 변환되면 안내 메시지(`Non displayable`).
- **의사 리터럴(pseudo-literal) 처리**: float은 `-inff`, `+inff`, `nanf`; double은 `-inf`, `+inf`, `nan`.
- 변환이 무의미하거나 오버플로우면 `impossible` 안내. numeric limits/특수값 헤더 사용 가능.
- 출력 예: `./convert 42.0f` → `char: '*'` / `int: 42` / `float: 42.0f` / `double: 42.0`.

### ex01 — Serialization
- 파일: `Makefile`, `*.cpp`, `*.{h,hpp}`
- `Serializer` 클래스: 사용자 초기화 불가, static 메서드:
  - `uintptr_t serialize(Data* ptr)`: 포인터 → `uintptr_t`.
  - `Data* deserialize(uintptr_t raw)`: `uintptr_t` → `Data*`.
- 멤버를 가진 **비어 있지 않은 `Data` 구조체** 생성(파일 제출 필수). serialize → deserialize 후 원본 포인터와 같은지 확인하는 테스트.

### ex02 — Identify real type
- 파일: `Makefile`, `*.cpp`, `*.{h,hpp}` / 금지: `std::typeinfo` (`typeinfo` 헤더 include 금지)
- `Base`: **public virtual 소멸자만** 보유. `A`, `B`, `C`는 빈 클래스로 Base를 public 상속. (이 4개 클래스는 OCF 불필요)
- 함수:
  - `Base* generate(void)`: A/B/C 중 무작위 생성, `Base*`로 반환.
  - `void identify(Base* p)`: 실제 타입 `"A"`/`"B"`/`"C"` 출력.
  - `void identify(Base& p)`: 실제 타입 출력. **내부에서 포인터 사용 금지**.

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
