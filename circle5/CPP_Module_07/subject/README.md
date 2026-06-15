# C++ Module 07 — 요구사항 정리

> 42Seoul Circle 5 · *C++ templates* (Subject Version 10.0)
> 본 문서는 `CPP Module 07.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

C++의 **템플릿(templates)** 을 학습한다. 함수 템플릿과 클래스 템플릿으로 타입에 독립적인 제네릭 코드를 작성한다.

## 2. 공통 규칙 (요약)

CPP 모듈 공통 규칙 적용 ([Module 00 README](../../../circle4/CPP_Module_00/subject/README.md) 참고). Module 02~09 모든 클래스 **Orthodox Canonical Form**. **템플릿은 헤더 파일(.hpp/.tpp)에 정의**(함수 템플릿 구현을 헤더에 두는 것은 예외적으로 허용).

## 3. Exercises

### ex00 — Start with a few functions
- 파일: `Makefile`, `main.cpp`, `whatever.{h,hpp}`
- 함수 템플릿 구현:
  - `swap`: 두 인자 값 교환, 반환 없음.
  - `min`: 더 작은 값 반환, **같으면 두 번째** 반환.
  - `max`: 더 큰 값 반환, **같으면 두 번째** 반환.
- 어떤 타입이든 호출 가능. 두 인자는 같은 타입이어야 하고 모든 비교 연산자를 지원해야 함.
- **템플릿은 헤더에 정의**. (예시 main: int, std::string으로 동작 확인)

### ex01 — Iter
- 파일: `Makefile`, `main.cpp`, `iter.{h,hpp}`
- 함수 템플릿 `iter`: 3개 인자, 반환 없음.
  - 1번: 배열의 주소.
  - 2번: 배열 길이(**const value**).
  - 3번: 각 원소에 호출할 함수.
- 어떤 타입의 배열에서도 동작. 3번 인자는 인스턴스화된 함수 템플릿일 수 있음. 함수는 context에 따라 const/non-const 참조로 인자를 받을 수 있음 → **const/non-const 원소 모두 지원** 고려.
- 테스트용 `main.cpp` 제출.

### ex02 — Array
- 파일: `Makefile`, `main.cpp`, `Array.{h,hpp}` (+ 선택 `Array.tpp`)
- 타입 T 원소를 담는 클래스 템플릿 `Array`:
  - 인자 없는 생성: 빈 배열.
  - `unsigned int n` 생성: n개 원소를 **기본값으로 초기화**(힌트: `new int()`).
  - 복사 생성자 + 대입 연산자: 복사 후 원본/사본 한쪽 수정이 다른 쪽에 영향 없어야 함(깊은 복사).
  - 메모리 할당은 **반드시 `new[]`** 사용. 사전 할당(preventive allocation) 금지, 미할당 메모리 접근 금지.
  - 첨자 연산자 `[]`로 원소 접근. 인덱스 범위 밖이면 **`std::exception`** throw.
  - `size()` 멤버 함수: 원소 개수 반환, 인자 없음, 인스턴스 수정 안 함(const).
- 테스트용 `main.cpp` 제출.

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
