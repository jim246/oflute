CC=g++
CXXFLAGS+=-I. -Igosu `gosu/bin/gosu-config --cxxflags`
CXXFLAGS+=-Itinyxml
CXXFLAGS+=-g #-Wall -Wextra

LDFLAGS+=`gosu/bin/gosu-config --libs --cxxflags` 

LDLIBS+=gosu/lib/libgosu.a -lportaudiocpp 
LDLIBS+=-lSDL_ttf
LDLIBS+=-lboost_filesystem
LDLIBS+=tinyxml/tinylib.a

OBJECTS+=main.o juego.o estado.o estadoImagenFija.o
OBJECTS+=estadoMenu.o FFT.o analizador.o controlSonido.o 
OBJECTS+=estadoAnalizador.o animacion.o ecuaciones.o
OBJECTS+=estadoLecciones.o log.o
OBJECTS+=texto.o

EXE=programa

all: $(OBJECTS)
	cd tinyxml; $(MAKE)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXE) $(LDLIBS)

analizador.o: analizador.h
FFT.o: FFT.h
juego.o: juego.h
main.o: estado.h juego.h
estado.o: estado.h
log.o: log.h
estadoImagenFija.o: estadoImagenFija.h estado.h juego.h
estadoMenu.o: estado.h estadoMenu.h juego.h customFont.h animacion.h botonMenu.h
estadoAnalizador.o: estado.h estadoAnalizador.h juego.h analizador.h controlSonido.h
texto.o: texto.h
controlSonido.o: controlSonido.h
animacion.o:animacion.h
ecuaciones.o:animacion.h
estadoLecciones.o: estadoLecciones.h elementosInterfaz.h

.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
	cd tinyxml; $(MAKE) clean
