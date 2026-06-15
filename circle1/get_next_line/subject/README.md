# Get Next Line — 요구사항 정리

> 42Seoul Circle 1 · *Reading a line from a file descriptor is way too tedious* (Subject Version 14.0)
> 본 문서는 `get_next_line.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

파일 디스크립터에서 **한 줄씩** 읽어 반환하는 함수를 구현. C의 핵심 개념인 **static 변수**를 학습한다.

## 2. Mandatory — `get_next_line`

| 항목 | 내용 |
|------|------|
| 함수명 | `get_next_line` |
| 프로토타입 | `char *get_next_line(int fd);` |
| 제출 파일 | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` |
| 파라미터 | `fd`: 읽을 파일 디스크립터 |
| 반환값 | 정상: 읽은 줄 / 더 읽을 게 없거나 에러: `NULL` |
| 허용 외부 함수 | `read`, `malloc`, `free` |

**동작 요구사항**
- 반복 호출(루프 등) 시 텍스트 파일을 **한 줄씩** 차례대로 읽을 수 있어야 함.
- 파일 읽기와 **표준 입력(stdin)** 읽기 모두 정상 동작해야 함.
- 반환되는 줄은 끝의 `\n`을 **포함**해야 함. 단, 파일 끝(EOF)에 도달했고 파일이 `\n`으로 끝나지 않으면 `\n` 없이 반환.
- 헤더 `get_next_line.h`는 최소한 `get_next_line()` 프로토타입을 포함.
- 보조 함수는 `get_next_line_utils.c`에 작성.

**BUFFER_SIZE**
- `read()`의 버퍼 크기를 컴파일 옵션 `-D BUFFER_SIZE=n`으로 정의.
- 평가자/Moulinette가 이 값을 바꿔가며 테스트 → **플래그가 있을 때와 없을 때 모두 컴파일**되어야 함(없을 때 쓸 기본값은 자유).
- 컴파일 예시: `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c`
- BUFFER_SIZE가 1, 9999, 10000000 등 어떤 값이어도 동작해야 함.

> 효율: 호출마다 **최소한만 읽기**. 개행을 만나면 현재 줄을 반환. 파일 전체를 읽은 뒤 처리하면 안 됨.

**정의되지 않은 동작(UB)**: 마지막 호출 후 read가 EOF에 도달하지 않은 상태에서 파일이 수정되는 경우, 바이너리 파일을 읽는 경우.

## 3. 금지 사항 (Forbidden)

- **libft 사용 금지.**
- `lseek()` 사용 금지.
- **전역 변수 금지.**

## 4. Bonus

> mandatory가 **완벽**할 때만 평가됨.

- `get_next_line()`을 **static 변수 1개만** 사용해 구현.
- **여러 fd 동시 관리**: fd 3, 4, 5를 번갈아 호출해도 각 fd의 읽기 상태를 잃지 않아야 함.
- 보너스 파일은 `_bonus.[c/h]` 접미사:
  - `get_next_line_bonus.c`
  - `get_next_line_bonus.h`
  - `get_next_line_utils_bonus.c`

## 5. 공통 규칙 & README 요구사항

- 언어 C, **Norm** 준수(보너스 포함). 비정상 종료/메모리 누수 시 0점.
- Makefile은 `cc` + `-Wall -Wextra -Werror`, 불필요한 relinking 금지, 규칙 `$(NAME)/all/clean/fclean/re`.
- 루트에 `README.md` 필수: 첫 줄(이탤릭) 42 문구, **Description / Instructions / Resources**(+AI 사용 내역), **선택한 알고리즘에 대한 상세 설명 및 근거**.

## 6. 제출 및 평가

- 테스트 시 유의: ① 버퍼 크기와 줄 길이는 매우 다양할 수 있음 ② fd는 일반 파일만 가리키는 게 아님.
- 통과 후 `get_next_line()`을 libft에 추가 가능. 평가 중 간단한 코드 수정 요청 가능.
