CC=g++
CFLAGS=-Igosu `gosu/bin/gosu-config --cxxflags` -g -Itinyxml
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a -lSDL_ttf
LDFLAGS+=tinyxml/tinyxml.o tinyxml/tinyxmlparser.o tinyxml/tinyxmlerror.o tinyxml/tinystr.o

OBJECTS=main.o

EXE=programa

all: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)

main.o: customFont.h texto.h leccion.h


.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
