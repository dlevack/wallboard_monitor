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

create table Status_Table (STATUS_ID int auto_increment not null,
       	     		   STATUS_NAME varchar(10) not null,
			   STATUS_COLOR varchar(10) not null,
			   Primary Key(STATUS_ID));

insert into Status_Table values ('','Unknown','clear');
insert into Status_Table values ('','Disabled','blue');
insert into Status_Table values ('','OK','green');
insert into Status_Table values ('','Warning','yellow');
insert into Status_Table values ('','Critical','red');
