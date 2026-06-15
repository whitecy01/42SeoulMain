# Minishell — 요구사항 정리

> 42Seoul Circle 3 · *As beautiful as a shell* (Subject Version 9.0)
> 본 문서는 `minishell.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

간단한 **쉘(작은 Bash)** 을 직접 구현하는 프로젝트. 프로세스와 파일 디스크립터에 대한 깊은 지식을 얻는다. 의심스러운 동작은 **bash를 기준**으로 삼는다.

## 2. Mandatory — `minishell`

| 항목 | 내용 |
|------|------|
| 프로그램명 | `minishell` |
| 제출 파일 | `Makefile`, `*.h`, `*.c` |
| libft 사용 | 허용 |

**허용 외부 함수**: `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

### 기본 동작
- 명령 대기 시 **프롬프트** 표시.
- 동작하는 **히스토리**.
- PATH 변수 또는 상대/절대 경로로 올바른 실행 파일을 찾아 실행.
- **전역 변수는 최대 1개** (수신한 시그널 번호 저장용으로만). 시그널 핸들러가 메인 데이터 구조에 접근하지 않도록 — 전역에 시그널 번호 외 정보/데이터 접근을 두는 것은 금지.

### 파싱 / 따옴표
- 닫히지 않은 따옴표나 과제가 요구하지 않는 특수문자(`\`, `;`)는 해석하지 않음.
- **작은따옴표 `'`**: 내부 메타문자 해석 방지.
- **큰따옴표 `"`**: 내부 메타문자 해석 방지, 단 `$`는 예외(확장).

### 리다이렉션 & 파이프
- `<` 입력 리다이렉션, `>` 출력 리다이렉션, `>>` 추가(append) 출력.
- `<<` (here_doc): delimiter를 받아 그 줄을 만날 때까지 입력 읽기 (히스토리 갱신 불필요).
- `|` 파이프: 각 명령의 출력을 다음 명령의 입력에 연결.

### 변수 확장
- 환경 변수 `$이름` → 값으로 확장.
- `$?` → 가장 최근 foreground 파이프라인의 **종료 상태**로 확장.

### 시그널 (interactive 모드, bash처럼)
- `ctrl-C`: 새 줄에 새 프롬프트 표시.
- `ctrl-D`: 쉘 종료.
- `ctrl-\`: 아무것도 안 함.

### 빌트인 명령 (구현 필수)
| 명령 | 비고 |
|------|------|
| `echo` | 옵션 `-n` |
| `cd` | 상대/절대 경로만 |
| `pwd` | 옵션 없음 |
| `export` | 옵션 없음 |
| `unset` | 옵션 없음 |
| `env` | 옵션·인자 없음 |
| `exit` | 옵션 없음 |

> `readline()`이 일으키는 메모리 누수는 고치지 않아도 됨. 단 **본인이 작성한 코드의 누수는 불허.** 과제에 없는 것은 구현 불필요.

## 3. Bonus

> mandatory가 **완벽**할 때만 평가.

- 우선순위 괄호와 함께 `&&`, `||` 구현.
- 현재 작업 디렉터리에 대한 **와일드카드 `*`** 동작.

## 4. 공통 규칙 & 제출

- 언어 C, **Norm** 준수(보너스 포함). 비정상 종료/메모리 누수 시 0점.
- Makefile은 `cc` + `-Wall -Wextra -Werror`, relink 금지. libft 사용 시 `libft` 폴더 연계.
- 루트에 `README.md` 필수(첫 줄 42 문구, Description/Instructions/Resources+AI 사용 내역).
- 평가 중 간단한 수정 요청 가능(이해도 검증용).
