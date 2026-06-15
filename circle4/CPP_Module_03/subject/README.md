# C++ Module 03 — 요구사항 정리

> 42Seoul Circle 4 · *Inheritance* (Subject Version 8.0)
> 본 문서는 `CPP Module 03.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**상속(Inheritance)** 을 학습한다. ClapTrap 로봇을 기반으로 단일 상속과 다이아몬드 상속(diamond problem)을 다룬다.

## 2. 공통 규칙 (요약)

CPP 모듈 공통 규칙 적용 ([Module 00 README](../../CPP_Module_00/subject/README.md) 참고). 모든 클래스는 **Orthodox Canonical Form**.

## 3. Exercises (ClapTrap 계열 누적)

### ex00 — Aaaaand... OPEN!
- 파일: `Makefile`, `main.cpp`, `ClapTrap.{h,hpp}`, `ClapTrap.cpp`
- `ClapTrap` 클래스, private 속성: `Name`(생성자 인자), `Hit points`(10), `Energy points`(10), `Attack damage`(0).
- public 멤버 함수:
  - `void attack(const std::string& target);`
  - `void takeDamage(unsigned int amount);`
  - `void beRepaired(unsigned int amount);`
- 공격 시 대상이 `<attack damage>`만큼 HP 감소, 수리 시 `<amount>` HP 회복. 공격·수리 각각 **에너지 1 소모**. HP나 에너지가 0이면 아무 동작 불가.
- 모든 멤버 함수·생성자·소멸자가 동작 설명 메시지 출력. (인스턴스 간 직접 상호작용 없음)

### ex01 — Serena, my love!
- 파일: 이전 파일 + `ScavTrap.{h,hpp}`, `ScavTrap.cpp`
- `ScavTrap`: ClapTrap **상속**. 생성자/소멸자/`attack()`은 다른 메시지 출력. **생성/소멸 체이닝**(ScavTrap 생성 시 ClapTrap 먼저 생성, 소멸은 역순)을 테스트로 보여야 함.
- 속성: HP(100), Energy(50), Attack damage(20). 고유 능력 `void guardGate();` (Gate keeper 모드 메시지).

### ex02 — Repetitive work
- 파일: 이전 파일 + `FragTrap.{h,hpp}`, `FragTrap.cpp`
- `FragTrap`: ClapTrap 상속. 생성/소멸 메시지 다름, 체이닝 동일.
- 속성: HP(100), Energy(100), Attack damage(30). 고유 능력 `void highFivesGuys(void);` (하이파이브 요청 출력).

### ex03 — Now it's weird!
- 파일: 이전 파일 + `DiamondTrap.{h,hpp}`, `DiamondTrap.cpp`
- `DiamondTrap`: **FragTrap과 ScavTrap을 모두 상속**(다중 상속).
  - private `name` 속성(ClapTrap의 변수명과 정확히 동일한 이름 사용).
  - `ClapTrap::name` = 생성자 인자 + `"_clap_name"` 접미사.
  - HP=FragTrap, Energy=ScavTrap, Attack damage=FragTrap, `attack()`=ScavTrap.
  - 고유 능력 `void whoAmI();` (자신의 name과 ClapTrap name 둘 다 출력).
- **ClapTrap 인스턴스는 단 한 번만 생성**(가상 상속 트릭). `-Wshadow`/`-Wno-shadow` 플래그 참고. (이 연습 없이도 모듈 통과 가능)

## 4. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
