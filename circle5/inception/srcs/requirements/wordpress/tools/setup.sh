#!/bin/sh

i=0
while ! mysqladmin -h$MYSQL_HOST -u$MYSQL_USER -p$MYSQL_PASSWORD ping >/dev/null 2>&1; do
  if [ $i -eq 0 ]; then
    echo "Waiting for MariaDB at Wordpress ..."
  else
    echo "Waiting for MariaDB at Wordpress ... ${i}"
  fi
	sleep 5
  i=$(($i+1))
done
echo "Waiting for MariaDB at Wordpress ... done"

wp-cli core download --allow-root
wp-cli config create --dbname=$MYSQL_DB --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=$MYSQL_HOST --allow-root
wp-cli core install --url=$DOMAIN_NAME --title=$WP_TITLE --admin_user=$WP_ADMIN_USER --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root
wp-cli user create $WP_USER $WP_USER_EMAIL --user_pass=$WP_USER_PASSWORD --role=editor --allow-root
#wp-cli theme install astra --allow-root
#wp-cli theme update astra --allow-root
#wp-cli theme activate astra --allow-root

echo "\
--------------------

@wordpress ready
@port:9000

--------------------"

exec /usr/sbin/php-fpm7.3 -F