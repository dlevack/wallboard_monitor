CC = g++
SOURCES = ini.cpp INIReader.cpp wallboard_config.cpp

all: libwallconf.so.1.0

libwallconf.so.1.0: ini.cpp INIReader.cpp wallboard_config.cpp
	g++ -Wall -fPIC -c ini.cpp INIReader.cpp wallboard_config.cpp
	g++ -shared -Wl,-soname,libwallconf.so.1 -o libwallconf.so.1.0 ini.o INIReader.o wallboard_config.o

clean:
	rm -f *.o libwallconf.so.1.0
