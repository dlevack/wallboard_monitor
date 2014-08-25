#include <iostream>
#include "headers/INIReader.h"
using namespace std;

string h;
string n;
string u;
string p;

INIReader reader("/opt/wallboard_monitor/conf_files/db.conf");

string strip(string in) {
  string final;
  for(int i = 0; i < in.length(); i++) {
    if(in[i] != '"') {
      final += in[i];
    }
  }
  return final;
}

string getwallhost() {
  h = strip(reader.Get("", "host", "UNKNOWN"));
  return h;
}

string getwallname() {
  n = strip(reader.Get("", "name", "UNKNOWN"));
  return n;
}

string getwalluser() {
  u = strip(reader.Get("", "user", "UNKNOWN"));
  return u;
}

string getwallpass() {
  p = strip(reader.Get("", "pass", "UNKNOWN"));
  return p;
}
