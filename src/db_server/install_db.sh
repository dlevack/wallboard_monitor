#!/bin/bash
echo -n "     Database host: "
read HOST
echo -n "Database root user: "
read USER
echo -n "          Password: "
stty -echo
read PASS
stty echo
echo "";
DB_COUNT=`mysqlshow -h $HOST -u $USER -p$PASS |grep wallboard_db|wc -l`
echo "Found $DB_COUNT databases"

if [ $DB_COUNT == 0 ]
then
    mysql -h $HOST -u $USER -p$PASS < wallboard_monitor.sql
else
    echo -n "Database exists! Would you like to drop and recreate? [y/n]: "
    read RECREATE
    if [ $RECREATE == 'y' ] 
    then
	mysql -h $HOST -u $USER -p$PASS < drop_db.sql
	mysql -h $HOST -u $USER -p$PASS < wallboard_monitor.sql
    else
	echo "Unable to create database. Please edit SQL file to change database name."
    fi
fi
