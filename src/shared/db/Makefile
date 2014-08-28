CC = g++
SOURCES = wallboard_db.cpp

all: libwalldb.so.1.0

libwalldb.so.1.0: wallboard_db.cpp
	g++ -Wall -fPIC -c wallboard_db.cpp
	g++ -shared -Wl,-soname,libwalldb.so.1 -o libwalldb.so.1.0 wallboard_db.o

clean:
	rm -f *.o libwalldb.so.1.0
