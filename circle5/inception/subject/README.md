# Inception — 요구사항 정리

> 42Seoul Circle 5 · *System Administration with Docker* (Subject Version 5.0)
> 본 문서는 `Inception.pdf` 과제 명세를 한국어로 정리한 요구사항 문서입니다.

## 1. 개요

**Docker**를 사용해 시스템 관리를 학습한다. 가상 머신(VM) 안에서 여러 Docker 이미지를 직접 만들어, NGINX·WordPress·MariaDB로 구성된 작은 인프라를 `docker compose`로 구축한다.

## 2. General guidelines

- **가상 머신(VM)** 위에서 진행.
- 설정에 필요한 모든 파일은 **`srcs` 폴더**에 위치.
- 디렉터리 **루트에 `Makefile`** 필수 → `docker-compose.yml`로 Docker 이미지를 빌드해 전체 애플리케이션 구성.

## 3. Mandatory part

### 3.1 구성 요건
- `docker compose` 사용. 각 **Docker 이미지명 = 서비스명**, 각 서비스는 **전용 컨테이너**에서 실행.
- 컨테이너는 성능을 위해 **Alpine 또는 Debian의 penultimate(끝에서 두 번째) 안정 버전**으로 빌드.
- 서비스마다 **Dockerfile 직접 작성**(서비스당 1개), `Makefile`이 `docker-compose.yml`을 통해 호출.
- **이미 만들어진 이미지 pull 금지**, DockerHub 같은 서비스 사용 금지(Alpine/Debian 베이스는 예외).

### 3.2 구축할 서비스 (각각 별도 컨테이너)
- **NGINX**: **TLSv1.2 또는 TLSv1.3만** 사용.
- **WordPress + php-fpm**: 설치·설정, **nginx 없이**.
- **MariaDB**: **nginx 없이**.
- **볼륨 1**: WordPress 데이터베이스.
- **볼륨 2**: WordPress 웹사이트 파일.
- **docker-network**: 컨테이너 간 연결.
- 컨테이너는 **크래시 시 재시작(restart)** 되어야 함.

### 3.3 금지 사항 / 제약
- 컨테이너는 VM이 아님 → **무한 루프 기반 hacky 패치 금지**: `tail -f`, `bash`, `sleep infinity`, `while true` 등(entrypoint·entrypoint 스크립트 포함). PID 1·Dockerfile best practice 학습 권장.
- **`network: host`, `--link`, `links:` 금지.** `docker-compose.yml`에 **network 라인 필수**.
- WordPress DB에 **사용자 2명**(그 중 1명은 관리자). 관리자 이름에 `admin`/`Admin`/`administrator`/`Administrator` 포함 금지(`admin-123` 등도 불가).
- 볼륨은 호스트의 **`/home/<login>/data`** 폴더에 위치.
- 도메인 이름을 로컬 IP로 연결: **`<login>.42.fr`** (예: `wil.42.fr`).
- **`latest` 태그 금지.**
- **Dockerfile에 비밀번호 금지.** **환경 변수 사용 필수**, **`.env` 파일 사용 필수**. 기밀 정보는 **Docker secrets** 사용 강력 권장.
  - Git 저장소에 (secrets 외부의) credential·API 키·비밀번호 노출 시 **프로젝트 실패**.
- **NGINX 컨테이너가 인프라로의 유일한 진입점** → **443 포트만**, TLSv1.2/1.3 사용.

### 3.4 디렉터리 구조 (예시)
- 루트: `Makefile`, `secrets/`(credentials.txt, db_password.txt, db_root_password.txt), `srcs/`
- `srcs/`: `docker-compose.yml`, `.env`, `requirements/`
- `srcs/requirements/`: `mariadb/`, `nginx/`, `wordpress/`, `tools/`, `bonus/` (각 서비스에 `Dockerfile`, `.dockerignore`, `conf/`, `tools/`)

## 4. README 요구사항 (저장소 루트)

저장소 루트에 `README.md` 필수. 다음을 포함:
- **첫 줄은 이탤릭**: *This project has been created as part of the 42 curriculum by <login1>[, <login2>...]*.
- **Description**: 프로젝트 목표·개요.
- **Instructions**: 빌드·설치·실행 정보.
- **Resources**: 관련 참고자료 + **AI 사용 방식**(어떤 작업·어느 부분에 사용했는지) 명시.
- **Project description**: Docker 사용·소스 설명, 주요 설계 선택 + 다음 비교:
  - Virtual Machines vs Docker
  - Secrets vs Environment Variables
  - Docker Network vs Host Network
  - Docker Volumes vs Bind Mounts

### 4.1 검증 전제 문서 (Markdown, 루트)
- **`USER_DOC.md`** (사용자 문서): 스택이 제공하는 서비스, 시작/중지, 웹사이트·관리자 패널 접근, credential 위치·관리, 서비스 정상 동작 확인.
- **`DEV_DOC.md`** (개발자 문서): 환경 초기 셋업(전제조건·설정파일·secrets), Makefile·Docker Compose로 빌드·실행, 컨테이너·볼륨 관리 명령, 데이터 저장 위치·영속성.

## 5. Bonus part

> mandatory가 **완벽**할 때만 평가. 추가 서비스마다 Dockerfile 작성, 필요 시 전용 볼륨·추가 포트 허용.

- WordPress용 **redis cache** 설정.
- WordPress 웹사이트 볼륨을 가리키는 **FTP 서버** 컨테이너.
- **PHP 제외** 언어로 만든 간단한 정적 웹사이트.
- **Adminer** 설정.
- 유용하다고 판단되는 자유 서비스(디펜스에서 정당화).

## 6. 제출 및 평가

- Git 저장소에 제출, 폴더·파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용).
