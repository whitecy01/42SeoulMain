# ft_irc — 요구사항 정리

> 42Seoul Circle 5 · *Internet Relay Chat* (Subject Version 9.1)
> 본 문서는 `ft_irc.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

직접 **IRC 서버**를 C++98로 구현한다. 실제 IRC 클라이언트로 서버에 접속해 테스트한다. 인터넷을 지탱하는 표준 프로토콜(TCP/IP, IRC)을 이해하는 것이 목표.

- **IRC 클라이언트를 만들지 않는다.**
- **서버 간(server-to-server) 통신을 구현하지 않는다.**

## 2. 공통 규칙 (General rules)

- 어떤 상황에서도(메모리 부족 포함) **크래시·예기치 못한 종료 금지** → 위반 시 0점(비기능 간주).
- `Makefile`: 불필요한 relink 금지, 규칙 `$(NAME)`, `all`, `clean`, `fclean`, `re` 포함.
- `c++` + `-Wall -Wextra -Werror`, **C++98 표준**(`-std=c++98`로도 컴파일).
- 가능하면 C++ 기능 선호(`<cstring>` > `<string.h>`). C 함수 허용하나 C++ 버전 우선.
- **외부 라이브러리·Boost 금지.**

## 3. Mandatory part

| 항목 | 내용 |
|------|------|
| 프로그램명 | `ircserv` |
| 제출 파일 | `Makefile`, `*.{h,hpp}`, `*.cpp`, `*.tpp`, `*.ipp`, (선택) 설정 파일 |
| 실행 | `./ircserv <port> <password>` |
| 인자 | `port`(수신 포트), `password`(접속 비밀번호) |
| 허용 외부 함수 | C++98 전체 + `socket`, `close`, `setsockopt`, `getsockname`, `getprotobyname`, `gethostbyname`, `getaddrinfo`, `freeaddrinfo`, `bind`, `connect`, `listen`, `accept`, `htons`, `htonl`, `ntohs`, `ntohl`, `inet_addr`, `inet_ntoa`, `inet_ntop`, `send`, `recv`, `signal`, `sigaction`, `sigemptyset`, `sigfillset`, `sigaddset`, `sigdelset`, `sigismember`, `lseek`, `fstat`, `fcntl`, `poll`(또는 동등 함수) |
| libft | 사용 불가(n/a) |

### 3.1 Requirements
- **여러 클라이언트를 동시에** 멈춤 없이 처리.
- **fork 금지.** 모든 I/O는 **non-blocking**.
- 모든 작업(read/write/listen 등)에 **`poll()`(또는 select/kqueue/epoll 등 동등) 단 1개만** 사용.
  - non-blocking fd라도 **poll 없이 read/recv/write/send 하면 0점.**
- IRC 클라이언트 하나를 **레퍼런스 클라이언트**로 선택(평가에 사용). 에러 없이 서버에 접속되어야 함.
- 통신은 **TCP/IP (v4 또는 v6)**.
- 공식 IRC 서버처럼 동작해야 하며, 최소 다음 기능 구현:
  - **인증**, 닉네임(nickname)·유저네임(username) 설정, **채널 참가(join)**, **개인 메시지(private message)** 송수신.
  - 한 클라이언트가 채널에 보낸 메시지는 **그 채널의 다른 모든 참가자에게 전달(forward)**.
  - **operator(운영자)와 일반 사용자** 구분.
  - **채널 운영자 전용 명령어**:
    - `KICK` — 채널에서 클라이언트 추방.
    - `INVITE` — 클라이언트를 채널에 초대.
    - `TOPIC` — 채널 토픽 변경/조회.
    - `MODE` — 채널 모드 변경:
      - `i`: 초대 전용(invite-only) 채널 설정/해제.
      - `t`: TOPIC 명령을 운영자만 가능하도록 제한 설정/해제.
      - `k`: 채널 키(비밀번호) 설정/해제.
      - `o`: 채널 운영자 권한 부여/회수.
      - `l`: 채널 사용자 수 제한 설정/해제.
- 깔끔한 코드 작성 요구.

### 3.2 MacOS 한정
- MacOS의 `write()` 동작이 달라 **`fcntl()` 사용 허용**. 단 **`fcntl(fd, F_SETFL, O_NONBLOCK)` 형태만** 허용, 다른 플래그 금지.

### 3.3 테스트 예시 (부분 데이터 처리)
- 부분 수신, 저대역폭 등 모든 에러·상황 검증 필요.
- `nc -C 127.0.0.1 6667`에서 `ctrl+D`로 명령을 여러 조각(`com`→`man`→`d\n`)으로 전송해도 처리되어야 함 → **수신 패킷을 모아 명령을 재조립(aggregate)** 후 처리.

## 4. Bonus part

> mandatory가 **완벽**할 때만 평가. 모든 mandatory 요구사항 통과 못하면 보너스 전혀 평가 안 됨.

- 파일 전송(file transfer) 처리.
- 봇(bot).

## 5. 제출 및 평가

- Git 저장소에 제출, 파일명 정확히 확인. 테스트 프로그램 작성 권장(제출·채점 대상 아님, 디펜스에 유용).
- **레퍼런스 클라이언트**가 평가에 사용됨. 평가 중 간단한 수정 요청 가능(이해도 검증용).
