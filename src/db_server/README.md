db_server
=========

This is where the code will be for setting up the db server for the system. It can be run on the same host as the
web server or on a seperate system.

Setup
-----

Create the database

`mysql -u root -p < wallboard_monitor.sql`

Drop the database

`mysql -u root -p mysql < drop_db.sql`
