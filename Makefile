CC=g++
CXXFLAGS+=-I. -Igosu `gosu/bin/gosu-config --cxxflags` -ISDL_ttf
CXXFLAGS+=-g #-Wall -Wextra

LDFLAGS+=`gosu/bin/gosu-config --libs --cxxflags` 

LDLIBS+=gosu/lib/libgosu.a -lportaudiocpp 
LDLIBS+=-lSDL_ttf



#tinyxml/tinyxml.a -lboost_regex -g

OBJECTS=main.o juego.o estadoImagenFija.o \
	estadoMenu.o FFT.o analizador.o controlSonido.o estadoAnalizador.o colores.o animacion.o

EXE=programa

all: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $(EXE) $(LDLIBS)


analizador.o: analizador.h
FFT.o: FFT.h
juego.o: juego.h
main.o: estado.h juego.h
estadoImagenFija.o: estadoImagenFija.h estado.h juego.h
estadoMenu.o: estado.h estadoMenu.h juego.h customFont.h animacion.h botonMenu.h
estadoAnalizador.o: estado.h estadoAnalizador.h juego.h analizador.h controlSonido.h

controlSonido.o: controlSonido.h
animacion.o:animacion.h

colores.o: colores.h

.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
