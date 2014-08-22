#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "headers/INIReader.h"
#include <Magick++.h> 
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define CONF_FILE "/opt/wallboard_monitor/conf_files/db.conf"

using namespace std; 
using namespace Magick; 

string host;
string database;
string user;
string pass;

string strip(string in) {
  string final;
  for(int i = 0; i < in.length(); i++) {
    if(in[i] != '"') {
      final += in[i];
    }
  }
  return final;
}

int main(int argc,char **argv)  { 
  INIReader reader(CONF_FILE);

  if (reader.ParseError() < 0) {
    cout << "Can't load '" << CONF_FILE << "'\n";
    return 1;
  }

  host     = strip(reader.Get("", "host", "UNKNOWN"));
  database = strip(reader.Get("", "name", "UNKNOWN"));
  user     = strip(reader.Get("", "user", "UNKNOWN"));
  pass     = strip(reader.Get("", "pass", "UNKNOWN"));

  try { 
    sql::Connection *con;                         // Define connection handler
    sql::Statement *stmt;                         // Define statement handler
    sql::ResultSet  *res;                         // Define result object
    sql::Driver * driver = get_driver_instance(); // Defin driver for connection
    InitializeMagick(*argv);
    Image image;
    string color;
    string gradient;
    string radgradient;
    string imagefile;
    string imagepath = "/opt/wallboard_monitor/wallboard_web/images/";
    
    string db(argc > 1 ? argv[1] : database);     // Define db variable which will be either provided
                                                  // By command line or pulled from config file if not
                                                  // Provided on command line.

    con = driver->connect(host,                   // Connect to database host
                          user,
                          pass);
    con->setSchema(db);                           // Select database on host
    stmt = con->createStatement();

    res = stmt->executeQuery("SELECT STATUS_COLOR FROM Status_Table");
    while (res->next()) {
      color = res->getString("STATUS_COLOR");
      gradient  = "gradient:";
      gradient += color;
      gradient += "-black";
      
      radgradient  = "radial-gradient:";
      radgradient += color;
      radgradient += "-black";
      
      imagefile  = imagepath;
      imagefile += color;
      imagefile += "-bg.jpg";
      
      image.size("5x200");
      image.read(gradient);
      image.rotate(-90);
      image.write(imagefile);
      
      imagefile  = imagepath;
      imagefile += color;
      imagefile += "-bg2.jpg";

      image.size("5x200");
      image.read(gradient);
      image.rotate(90);
      image.write(imagefile);

      imagefile  = imagepath;
      imagefile += color;
      imagefile += ".png";
      
      image.size("25x25");
      image.read(radgradient);
      image.write(imagefile);
    }
    delete res;

    delete stmt;
    delete con;
  }
  catch( Exception &error_ ) { 
    cout << "Caught exception: " << error_.what() << endl; 
    return 1; 
  } 
  catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;

    return EXIT_FAILURE;
  }
  return 0; 
}
