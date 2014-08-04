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

insert into Status_Table values (1,'Unknown','clear');
insert into Status_Table values (2,'Disabled','blue');
insert into Status_Table values (3,'OK','green');
insert into Status_Table values (4,'Warning','yellow');
insert into Status_Table values (5,'Critical','red');

create table Page_Table (PAGE_ID int auto_increment not null,
       	     		 PAGE_NAME varchar(50) not null,
			 PAGE_DESC varchar(255) not null,
       	     		 Primary Key(PAGE_ID));

insert into Page_Table values (1,
       	    	       	       'Default',
			       'Default page - Displayed if no page is specified');

create table Category_Table (CAT_ID int auto_increment not null,
       	     		     CAT_NAME varchar(50) not null,
			     CAT_DESC varchar(255) not null,
       	     		     Primary Key(CAT_ID));

insert into Category_Table values (1,
       	    		   	   'Wallboard Servers',
				   'Servers that are part of the monitoring system');

create table Page_Category_Table (PAGE_ID int not null,
       	     			  CAT_ID int not null,
       	     			  Primary Key(PAGE_ID,CAT_ID));

insert into Page_Category_Table values (1,1);

create table Category_Host_Table (CAT_ID int not null,
       	     			  HOST_ID int not null,
				  Primary Key(CAT_ID,HOST_ID));
