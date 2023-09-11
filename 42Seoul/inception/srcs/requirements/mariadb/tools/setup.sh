#!/bin/sh
cat /var/lib/mysql/.setup 2> /dev/null

if [ $? -ne 0 ]; then
  service mysql start;
  mysql -e "CREATE DATABASE IF NOT EXISTS $MARIADB_DB_NAME";
  mysql -e "CREATE USER IF NOT EXISTS '$MARIADB_USER'@'%' IDENTIFIED BY '$MARIADB_PWD'";
  mysql -e "GRANT ALL PRIVILEGES ON $MARIADB_DB_NAME.* TO '$MARIADB_USER'@'%'";
  mysql -e "set password=password('$MARIADB_ROOT_PWD');"
  sleep 1
  mysql -u$MARIADB_ROOT -p$MARIADB_ROOT_PWD -e "FLUSH PRIVILEGES;"
  mysqladmin -u$MARIADB_ROOT -p$MARIADB_ROOT_PWD shutdown
  touch /var/lib/mysql/.setup
fi
exec mysqld
