create database wallboard_db;

grant all on wallboard_db.* to 'wallboard_user'@'localhost' identified by 'wallboard_pass';
grant all on wallboard_db.* to 'wallboard_user'@'%' identified by 'wallboard_pass';
flush privileges;

use wallboard_db;

create table Host_Table (HOST_ID int auto_increment not null,
       	     		 HOST_NAME varchar(50) not null,
			 HOST_IP varchar(15) not null,
			 HOST_STATUS int not null default 1,
                         Primary Key(HOST_ID));
