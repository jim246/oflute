CC=g++
CFLAGS=-Igosu `gosu/bin/gosu-config --cxxflags` -g -Itinyxml
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a #tinyxml/tinyxml.a -lboost_regex -g
OBJECTS=main.o estado.o estadoImagenFija.o estadoAutor.o estadoIntro.o estadoMenu.o
EXE=programa

actual: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)


main.o estado.o: estado.h juego.h
estadoIntro.o: estadoIntro.h estado.h estadoImagenFija.h estadoImagenFija.o
estadoAutor.o: estadoAutor.h estado.h estadoImagenFija.h estadoImagenFija.o
estadoImagenFija.o: estadoImagenFija.h estado.h
estadoMenu.o: estado.h estadoMenu.h

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
