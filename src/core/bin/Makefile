all: db_config

db_config: db_config.cpp
	g++ -Wall db_config.cpp -L/var/lib/jenkins/jobs/Wallboard/workspace/libs -lwallconf -o db_config

clean:
	rm -f db_config
