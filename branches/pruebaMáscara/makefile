CC=g++
CFLAGS=-Igosu `gosu/bin/gosu-config --cxxflags` -g 
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a -lSDL_ttf

OBJECTS=main.o

EXE=programa



all: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
