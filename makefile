CC=g++
CFLAGS=-Igosu `gosu/bin/gosu-config --cxxflags` -g 
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a -lSDL_ttf

OBJECTS=main.o

EXE=programa

all: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)

d: prueba.o
	$(CC) $? $(LDFLAGS) -o $@
main.o: customFont.h texto.h


.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
