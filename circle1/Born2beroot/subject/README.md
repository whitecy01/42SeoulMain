# Born2beRoot — 요구사항 정리

> 42Seoul Circle 1 · *System Administration related exercise* (Subject Version 5.0)
> 본 문서는 `Born2beroot.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**가상화(virtualization)** 입문 프로젝트. VirtualBox(불가 시 UTM)로 첫 가상머신을 만들고, 엄격한 규칙에 따라 직접 운영체제를 설정한다. 프로그래밍이 아닌 **시스템 관리(System Administration)** 과제.

## 2. 일반 가이드라인 (General Guidelines)

- **VirtualBox**(불가 시 UTM) 사용 필수.
- 저장소 루트에 **`signature.txt`** 1개만 제출 (가상 디스크의 서명).
- **스냅샷 사용 금지** (평가 중 발견 시 0점).

## 3. Mandatory — 서버 구축

### OS & 파티션
- **GUI 설치 금지**: X.org, wayland 등 그래픽 서버 설치 시 **0점**. (서버이므로 최소 서비스만)
- OS는 **최신 안정 버전 Debian**(testing/unstable 불가) 또는 **최신 안정 버전 Rocky** 중 택1. (입문자는 Debian 권장)
- **LVM**으로 **암호화된 파티션 최소 2개** 생성.
- Rocky: KDump 불필요, 단 **SELinux**가 부팅 시 실행되고 설정 적용. Debian: **AppArmor**가 부팅 시 실행.

### 네트워크 & 보안
- **SSH**: 포트 **4242**에서 동작. 보안상 **root SSH 접속 금지**.
- **방화벽**: UFW(Rocky는 firewalld)로 **포트 4242만** 개방, 부팅 시 활성화.
- **hostname**: 본인 로그인 + `42` (예: `wil42`). 평가 중 변경 요구됨.

### 사용자 & 그룹
- root 외에 **본인 로그인 이름의 사용자** 존재.
- 이 사용자는 **`user42`** 와 **`sudo`** 그룹에 속함.

### 강력한 비밀번호 정책 (Password Policy)
- 비밀번호 **30일마다 만료**.
- 비밀번호 변경 전 **최소 2일** 대기.
- 만료 **7일 전 경고** 메시지.
- 최소 **10자**, 대문자·소문자·숫자 포함, **동일 문자 3회 연속 초과 금지**.
- 사용자 이름 포함 금지.
- (root 제외) 이전 비밀번호와 **최소 7자 이상 달라야** 함.
- root 비밀번호도 정책 준수. 설정 후 root 포함 **모든 계정 비밀번호 변경**.

### sudo 설정
- 비밀번호 오류 시 인증 **3회로 제한**.
- 잘못된 비밀번호 시 **커스텀 에러 메시지** 표시.
- 모든 sudo 동작(입력·출력) **아카이빙** → 로그를 **`/var/log/sudo/`** 에 저장.
- **TTY 모드** 활성화.
- sudo가 사용하는 **경로 제한** (예: `/usr/local/sbin:/usr/local/bin:...:/snap/bin`).

### monitoring.sh (bash 스크립트)
서버 부팅 시 + **10분마다** 모든 터미널에 정보 출력(`wall` 활용, 에러 없이). cron으로 동작. 평가 중 동작 설명 + 수정 없이 중단 요구.

표시 정보:
- OS 아키텍처 + 커널 버전
- 물리 프로세서 수 / 가상 프로세서(vCPU) 수
- 가용 RAM 및 사용률(%)
- 가용 저장공간 및 사용률(%)
- CPU 사용률(%)
- 마지막 재부팅 날짜/시간
- LVM 활성 여부
- 활성 연결 수
- 서버 사용 중인 사용자 수
- 서버 IPv4 주소 + MAC 주소
- sudo로 실행된 명령 수

## 4. Bonus

> mandatory가 **완벽**할 때만 평가.

- 권장 구조와 유사한 **파티션 세분화** (root/swap/home/var/srv/tmp/var-log 등).
- **WordPress** 사이트 구축: lighttpd + MariaDB + PHP.
- 유용하다고 생각하는 **추가 서비스** 1개 (NGINX/Apache2 제외, 평가 중 선택 이유 설명). 필요 시 포트 추가 개방 + 방화벽 규칙 조정.

## 5. README 요구사항 (과제 자체 요구)

루트에 `README.md` 필수. 기본 항목(첫 줄 42 문구, Description/Instructions/Resources+AI 사용 내역) 외에 **Project description** 섹션에서 OS 선택 이유(장단점)와 주요 설계 선택(파티셔닝, 보안 정책, 사용자 관리, 설치 서비스), 그리고 다음 비교 포함:
- Debian vs Rocky Linux
- AppArmor vs SELinux
- UFW vs firewalld
- VirtualBox vs UTM

## 6. 제출 및 평가 — signature.txt

- VM 디스크 파일(`.vdi`, UTM은 `.qcow2`)의 **sha1 서명**을 `signature.txt`에 붙여넣기.
  - Linux: `sha1sum file.vdi` / macOS: `shasum file.vdi` / Windows: `certUtil -hashfile file.vdi sha1`
- **VM 자체를 Git에 올리는 것은 금지.** 평가 시 서명이 일치하지 않으면 **0점**.
- 첫 평가 후 서명이 바뀔 수 있음 → VM 복제 또는 save state로 대응.
- 평가 중 간단한 수정 요청 가능(이해도 검증용).
