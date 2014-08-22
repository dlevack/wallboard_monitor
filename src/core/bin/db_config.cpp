#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/INIReader.h"

#define CONF_FILE "/opt/wallboard_monitor/conf_files/db.conf"
using namespace std;

string host;
string database;
string user;
string pass;
int option;

string strip(string in) {
  string final;
  for(int i = 0; i < in.length(); i++) {
    if(in[i] != '"') {
      final += in[i];
    }
  }
  return final;
}

int main(int argc, const char **argv) {
  INIReader reader(CONF_FILE);
  if (reader.ParseError() < 0) {
    cout << "Can't load 'db.conf'\n";
    return 1;
  }
  
  host     = strip(reader.Get("", "host", "UNKNOWN"));
  database = strip(reader.Get("", "name", "UNKNOWN"));
  user     = strip(reader.Get("", "user", "UNKNOWN"));
  pass     = strip(reader.Get("", "pass", "UNKNOWN"));
  
  while (option != 5) {
    system("clear");
    cout << "[1]     Host: " << host << "\n";
    cout << "[2] Database: " << database << "\n";
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
      cin  >> database;
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
  myfile << "name = \"" << database  << "\"\n";
  myfile << "user = \"" << user  << "\"\n";
  myfile << "pass = \"" << pass  << "\"\n";
  myfile.close();
  
  return 0;
}
