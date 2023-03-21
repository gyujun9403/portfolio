sleep 5;
cat /var/lib/wordpress/.setup 2> /dev/null

if [ $? -ne 0 ]; then
  sed -i "s#/run/php/php7.3-fpm.sock#0.0.0.0:9000#g" /etc/php/7.3/fpm/pool.d/www.conf
  sed -i "s/database_name_here/${MARIADB_DB_NAME}/g" /var/www/wordpress/wp-config.php
  sed -i "s/username_here/${MARIADB_USER}/g" /var/www/wordpress/wp-config.php
  sed -i "s/password_here/${MARIADB_PWD}/g" /var/www/wordpress/wp-config.php
  sed -i "s/localhost/${MARIADB_HOST}/g" /var/www/wordpress/wp-config.php
  wp core install --url="${WORDPRESS_URL}" --title="${WORDPRESS_TITLE}" --admin_user="${WORDPRESS_ADMIN_USER}" --admin_password="${WORDPRESS_ADMIN_PWD}" --admin_email="${WORDPRESS_ADMIN_EMAIL}" --skip-email --path=/var/www/wordpress --allow-root
  wp plugin update --all --path=/var/www/wordpress --allow-root
  wp user create $WORDPRESS_USER $WORDPRESS_USER_EMAIL --role=author --user_pass=$WORDPRESS_USER_PWD --path=/var/www/wordpress --allow-root
  touch /var/lib/wordpress/.setup
fi

exec php-fpm7.3 -F