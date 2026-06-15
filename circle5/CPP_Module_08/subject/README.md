# C++ Module 08 — 요구사항 정리

> 42Seoul Circle 5 · *Templated containers, iterators, algorithms* (Subject Version 10.0)
> 본 문서는 `CPP Module 08.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**STL 컨테이너, 이터레이터, 알고리즘**을 학습한다. Module 08·09에서 비로소 STL 사용이 허용된다.

## 2. 공통 규칙 (요약)

CPP 모듈 공통 규칙 적용 ([Module 00 README](../../../circle4/CPP_Module_00/subject/README.md) 참고). Module 02~09 모든 클래스 **Orthodox Canonical Form**.

**모듈 특화 규칙**: 이 모듈의 연습은 STL 없이도 풀 수 있지만, **STL 컨테이너(vector/list/map 등)와 알고리즘(`<algorithm>`)을 적절한 곳마다 최대한 사용하는 것이 목표**다. 사용하지 않으면 코드가 동작해도 매우 낮은 점수. 템플릿은 헤더에 정의하거나 선언만 헤더에 두고 구현은 `.tpp`에 둘 수 있음(헤더는 필수, `.tpp`는 선택).

## 3. Exercises

### ex00 — Easy find
- 파일: `Makefile`, `main.cpp`, `easyfind.{h,hpp}` (+ 선택 `easyfind.tpp`)
- 타입 T를 받는 함수 템플릿 `easyfind`: 인자 2개(T 타입, int).
- T가 **정수 컨테이너**라고 가정, 두 번째 인자의 **첫 출현**을 첫 번째 인자에서 찾음.
- 못 찾으면 예외 throw 또는 임의의 에러 값 반환(표준 컨테이너 동작 참고).
- **연관 컨테이너(associative)는 처리 불필요**. 테스트 제출.

### ex01 — Span
- 파일: `Makefile`, `main.cpp`, `Span.{h,hpp}`, `Span.cpp`
- `Span` 클래스: 최대 N개 정수 저장(N은 `unsigned int`, 생성자 인자).
  - `addNumber()`: 정수 하나 추가. 이미 N개면 예외 throw.
  - `shortestSpan()` / `longestSpan()`: 저장된 수들 간 최단/최장 거리 반환. 0개 또는 1개면 예외 throw.
- 최소 **10,000개** 이상으로 테스트.
- **이터레이터 범위로 한 번에 여러 수 추가**하는 멤버 함수 구현(컨테이너의 range 기반 멤버 함수 참고).
- 예시: Span(5)에 6,3,17,9,11 → shortest=2, longest=14.

### ex02 — Mutated abomination
- 파일: `Makefile`, `main.cpp`, `MutantStack.{h,hpp}` (+ 선택 `MutantStack.tpp`)
- `std::stack`은 STL 컨테이너 중 거의 유일하게 **iterable하지 않음** → 이를 순회 가능하게 만든다.
- `MutantStack` 클래스: **`std::stack`을 기반으로 구현**. 모든 멤버 함수 제공 + **이터레이터** 기능 추가.
- 같은 테스트를 `std::list` 등으로 바꿔 실행해도 동일 출력이 나와야 함. 테스트 제출.

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
