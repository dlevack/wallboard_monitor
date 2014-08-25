CC = c++
CFLAGS = -O2 `Magick++-config --cppflags --cxxflags --ldflags --libs` -lwallconf -lmysqlcppconn
SOURCES = gen_wallboard_images.cpp
EXECUTABLE = gen_wallboard_images

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -f $(EXECUTABLE)
