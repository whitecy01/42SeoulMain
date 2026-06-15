# C++ Module 04 — 요구사항 정리

> 42Seoul Circle 4 · *Subtype Polymorphism, Abstract Classes, and Interfaces* (Subject Version 12.0)
> 본 문서는 `CPP Module 04.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**서브타입 다형성(subtype polymorphism)**, **추상 클래스(abstract class)**, **인터페이스(interface, 순수 가상 클래스)** 를 학습한다. `virtual` 함수가 핵심.

## 2. 공통 규칙 (요약)

CPP 모듈 공통 규칙 적용 ([Module 00 README](../../CPP_Module_00/subject/README.md) 참고). 모든 클래스 **Orthodox Canonical Form**. 각 클래스의 생성자/소멸자는 **서로 다른 고유 메시지** 출력. 모든 연습에서 충실한 테스트 제출.

## 3. Exercises

### ex00 — Polymorphism
- 파일: `Makefile`, `main.cpp`, `*.cpp`, `*.{h,hpp}`
- 기반 클래스 `Animal`(protected `std::string type`). `Dog`, `Cat`이 `Animal` 상속, 각각 type을 "Dog"/"Cat"으로 초기화.
- 모든 동물은 `makeSound()` 사용 가능(적절한 소리 출력 — 고양이는 안 짖음). `makeSound()`는 **virtual**이어야 다형성 동작(`Animal*`로 Dog/Cat의 소리 출력).
- `WrongAnimal`/`WrongCat`: virtual을 안 쓰면 WrongCat이 WrongAnimal 소리를 내는 것을 구현해 차이를 이해.

### ex01 — I don't want to set the world on fire
- 파일: 이전 파일 + `*.cpp`, `*.{h,hpp}`
- `Brain` 클래스: `std::string ideas[100]` 배열 보유. `Dog`/`Cat`은 private `Brain*` 속성 — 생성 시 `new Brain()`, 소멸 시 `delete`.
- main에서 `Animal*` 배열 생성(절반 Dog, 절반 Cat), 마지막에 순회하며 `Animal`로 delete(올바른 소멸자 순서 호출).
- **깊은 복사(deep copy)** 필수(얕은 복사 금지), 메모리 누수 확인.

### ex02 — Abstract class
- 파일: 이전 파일 + `*.cpp`, `*.{h,hpp}`
- `Animal` 클래스를 **인스턴스화 불가능(추상 클래스)** 으로 수정(`makeSound()`를 순수 가상으로). 나머지는 이전과 동일하게 동작. (원하면 클래스명에 `A` 접두사 추가 가능)

### ex03 — Interface & recap
- 파일: `Makefile`, `main.cpp`, `*.cpp`, `*.{h,hpp}` (이 연습 없이도 모듈 통과 가능)
- **AMateria** (추상): `getType()`, `virtual AMateria* clone() const = 0`, `virtual void use(ICharacter& target)`.
  - 구체 클래스 `Ice`("ice"), `Cure`("cure"). `clone()`은 같은 타입의 새 인스턴스 반환.
  - `use(ICharacter&)`: Ice → `* shoots an ice bolt at <name> *`, Cure → `* heals <name>'s wounds *`.
- **ICharacter** 인터페이스 구현 → 구체 클래스 `Character`:
  - 슬롯 **4개** 인벤토리(생성 시 비어 있음). 빈 슬롯 0→3 순으로 장착. 가득 찬 인벤토리/없는 Materia에 use·unequip은 아무 일 없음(버그는 금지). `unequip()`은 Materia를 **삭제하지 않음**(주소 보관, 누수 방지).
  - **깊은 복사**: 복사 시 기존 Materia 삭제 후 새로 추가. 소멸 시 Materia 삭제.
- **IMateriaSource** 인터페이스 구현 → 구체 클래스 `MateriaSource`:
  - `learnMateria(AMateria*)`: Materia를 복사 저장(최대 4개, 중복 허용).
  - `createMateria(std::string const&)`: 학습한 타입의 복사본 반환, 모르는 타입이면 0 반환.

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
