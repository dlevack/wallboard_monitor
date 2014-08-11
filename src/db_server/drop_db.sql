use mysql;
drop database wallboard_db;
delete from user where User='wallboard_user';
flush privileges;
