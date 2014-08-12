db_server
=========

This is where the code will be for setting up the db server for the system. It can be run on the same host as the
web server or on a seperate system.

file list
---------

* README.md - This file
* db_config.php - PHP script for editing the DB config file
* drop_db.sql - SQL file for dropping the database and removing the user.
* install_db.sh - Bash script for installing the database
* wallboard_monitor.sql - SQL file to create the database, add the user, and grand the user access to the database

Setup
-----

`./db_config.php`

`./install_db.sh`
