# ft_printf — 요구사항 정리

> 42Seoul Circle 1 · *Because ft_putnbr() and ft_putstr() aren't enough* (Subject Version 12.0)
> 본 문서는 `ft_printf.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

C 표준 함수 `printf()`를 직접 재구현하는 프로젝트. **가변 인자(variadic functions)** 사용법을 학습한다. 핵심은 **확장 가능하고 잘 구조화된 코드**.

| 항목 | 내용 |
|------|------|
| Program Name | `libftprintf.a` |
| 제출 파일 | `Makefile`, `*.h`, `*/*.h`, `*.c`, `*/*.c` |
| Makefile 규칙 | `NAME`, `all`, `clean`, `fclean`, `re` |
| 허용 외부 함수 | `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end` |
| libft 사용 | 허용 |
| 헤더 | `ft_printf.h` (프로토타입 포함) |

## 2. 공통 규칙

- 언어 C, **Norm** 준수(보너스 포함). 비정상 종료/메모리 누수 시 0점.
- Makefile은 `cc` + `-Wall -Wextra -Werror`, 불필요한 relinking 금지.
- 라이브러리는 **`ar`** 로 생성(`libtool` 금지). `libftprintf.a`는 루트에 생성.
- libft를 쓰면 소스와 Makefile을 `libft` 폴더에 복사하고, 프로젝트 Makefile이 먼저 라이브러리를 빌드.

## 3. Mandatory — `ft_printf`

```c
int ft_printf(const char *, ...);
```

- 원본 `printf()`의 **버퍼 관리는 구현하지 않는다.**
- 결과는 원본 `printf()`와 비교 평가된다(반환값=출력한 문자 수).
- 다음 변환(conversion)을 처리해야 함: `cspdiuxX%`

| 변환 | 의미 |
|------|------|
| `%c` | 단일 문자 |
| `%s` | 문자열 (C 관례) |
| `%p` | `void *` 포인터를 16진수로 출력 |
| `%d` | 10진수 정수 |
| `%i` | 10진수 정수 |
| `%u` | 부호 없는 10진수 |
| `%x` | 16진수 소문자 |
| `%X` | 16진수 대문자 |
| `%%` | 퍼센트 기호 |

## 4. Bonus

> 보너스는 mandatory가 **완벽**할 때만 평가. mandatory에 에러가 하나라도 있으면 보너스는 전혀 평가되지 않음. 보너스를 할 거면 처음부터 설계에 반영할 것.

- 모든 변환에 대해 플래그 조합 `-`, `0`, `.`(precision)과 **최소 필드 폭(width)** 처리.
- 플래그 `#`, `+`, ` `(공백) 처리.

## 5. README 요구사항 (과제 자체 요구)

루트에 `README.md` 필수. 최소 포함:
- 첫 줄(이탤릭): `This project has been created as part of the 42 curriculum by <login>`
- **Description / Instructions / Resources**(+AI 사용 내역) 섹션
- **선택한 알고리즘과 자료구조에 대한 상세 설명 및 근거**

## 6. 제출 및 평가

- Git 저장소에 제출, 파일명 정확히 확인. 통과 후 `ft_printf()`를 libft에 추가해 재사용 가능.
- 평가 중 간단한 코드 수정 요청 가능(이해도 검증용).
