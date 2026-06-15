# Libft — 요구사항 정리

> 42Seoul Circle 0 · *Your very first own library* (Subject Version 19.0)
> 본 문서는 `Libft.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

C 표준 라이브러리(libc)의 주요 함수들과 자주 쓰이는 유틸리티 함수를 직접 구현하여, 정적 라이브러리 **`libft.a`** 로 묶는 프로젝트. 이후 모든 C 과제에서 재사용한다.

| 항목 | 내용 |
|------|------|
| Program Name | `libft.a` |
| 제출 파일 | `Makefile`, `libft.h`, `ft_*.c` |
| Makefile 규칙 | `NAME`, `all`, `clean`, `fclean`, `re` (+보너스 시 `bonus`) |
| 허용 외부 함수 | 함수별로 명시 (`malloc`, `free`, `write` 등) |
| libft 사용 | 해당 없음 (이게 libft 자체) |

## 2. 공통 규칙 (Common Instructions)

- 언어는 **C**, **Norm**(42 코딩 규칙) 준수. 보너스 파일도 Norm 검사 대상이며 위반 시 0점.
- segfault, bus error, double free 등으로 비정상 종료 금지(정의되지 않은 동작 제외) → 위반 시 0점.
- 힙 할당 메모리는 반드시 해제. **메모리 누수 불허**.
- Makefile은 `cc`와 `-Wall -Wextra -Werror` 플래그 사용, **불필요한 relinking 금지**.
- 보너스는 Makefile에 `bonus` 규칙으로 분리. 평가는 mandatory와 bonus를 **별도로** 진행.

## 3. 기술적 제약 (Technical Considerations)

- **전역 변수 선언 금지.**
- 복잡한 함수를 쪼갤 때 helper 함수는 `static`으로 선언해 파일 스코프로 제한.
- 모든 파일은 저장소 **루트**에 위치. 사용하지 않는 파일 제출 금지.
- 모든 `.c`는 `-Wall -Wextra -Werror`로 컴파일되어야 함.
- 라이브러리 생성은 반드시 **`ar`** 명령 사용. **`libtool` 사용 금지.**
- `libft.a`는 저장소 루트에 생성.
- `restrict` 키워드(C99)는 프로토타입에 포함 금지, `-std=c99`로 컴파일 금지.

## 4. Part 1 — Libc 함수 재구현

원본과 동일한 프로토타입·동작(man page 기준)으로 구현하되, 이름 앞에 `ft_` 접두사를 붙인다 (`strlen` → `ft_strlen`). 외부 함수에 의존 금지.

**문자 분류 함수**(`isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint`)는 반환값이 매치 시 `1`, 불일치 시 `0`.

| 분류 | 함수 |
|------|------|
| 문자 분류/변환 | `isalpha` `isdigit` `isalnum` `isascii` `isprint` `toupper` `tolower` |
| 문자열 | `strlen` `strlcpy` `strlcat` `strchr` `strrchr` `strncmp` `strnstr` |
| 메모리 | `memset` `bzero` `memcpy` `memmove` `memchr` `memcmp` |
| 변환 | `atoi` |
| malloc 사용 | `calloc` `strdup` |

> `calloc`: `nmemb` 또는 `size`가 0이면 `free()`로 해제 가능한 고유 포인터를 반환해야 함.

## 5. Part 2 — 추가 함수

libc에 없거나 형태가 다른 함수들. Part 1의 함수를 활용 가능. 할당 실패 시 모두 `NULL` 반환.

| 함수 | 프로토타입 | 설명 |
|------|-----------|------|
| `ft_substr` | `char *ft_substr(char const *s, unsigned int start, size_t len)` | `s`의 `start`부터 최대 `len` 길이의 부분 문자열 |
| `ft_strjoin` | `char *ft_strjoin(char const *s1, char const *s2)` | `s1`+`s2` 연결 |
| `ft_strtrim` | `char *ft_strtrim(char const *s1, char const *set)` | `s1` 양끝에서 `set` 문자 제거 |
| `ft_split` | `char **ft_split(char const *s, char c)` | 구분자 `c`로 분리, `NULL`로 끝나는 배열 반환 |
| `ft_itoa` | `char *ft_itoa(int n)` | 정수 → 문자열 (음수 처리 필수) |
| `ft_strmapi` | `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | 각 문자에 `f(인덱스, 문자)` 적용해 새 문자열 |
| `ft_striteri` | `void ft_striteri(char *s, void (*f)(unsigned int, char*))` | 각 문자를 주소로 `f`에 전달(수정 가능) |
| `ft_putchar_fd` | `void ft_putchar_fd(char c, int fd)` | fd에 문자 출력 |
| `ft_putstr_fd` | `void ft_putstr_fd(char *s, int fd)` | fd에 문자열 출력 |
| `ft_putendl_fd` | `void ft_putendl_fd(char *s, int fd)` | fd에 문자열 + 개행 출력 |
| `ft_putnbr_fd` | `void ft_putnbr_fd(int n, int fd)` | fd에 정수 출력 |

## 6. Part 3 (Bonus) — 연결 리스트

`libft.h`에 구조체 추가:

```c
typedef struct s_list
{
	void			*content;   // 노드 데이터 (void* → 임의 타입 저장)
	struct s_list	*next;      // 다음 노드 주소, 마지막이면 NULL
}	t_list;
```

| 함수 | 설명 |
|------|------|
| `ft_lstnew` | 새 노드 생성 (`content` 초기화, `next`=NULL) |
| `ft_lstadd_front` | 리스트 맨 앞에 노드 추가 |
| `ft_lstsize` | 노드 개수 반환 |
| `ft_lstlast` | 마지막 노드 반환 |
| `ft_lstadd_back` | 리스트 맨 뒤에 노드 추가 |
| `ft_lstdelone` | `del`로 content 해제 + 노드 해제 (next는 해제 안 함) |
| `ft_lstclear` | 노드와 이후 전부 삭제 후 포인터를 NULL로 |
| `ft_lstiter` | 각 노드 content에 `f` 적용 |
| `ft_lstmap` | 각 content에 `f` 적용한 새 리스트 생성 (`del`로 실패 시 정리) |

## 7. README 요구사항 (과제 자체 요구)

저장소 루트에 `README.md` 필수. 최소 포함 항목:
- 첫 줄(이탤릭): `This project has been created as part of the 42 curriculum by <login>`
- **Description**: 프로젝트 목표와 개요
- **Instructions**: 컴파일/설치/실행 정보
- **Resources**: 참고 자료 + **AI 사용 내역**(어떤 작업/부분에 사용했는지) 명시
- 생성한 라이브러리에 대한 상세 설명 (언어 자유, 영어 권장)

## 8. 제출 및 평가

- Git 저장소 루트에 모든 파일 제출. 파일명 정확히 확인.
- 평가 중 간단한 코드 수정 요청(동작 변경, 함수 일부 재작성 등)이 있을 수 있음 — 이해도 검증용.
