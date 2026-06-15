# ft_transcendence (신버전) — 요구사항 정리

> 42Seoul Circle 6 · *Surprise.* (Subject Version 19.0)
> 본 문서는 `ft_transcendence.pdf`(신버전, 모듈형) 과제 명세를 한국어로 정리한 요구사항 문서입니다.
> 구버전(v13, Pong 콘테스트)은 [README_before.md](./README_before.md) 참고.

## 1. 개요

Common Core 마지막 프로젝트. **4~5인 팀**으로 실제 웹 애플리케이션을 만든다. 프로젝트 아이디어는 팀이 자유롭게 결정(Pong에 한정되지 않음). **고정된 mandatory 코어 + 선택 모듈(점수)** 구조.

## 2. 팀 조직 (Team Organization)

- **필수 역할 배정**(README.md에 명시):
  - **Product Owner (PO)**: 제품 비전·우선순위, 백로그 유지, 기능 결정, 완료 검증, 이해관계자 소통.
  - **Project Manager (PM)/Scrum Master**: 회의·계획 조직, 진행·마감 추적, 소통 보장, 리스크 관리.
  - **Technical Lead/Architect**: 기술 아키텍처·스택 결정, 코드 품질·베스트 프랙티스, 핵심 코드 리뷰.
  - **Developers (전원)**: 기능·모듈 구현, 코드 리뷰 참여, 테스트, 문서화.
- 4인: 일부 역할 겸임 / 5인: 전담 PO·PM·Tech Lead + Developer 2.
- 평가 시 역할 분배·작업 조직·소통·기여를 설명해야 하며, **전원이 프로젝트와 본인 기여를 설명**할 수 있어야 함.

## 3. Mandatory part — General requirements

(위반 시 프로젝트 거부)
- 웹 애플리케이션: **프론트엔드 + 백엔드 + 데이터베이스** 필수.
- Git: 명확한 커밋 메시지, **전원 커밋**, 적절한 작업 분배.
- 배포: **컨테이너화(Docker/Podman 등)**, **단일 명령**으로 실행.
- 최신 **Google Chrome** 호환, 브라우저 콘솔에 경고·에러 없음.
- **Privacy Policy & Terms of Service** 페이지(접근 가능, 실내용 포함, placeholder 금지) — 없으면 거부.
- **다중 사용자 동시 지원(Multi-user, 필수)**: 동시 로그인·동작, 동시성 처리, 실시간 갱신, 데이터 손상·레이스 컨디션 없음.

## 4. Mandatory part — Technical requirements

- 프론트엔드: 명확·반응형·모든 기기 접근 가능. **CSS 프레임워크/스타일링 솔루션** 사용(Tailwind, Bootstrap 등).
- credential은 **`.env`(git ignore) + `.env.example`** 제공.
- DB: 명확한 스키마·정의된 관계.
- **기본 사용자 관리 시스템**: 안전한 회원가입·로그인. 최소 **email+password**(해시·솔트). OAuth·2FA 등은 모듈로.
- 모든 폼·입력은 **프론트+백엔드 양쪽 검증**.
- 백엔드는 **HTTPS 전면 사용**.
- *프레임워크 정의*: 구조·관례·내장 기능·생태계를 제공하는 도구. (React/Vue/Angular/Svelte/Next.js, Express/Fastify/NestJS/Django/Flask 등. jQuery·Lodash·Axios는 프레임워크 아님. React는 본 과제 맥락상 프레임워크로 간주.)

## 5. Modules — 총 14점 필요

각 **Major = 2점**, **Minor = 1점**. 14점 초과 권장(평가 시 일부 불인정 대비). 카테고리: Web / Accessibility·i18n / User Management / AI / Cybersecurity / Gaming & UX / Devops / Data·Analytics / Blockchain / Modules of choice.

> **의존성 주의**: Gaming 모듈(AI 상대, 토너먼트, 커스터마이징, 관전, 3+ 멀티, 게임 추가)·Game Statistics는 **게임 최소 1개 선구현** 필요. Advanced chat은 기본 chat(User interaction) 필요. SSR은 ICP 블록체인 백엔드와 비호환. 평가 시 데모 못 하거나 미완성 모듈 = 0점.

### 5.1 Web
- **Major**: 프론트+백엔드 모두 프레임워크 사용 / 실시간 기능(WebSocket 등) / 유저 상호작용(기본 chat+프로필+친구) / 보안 public API(API 키·rate limit·문서·5+ 엔드포인트).
- **Minor**: 프론트 프레임워크 / 백엔드 프레임워크 / ORM / 알림 시스템 / 실시간 협업 / SSR / PWA / 커스텀 디자인 시스템(10+ 컴포넌트) / 고급 검색(필터·정렬·페이지네이션) / 파일 업로드·관리.

### 5.2 Accessibility & Internationalization
- **Major**: WCAG 2.1 AA 완전 준수(스크린리더·키보드·보조기술).
- **Minor**: 다국어(3+ 언어, i18n·언어 전환기) / RTL 지원 / 추가 브라우저(2+) 지원.

### 5.3 User Management
- **Major**: 표준 사용자 관리·인증(프로필 수정·아바타·친구 온라인 상태·프로필 페이지) / 고급 권한 시스템(CRUD·역할 관리) / 조직(organization) 시스템.
- **Minor**: 게임 통계·매치 히스토리(게임 필요) / OAuth 2.0 원격 인증 / 2FA / 사용자 활동 분석 대시보드.

### 5.4 Artificial Intelligence
- **Major**: AI 게임 상대(인간 유사, 가끔 승리, 게임 필요) / RAG 시스템 / LLM 인터페이스 / ML 추천 시스템.
- **Minor**: 콘텐츠 모더레이션 AI / 음성·speech 통합 / 감정 분석 / 이미지 인식·태깅.

### 5.5 Cybersecurity
- **Major**: WAF/ModSecurity(하드닝) + HashiCorp Vault(시크릿 암호화·격리).

### 5.6 Gaming & user experience
- **Major**: 웹 게임 구현(실시간 멀티, 명확한 규칙·승패, 2D/3D) / 원격 플레이어(별도 컴퓨터, 지연·끊김·재접속 처리) / 3+ 멀티플레이어 / 게임 추가(히스토리·매치메이킹) / 고급 3D 그래픽(Three.js·Babylon.js).
- **Minor**: 고급 chat(차단·게임 초대·알림·프로필·이력·타이핑/읽음, 기본 chat 필요) / 토너먼트 시스템 / 게임 커스터마이징 / 게이미피케이션(업적·뱃지·리더보드 등 3+) / 관전 모드.

### 5.7 Devops
- **Major**: ELK 로그 관리 / Prometheus+Grafana 모니터링 / 마이크로서비스 백엔드.
- **Minor**: 헬스체크·상태 페이지·자동 백업·재해 복구.

### 5.8 Data & Analytics
- **Major**: 고급 분석 대시보드(인터랙티브 차트·실시간·내보내기·필터).
- **Minor**: 데이터 export/import / GDPR 준수 기능.

### 5.9 Blockchain
- **Major**: 토너먼트 점수를 블록체인에 저장(Avalanche + Solidity 스마트 컨트랙트, 테스트넷).
- **Minor**: ICP 백엔드(SSR과 비호환).

### 5.10 Modules of choice
- **Major/Minor**: 목록에 없는 커스텀 모듈. 기술 복잡도·가치·정당성을 README에 명시(사소한 구현은 거부).

> 예시(Pong): 게임6 + User Management3 + Web3 + AI2 = 14점.

## 6. README 요구사항 (저장소 루트)

- **첫 줄 이탤릭**: *This project has been created as part of the 42 curriculum by <login1>[, ...]*.
- 기본: **Description**(프로젝트명·목표·핵심 기능), **Instructions**(전제조건·.env 설정·실행 단계), **Resources**(참고자료 + AI 사용 방식).
- **추가 섹션 필수**: Team Information(역할·책임), Project Management(작업 조직·도구·소통 채널), Technical Stack(프론트·백·DB 선택 근거), Database Schema(구조·관계·필드), Features List(기능·담당자·설명), Modules(목록·점수 계산·정당성·구현·담당자), Individual Contributions(개인별 기여·도전·해결).

## 7. 제출 및 평가

- Git 저장소에 제출, 파일명 정확히 확인. 평가 중 간단한 수정 요청 가능(이해도 검증용). README는 평가의 핵심 — 명확·완전·전문적·정직해야 함.
