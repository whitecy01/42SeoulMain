# Pipex — 요구사항 정리

> 42Seoul Circle 2 · *Explore a UNIX mechanism (pipe) in detail* (Subject Version 4.0)
> 본 문서는 `pipex.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

쉘에서 익숙한 **파이프(`|`)** 메커니즘을 직접 구현하는 프로젝트. 프로세스 생성(`fork`), 파이프(`pipe`), 입출력 리다이렉션(`dup2`), 프로그램 실행(`execve`)을 학습한다.

## 2. Mandatory — `pipex`

| 항목 | 내용 |
|------|------|
| 프로그램명 | `pipex` |
| 제출 파일 | `Makefile`, `*.h`, `*.c` |
| Makefile 규칙 | `NAME`, `all`, `clean`, `fclean`, `re` |
| 인자 | `file1 cmd1 cmd2 file2` |
| libft 사용 | 허용 |

**허용 외부 함수**
- `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid`
- 직접 코딩한 `ft_printf` 또는 그에 준하는 함수

**동작**

```bash
./pipex file1 cmd1 cmd2 file2
```

4개 인자를 받음:
- `file1`, `file2`: 파일 이름
- `cmd1`, `cmd2`: 인자를 포함한 쉘 명령

다음 쉘 명령과 **정확히 동일하게** 동작해야 함:

```bash
< file1 cmd1 | cmd2 > file2
```

**예시**
```bash
./pipex infile "ls -l" "wc -l" outfile   # < infile ls -l | wc -l > outfile
./pipex infile "grep a1" "wc -w" outfile  # < infile grep a1 | wc -w > outfile
```

## 3. 요구사항 (Requirements)

- Makefile은 불필요한 relinking 금지.
- 프로그램이 **비정상 종료(segfault, bus error, double free 등) 금지**.
- **메모리 누수 금지.**
- 에러 처리는 확신이 없으면 위 쉘 명령(`< file1 cmd1 | cmd2 > file2`)과 동일하게.

## 4. Bonus

> mandatory가 **완벽**할 때만 평가.

- **다중 파이프** 처리:
  ```bash
  ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
  # < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
  ```
- 첫 인자가 `"here_doc"`일 때 `<<` / `>>` 지원:
  ```bash
  ./pipex here_doc LIMITER cmd cmd1 file
  # cmd << LIMITER | cmd1 >> file
  ```

## 5. 공통 규칙 & 제출

- 언어 C, **Norm** 준수(보너스 포함). 비정상 종료/메모리 누수 시 0점.
- Makefile은 `cc` + `-Wall -Wextra -Werror`. libft 사용 시 `libft` 폴더에 소스+Makefile 복사 후 빌드 연계.
- Git 저장소에 제출, 파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
