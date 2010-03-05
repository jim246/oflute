CC=g++
CFLAGS=-Igosu `gosu/bin/gosu-config --cxxflags` -g -Itinyxml
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a -lportaudio #tinyxml/tinyxml.a -lboost_regex -g
OBJECTS=main.o estadoImagenFija.o estadoAutor.o estadoIntro.o \
	estadoMenu.o estadoAnalizador.o analizador.o FFT.o
EXE=programa

actual: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)


analizador.o: analizador.h
FFT.o: FFT.h

main.o: estado.h juego.h
estadoIntro.o: estadoIntro.h estado.h estadoImagenFija.h estadoImagenFija.o
estadoAutor.o: estadoAutor.h estado.h estadoImagenFija.h estadoImagenFija.o
estadoImagenFija.o: estadoImagenFija.h estado.h
estadoMenu.o: estado.h estadoMenu.h
estadoAnalizador.o: estado.h estadoAnalizador.h

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
