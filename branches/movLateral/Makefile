CC=g++
CFLAGS=-Igosu `gosu/bin/gosu-config --cxxflags` -g -Itinyxml
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a tinyxml/tinyxml.a -lboost_regex -g
OBJECTS=pruebaAlpha.o cancion.o nota.o
EXE=programa

actual: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)


nota.o cancion.o: cancion.h nota.h

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -rf $(OBJECTS) $(EXE)
