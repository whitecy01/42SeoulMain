# C++ Module 05 — 요구사항 정리

> 42Seoul Circle 5 · *Repetition and Exceptions* (Subject Version 11.0)
> 본 문서는 `CPP Module 05.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**반복(repetition)** 과 **예외(exceptions)** 를 학습한다. 관료제(bureaucracy)를 테마로 try/catch 예외 처리, 추상 클래스, 다형성을 종합한다.

## 2. 공통 규칙 (요약)

CPP 모듈 공통 규칙 적용 ([Module 00 README](../../../circle4/CPP_Module_00/subject/README.md) 참고). Module 02~09 모든 클래스 **Orthodox Canonical Form**(단, **예외 클래스는 OCF 불필요**, 그 외 모든 클래스는 필수).

## 3. Exercises

### ex00 — Mommy, when I grow up, I want to be a bureaucrat!
- 파일: `Makefile`, `main.cpp`, `Bureaucrat.{h,hpp}`, `Bureaucrat.cpp`
- `Bureaucrat`: **const name**, **grade**(1=최고 ~ 150=최저).
- 범위 밖 grade로 생성 시 예외: `Bureaucrat::GradeTooHighException` 또는 `GradeTooLowException`.
- getter `getName()`, `getGrade()`. grade 증가/감소 멤버 함수 2개(범위 벗어나면 동일 예외). **grade 3 증가 → grade 2**(숫자 작을수록 높음).
- 예외는 try/catch (`std::exception&`)로 잡을 수 있어야 함.
- `<<` 연산자 오버로드: `<name>, bureaucrat grade <grade>.` 출력. 테스트 제출.

### ex01 — Form up, maggots!
- 파일: 이전 + `Form.{h,hpp}`, `Form.cpp`
- `Form`: const name, signed 여부(bool, 초기값 false), **서명에 필요한 const grade**, **실행에 필요한 const grade**. 모든 속성 **private**.
- grade 규칙은 Bureaucrat와 동일 → `Form::GradeTooHighException`/`GradeTooLowException`.
- getter + `<<` 오버로드(모든 정보 출력).
- `beSigned(Bureaucrat)`: 관료 grade가 충분(≥ 요구치)하면 signed 처리, 아니면 `GradeTooLowException`.
- `Bureaucrat::signForm()`: `beSigned()` 호출. 성공 시 `<bureaucrat> signed <form>`, 실패 시 `<bureaucrat> couldn't sign <form> because <reason>.`.

### ex02 — No, you need form 28B, not 28C...
- 파일: `Makefile`, `main.cpp`, `Bureaucrat.*`, `AForm.*`, `ShrubberyCreationForm.*`, `RobotomyRequestForm.*`, `PresidentialPardonForm.*`
- 기반 `Form`을 **추상 클래스로 만들어 `AForm`으로 이름 변경**. 속성은 여전히 private, 기반 클래스 소유.
- 구체 클래스(생성자 인자: target 하나):
  - **ShrubberyCreationForm**(sign 145, exec 137): `<target>_shrubbery` 파일 생성 후 ASCII 나무 작성.
  - **RobotomyRequestForm**(sign 72, exec 45): 드릴 소리 후 50% 확률로 `<target> robotomized successfully`, 아니면 실패 메시지.
  - **PresidentialPardonForm**(sign 25, exec 5): `<target>`이 Zaphod Beeblebrox에게 사면됨 출력.
- 기반에 `execute(Bureaucrat const& executor) const` 추가, 구체 클래스에서 동작 구현. **서명 여부 + 실행 grade** 확인 후 부족하면 예외(검사를 기반/구체 어디서 할지는 자유, 더 우아한 방법 권장).
- `Bureaucrat::executeForm(AForm const& form) const`: 실행 시도, 성공 시 `<bureaucrat> executed <form>`, 실패 시 명시적 에러.

### ex03 — At least this beats coffee-making
- 파일: 이전 + `Intern.{h,hpp}`, `Intern.cpp`
- `Intern`: 이름·grade·고유 특성 없음.
- `makeForm(std::string formName, std::string target)`: 이름에 해당하는 `AForm*` 반환(target 초기화). `Intern creates <form>` 출력, 없는 이름이면 명시적 에러.
- **과도한 if/elseif/else 금지**(평가에서 거부).

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
