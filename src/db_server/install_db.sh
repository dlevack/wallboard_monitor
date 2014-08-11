#!/bin/bash
echo -n "Database root user: "
read USER
echo -n "          Password: "
stty -echo
read PASS
stty echo
echo "";
DB_COUNT=`mysqlshow -u $USER -p$PASS |grep wallboard_db|wc -l`
echo "Found $DB_COUNT databases"

if [ $DB_COUNT == 0 ]
then
    mysql -u $USER -p$PASS < wallboard_monitor.sql
else
    echo -n "Database exists! Would you like to drop and recreate? [y/n]: "
    read RECREATE
    if [ $RECREATE == 'y' ] 
    then
	mysql -u $USER -p$PASS < drop_db.sql
	mysql -u $USER -p$PASS < wallboard_monitor.sql
    else
	echo "Unable to create database. Please edit SQL file to change database name."
    fi
fi

# echo $USER
# echo $PASS