CC = c++
CFLAGS = -L/var/lib/jenkins/jobs/Wallboard/workspace/libs -lwallconf -lmysqlcppconn
SOURCES = install_db.cpp
EXECUTABLE = install_db

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -f $(EXECUTABLE)
