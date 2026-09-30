#!/bin/sh
if [ ! -d "/var/lib/mysql/$MYSQL_DB" ]; then
  mysql_install_db --datadir=/var/lib/mysql --auth-root-authentication-method=normal >/dev/null
  mysqld --bootstrap << EOF
use mysql;
flush privileges;
create database $MYSQL_DB;
create user '$MYSQL_USER'@'%' identified by '$MYSQL_PASSWORD';
grant all privileges on $MYSQL_DB.* to '$MYSQL_USER'@'%';
alter user '$MYSQL_ROOT'@'localhost' identified by '$MYSQL_ROOT_PASSWORD';
flush privileges;
EOF
fi
echo "\
--------------------
@mariadb ready
@port:3306
--------------------"
exec mysqld --datadir=/var/lib/mysql

#EOF (End Of File) 이후의 SQL 쿼리는 다음을 실행:
# use mysql;: 'mysql' 데이터베이스를 사용.
# flush privileges;: 권한을 새로고침하여 변경 사항을 적용.
# create database $MYSQL_DB;: 새로운 데이터베이스를 생성.
# create user '$MYSQL_USER'@'%' identified by '$MYSQL_PASSWORD';: 새로운 사용자를 생성하고 비밀번호를 설정.
# grant all privileges on $MYSQL_DB.* to '$MYSQL_USER'@'%';: 해당 사용자에게 새로 생성된 데이터베이스에 대한 모든 권한을 부여.
# alter user '$MYSQL_ROOT'@'localhost' identified by '$MYSQL_ROOT_PASSWORD';: root 사용자의 비밀번호를 변경.
# flush privileges;: 권한을 새로고침하여 변경 사항을 적용.