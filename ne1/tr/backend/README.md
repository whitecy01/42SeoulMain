### 초기 유저 데이터 삽입 
- ```init.localhost:3000``` 접속
- 콘솔창에 오류는 뜨지만, DB에는 데이터가 잘 들어갑니다.
- 테스트용이니 오류 신경 안쓰셔도 됩니다.

### PostgreSQL CLI 명령어
- PostgreSQL 진입 : ```psql -U postgres -d postgres```
- 데이터베이스 목록 조회 : ```\list```
- 데이터베이스 변경 : ```\c [database]```
- 테이블 목록 조회 : ```\dt```
- 테이블 내 데이터 조회 : ```select * from public.[table];```
- 테이블 데이터 삭제 : ```delete from public.[table];```
- 테이블 삭제 : ```drop table public.[table] cascade;```
