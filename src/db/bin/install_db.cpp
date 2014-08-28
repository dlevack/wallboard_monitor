#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <stdexcept>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <stdio.h>
#include <algorithm>
#include<sys/socket.h>
#include<errno.h>
#include<netdb.h>
#include<arpa/inet.h>

#define MAX 1024

using namespace std;

string redtext(string s) {
  string st;
  st  = "\033[1;31m";
  st += s;
  st += "\033[0m";
  return st;
}

string cyantext(string s) {
  string st;
  st  = "\033[1;36m";
  st += s;
  st += "\033[0m";
  return st;
}

string greentext(string s) {
  string st;
  st  = "\033[1;32m";
  st += s;
  st += "\033[0m";
  return st;
}

const size_t MAXWIDTH = 100;

void print(const std::string& var_text) {
  std::cout << std::left << std::setw(MAXWIDTH) << std::setfill('.')
            << var_text ;
}

int hostname_to_ip(char * hostname,
                   char* ip) {
  struct hostent *he;
  struct in_addr **addr_list;
  int i;

  if ( (he = gethostbyname( hostname ) ) == NULL) {
    // get the host info
    herror("gethostbyname");
    return 1;
  }

  addr_list = (struct in_addr **) he->h_addr_list;

  for(i = 0; addr_list[i] != NULL; i++) {
    //Return the first one;
    strcpy(ip,
           inet_ntoa(*addr_list[i]));
    return 0;
  }
  return 1;
}

string host;
string name;
string user;
string pass;
string root;
string text;

string getwallhost();
string getwallname();
string getwalluser();
string getwallpass();

sql::Connection *con;                         // Define connection handler
sql::Statement *stmt;                         // Define statement handler
sql::ResultSet  *res;                         // Define result object
sql::Driver * driver = get_driver_instance(); // Defin driver for connection

void connect(string h,
	     string n,
	     string u,
	     string p) {
  con = driver->connect(h,                    // Connect to database host
			u,
			p);
  con->setSchema(n);                          // Select database on host

}

int main(int argc, const char **argv) {
  string query;
  
  host = getwallhost();  // Read database host from config file
  name = getwallname();  // Read database name from config file
  user = getwalluser();  // Read database user from config file
  pass = getwallpass();  // Read database password from config file
  
  /* Get the super user login info so that we can use that to check for db and create it. */
  cout << "Please enter the super user for the MySQL database.\n";
  cout << "This user will only be user for creating the database\n";
  cout << "and the db user from the ini file.\n";
  cout << "Super User [";
  cout << cyantext("root") << "]: ";
  getline(cin,root);
  
  if (root == "") {
    root = "root"; // Set super user to root if none entered
  }
  char *password; // password string pointer
  password = getpass("Enter Password: "); // get a password
  
  /* Verify that we can connect to the database*/
  text  = "Attempting to connect to ";
  text += host;
  text += " with user ";
  text += root;
  print(text);
  
  try {
    connect(host,
	    "mysql",
	    root,
	    password);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  
  /* Check to see if the database already exists */
  text  = "Checking to see if ";
  text += name;
  text += " database exists";
  print(text);
  stmt = con->createStatement();
  res = stmt->executeQuery("show databases");
  bool dbfound;
  while (res->next()) {
    if (res->getString("database") == name) {
      dbfound = 1;
    }
  }
  if (dbfound) {
    /* Database exists - Chack to see if user wants to drop and recreate */
    cout << "[" << redtext("Found") << "]";
    cout << "\n\n";
    cout << "Would you like to remove the existing ";
    cout << name;
    cout << " database and recreate it?\n";
    
    /* Warn that all data will be lost if dropped */
    
    cout << redtext("Any data in the ");
    cout << redtext(name);
    cout << redtext(" database will be lost!\n");
    cout << "Recreate [yes/";
    cout << cyantext("no");
    cout << "]: ";
    string recreate;
    getline(cin,recreate);
    if (recreate == "") {
      recreate = "no"; // Set recreate to no if nothing was entered
    }
    if (recreate != "yes") {
      /* Exit unless user specified 'yes' */
      recreate.clear();
      return EXIT_FAILURE;
    }
    recreate.clear();  
    /* Drop the database */
    text  = "Dropping database ";
    text += name;
    print(text);
    
    query  = "drop database ";
    query += name;
    try {
      stmt->execute(query);
      cout << "[" << greentext("OK") << "]";
      cout << "\n";
    }
    catch (sql::SQLException &e) {
      cout << "[" << redtext("Failed") << "]";
      cout << "\n";
      return EXIT_FAILURE;
    }
    query.clear();
    
    /* Remove User */
    text  = "Removing ";
    text += user;
    text += " user";
    print(text);

    query  = "delete from user where User='";
    query += user;
    query += "'";
    try {
      stmt->execute(query);
      cout << "[" << greentext("OK") << "]";
      cout << "\n";
    }
    catch (sql::SQLException &e) {
      cout << "[" << redtext("Failed") << "]";
      cout << "\n";
      return EXIT_FAILURE;
    }
    query.clear();

  } else {
    cout << "[" << greentext("Not Found") << "]";
    cout << "\n";
  }
  /* Create the database */
  text  = "Creating database ";
  text += name;
  print(text);
  query  = "create database ";
  query += name;
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add Database User */
  text  = "Adding ";
  text += user;
  text += " from localhost";
  print(text);
  query  = "grant all on ";
  query += name;
  query += ".* to '";
  query += user;
  query += "'@'localhost' identified by '";
  query += pass;
  query += "'";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add Database User */
  text  = "Adding ";
  text += user;
  text += " from remote host";
  print(text);
  query  = "grant all on ";
  query += name;
  query += ".* to '";
  query += user;
  query += "'@'%' identified by '";
  query += pass;
  query += "'";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  con->setSchema(name); // Select the database we just created
  
  /* Add the host table */
  text  = "Adding Host_Table to database";
  print(text);
  query  = "create table Host_Table (HOST_ID int auto_increment not null,";
  query += "HOST_NAME varchar(50) not null,";
  query += "HOST_IP varchar(15) not null,";
  query += "HOST_STATUS int not null default 1,";
  query += "Primary Key(HOST_ID))";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add this host to host table */

  char hostname[1024];
  gethostname(hostname,
              1024);
  char ip[100];

  hostname_to_ip(hostname,
                 ip);
  text  = "Adding ";
  text += hostname;
  text += " to Host_Table";
  print(text);
  query  = "insert into Host_Table (HOST_NAME, HOST_IP) values";
  query += "('";
  query += hostname;
  query += "','";
  query += ip;
  query += "')";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  

  /* Add the status table */
  text  = "Adding Status_Table to database";
  print(text);
  query  = "create table Status_Table (STATUS_ID int auto_increment not null,";
  query += "STATUS_NAME varchar(10) not null,";
  query += "STATUS_COLOR varchar(10) not null,";
  query += "Primary Key(STATUS_ID))";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Insert status records */
  text  = "Adding default data to Status_Table";
  print(text);
  query  = "insert into Status_Table (STATUS_NAME,STATUS_COLOR) values";
  query += "('Unknown','white'),";
  query += "('Disabled','blue'),";
  query += "('OK','green'),";
  query += "('Warning','yellow'),";
  query += "('Critical','red')";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add page table */
  text  = "Adding Page_Table to database";
  print(text);
  query  = "create table Page_Table (PAGE_ID int auto_increment not null,";
  query += "PAGE_NAME varchar(50) not null,";
  query += "PAGE_DESC varchar(255) not null,";
  query += "Primary Key(PAGE_ID))";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Insert page records */
  text  = "Adding default data to Page_Table";
  print(text);
  query  = "insert into Page_Table (PAGE_NAME,PAGE_DESC) values";
  query += "('Default','Default page - Displayed if no page is specified')";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add category table */
  text  = "Adding Category_Table to database";
  print(text);
  query  = "create table Category_Table (CAT_ID int auto_increment not null,";
  query += "CAT_NAME varchar(50) not null,";
  query += "CAT_DESC varchar(255) not null,";
  query += "Primary Key(CAT_ID))";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();

  /* Insert category records */
  text  = "Adding default data to Category_Table";
  print(text);
  query  = "insert into Category_Table (CAT_NAME,CAT_DESC) values";
  query += "('Wallboard Servers','Servers that are part of the monitoring system')";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add page category table */
  text  = "Adding Page_Category_Table to database";
  print(text);
  query  = "create table Page_Category_Table (PAGE_ID int not null,";
  query += "CAT_ID int not null,";
  query += "Primary Key(PAGE_ID,CAT_ID))";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();

  /* Insert category records */
  text  = "Adding default data to Page_Category_Table";
  print(text);
  query  = "insert into Page_Category_Table (PAGE_ID,CAT_ID) values";
  query += "(1,1)";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add category host table */
  text  = "Adding Category_Host_Table to database";
  print(text);
  query  = "create table Category_Host_Table (CAT_ID int not null,";
  query += "HOST_ID int not null,";
  query += "Primary Key(CAT_ID,HOST_ID))";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  /* Add user table */
  text  = "Adding User_Table to database";
  print(text);
  query  = "create table User_Table (USER_ID int auto_increment not null,";
  query += "USER_NAME varchar(20) not null,";
  query += "USER_PASS varchar(255) not null,";
  query += "Primary Key(USER_ID))";
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();
  
  FILE *fp;
  int status;
  char path[MAX];
  string adminpass;

  fp = popen("echo -n \"admin\" | md5sum| cut -d \\  -f 1" , "r");
  if (fp == NULL) {
    perror("popen failed");
  }
  while (fgets(path, MAX, fp) != NULL) {
    adminpass = path;
  }
  status = pclose(fp);
  adminpass.erase(remove(adminpass.begin(), adminpass.end(), '\n'), adminpass.end());
  
  /* Insert admin user record */
  text  = "Adding admin user to User_Table";
  print(text);
  query  = "insert into User_Table (USER_NAME,USER_PASS) values";
  query += "('admin','";
  query += adminpass;
  query += "')";
  
  try {
    stmt->execute(query);
    cout << "[" << greentext("OK") << "]";
    cout << "\n";
  }
  catch (sql::SQLException &e) {
    cout << "[" << redtext("Failed") << "]";
    cout << "\n";
    return EXIT_FAILURE;
  }
  query.clear();

  delete con;
}
