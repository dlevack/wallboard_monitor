#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

string host;
string name;
string user;
string pass;
string color;
string getwallhost();
string getwallname();
string getwalluser();
string getwallpass();

sql::Connection *con;                         // Define connection handler
sql::Statement *stmt;                         // Define statement handler
sql::ResultSet  *res;                         // Define result object
sql::Driver * driver = get_driver_instance(); // Defin driver for connection

void get_config() {
  host = getwallhost();
  name = getwallname();
  user = getwalluser();
  pass = getwallpass();
}

void db_connect() {
  get_config();
  con = driver->connect(host,                   // Connect to database host
                        user,
                        pass);
  con->setSchema(name);                           // Select database on host
  stmt = con->createStatement();
}

void db_close() {
  delete res;
  delete stmt;
  delete con;
}

int count_colors() {
  int countcolors = 0;
  db_connect();

  res = stmt->executeQuery("SELECT count(STATUS_COLOR) as count FROM Status_Table");
  while (res->next()) {
    countcolors = res->getInt("count");
  }
  db_close();
  return countcolors;
}

string* get_color_list()  {
  int count = count_colors();
  string* colors = new string[count];
  db_connect();

  res = stmt->executeQuery("SELECT STATUS_COLOR FROM Status_Table");
  int i = 0;
  while (res->next()) {
    color = res->getString("STATUS_COLOR");
    colors[i] = color;
    i++;
  }
  db_close();
  return colors;
}

string get_color_from_status(string status) {
  string color;
  db_connect();

  string query;
  query  = "select STATUS_COLOR from Status_Table where STATUS_NAME='";
  query += status;
  query += "'";
  res = stmt->executeQuery(query);
  while (res->next()) {
    color = res->getString("STATUS_COLOR");
  }
  db_close();
  return color;
}
