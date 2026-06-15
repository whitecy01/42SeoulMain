# Philosophers — 요구사항 정리

> 42Seoul Circle 3 · *I never thought philosophy would be so deadly* (Subject Version 12.0)
> 본 문서는 `Philosophers.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**식사하는 철학자 문제**를 통해 **스레드(thread)** 와 **뮤텍스(mutex)**, 그리고 보너스에서는 **프로세스와 세마포어**를 학습한다. 동시성 제어와 data race 방지가 핵심.

## 2. 문제 개요 (Overview)

- 원형 테이블에 철학자 1명 이상이 앉아 있고, 가운데 스파게티가 있음.
- 철학자는 **먹기 / 생각하기 / 자기**를 번갈아 함(동시에 하나만).
- 포크는 **철학자 수만큼** 존재. 먹으려면 **양쪽(왼쪽+오른쪽) 포크 2개**를 들어야 함.
- 다 먹으면 포크를 내려놓고 잠. 깨면 다시 생각. 철학자가 **굶어 죽으면** 시뮬레이션 종료.
- 철학자들은 서로 소통하지 않고, 다른 철학자가 죽기 직전인지 모름. 죽지 않아야 함.

## 3. 전역 규칙 (Global rules)

- **전역 변수 금지!**
- 인자:
  ```
  number_of_philosophers time_to_die time_to_eat time_to_sleep
  [number_of_times_each_philosopher_must_eat]
  ```
  | 인자 | 의미 |
  |------|------|
  | `number_of_philosophers` | 철학자 수(= 포크 수) |
  | `time_to_die` (ms) | 마지막 식사 시작/시뮬레이션 시작 이후 이 시간 내에 먹지 못하면 사망 |
  | `time_to_eat` (ms) | 먹는 데 걸리는 시간(이 동안 포크 2개 잡음) |
  | `time_to_sleep` (ms) | 자는 시간 |
  | `[must_eat]` (선택) | 모두가 이 횟수만큼 먹으면 시뮬레이션 종료. 없으면 사망 시 종료 |
- 철학자는 1 ~ N 번호. 1번은 N번 옆에, N번은 N-1과 N+1 사이에 앉음.

### 로그 형식
상태 변화 시 출력 (각각 겹치지 않게):
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
- 사망 메시지는 **실제 사망 후 10ms 이내**에 출력.
- **data race가 없어야 함.**

## 4. Mandatory — `philo` (스레드 + 뮤텍스)

| 항목 | 내용 |
|------|------|
| 프로그램명 | `philo` |
| 제출 파일 | `Makefile`, `*.h`, `*.c` (디렉터리 `philo/`) |
| libft 사용 | **불허** |

**허용 외부 함수**: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

- **각 철학자 = 별도의 스레드.**
- 각 철학자 쌍 사이에 포크 1개(왼쪽/오른쪽). 철학자가 1명이면 포크 1개만 사용 가능.
- 포크 중복 사용을 막기 위해 **각 포크 상태를 뮤텍스로 보호**.

## 5. Bonus — `philo_bonus` (프로세스 + 세마포어)

> mandatory가 **완벽**할 때만 평가.

| 항목 | 내용 |
|------|------|
| 프로그램명 | `philo_bonus` |
| 제출 파일 | `Makefile`, `*.h`, `*.c` (디렉터리 `philo_bonus/`) |

**허용 외부 함수**: 위 + `fork`, `kill`, `exit`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`

- 모든 포크는 테이블 가운데에 둠. 메모리상 상태 없이 **세마포어**로 가용 포크 수 표현.
- **각 철학자 = 별도의 프로세스.** 단, 메인 프로세스는 철학자 역할을 하지 않음.

## 6. 공통 규칙 & 제출

- 언어 C, **Norm** 준수(보너스 포함). 비정상 종료/메모리 누수 시 0점.
- Makefile은 `cc` + `-Wall -Wextra -Werror`, relink 금지.
- mandatory는 `philo/`, bonus는 `philo_bonus/` 디렉터리에 제출. 평가 중 간단한 수정 요청 가능.
