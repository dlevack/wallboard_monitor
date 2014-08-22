CC = g++
CFLAGS = -c
LDFLAGS = 
SOURCES = ini.cpp INIReader.cpp db_config.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = db_config

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
