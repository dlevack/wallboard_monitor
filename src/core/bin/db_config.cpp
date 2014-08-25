#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONF_FILE "/opt/wallboard_monitor/conf_files/db.conf"
using namespace std;

string host;
string name;
string user;
string pass;
int option;

string getwallhost();
string getwallname();
string getwalluser();
string getwallpass();

int main(int argc, const char **argv) {
  
  host     = getwallhost();
  name     = getwallname();
  user     = getwalluser();
  pass     = getwallpass();
  
  while (option != 5) {
    system("clear");
    cout << "[1]     Host: " << host << "\n";
    cout << "[2] Database: " << name << "\n";
    cout << "[3]     User: " << user << "\n";
    cout << "[4] Password: " << pass << "\n";
    cout << "[5] Quit\n";
    cout << "\n";
    cout << "Select config to change: ";
    cin >> option;
    if (option == 1) {
      cout << "Hostname: ";
      cin  >> host;
    }
    if (option == 2) {
      cout << "Database: ";
      cin  >> name;
    }
    if (option == 3) {
      cout << "Username: ";
      cin  >> user;
    }
    if (option == 4) {
      cout << "Password: ";
      cin  >> pass;
    }
  }
  
  ofstream myfile;
  myfile.open (CONF_FILE);
  myfile << "host = \"" << host  << "\"\n";
  myfile << "name = \"" << name  << "\"\n";
  myfile << "user = \"" << user  << "\"\n";
  myfile << "pass = \"" << pass  << "\"\n";
  myfile.close();
  
  return 0;
}
