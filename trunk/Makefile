CC=g++
CXXFLAGS += -I. -Igosu `gosu/bin/gosu-config --cxxflags`
CXXFLAGS += -Ipugixml -Ikissfft
CXXFLAGS += -g -Wall
CXXFLAGS += `pkg-config --cflags libpulse-simple`

LDFLAGS += `gosu/bin/gosu-config --libs --cxxflags` 
LDFLAGS += `pkg-config --libs libpulse-simple`

LDLIBS += gosu/lib/libgosu.a
LDLIBS += -lSDL_ttf
LDLIBS += -lboost_filesystem
LDLIBS += -lboost_regex
LDLIBS += -lboost_thread
LDLIBS += pugixml/pugixml.a
LDLIBS += kissfft/kissfft.a

OBJECTS += main.o juego.o estado.o estadoImagenFija.o
OBJECTS += estadoMenu.o FFT.o
OBJECTS += estadoAnalizador.o animacion.o ecuaciones.o
OBJECTS += estadoLecciones.o log.o
OBJECTS += texto.o elementosInterfaz.o
OBJECTS += elementosInterfaz_imagen.o elementosInterfaz_texto.o elementosInterfaz_combinado.o
OBJECTS += estadoCancion.o estadoMenuCanciones.o
OBJECTS += estadoCalibrarMicro.o 
OBJECTS += analizadorProxy.o analizador.o
OBJECTS += global.o

EXE=oflute

all: $(EXE)

$(EXE): $(OBJECTS)
	make -C pugixml
	make -C kissfft
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXE) $(LDLIBS)

libgosu:
	cd gosu/linux ; make clean ; ./configure && make

regosu:
	make -C gosu/linux

FFT.o: FFT.h
juego.o: juego.h
main.o: estado.h juego.h global.h
estado.o: estado.h
log.o: log.h
estadoImagenFija.o: estadoImagenFija.h estado.h juego.h
estadoMenu.o: estado.h estadoMenu.h juego.h customFont.h animacion.h botonMenu.h
estadoAnalizador.o: estado.h estadoAnalizador.h juego.h analizador.h controlSonido.h analizadorProxy.h
texto.o: texto.h
controlSonido.o: controlSonido.h
animacion.o:animacion.h
ecuaciones.o:animacion.h
estadoLecciones.o: estadoLecciones.h elementosInterfaz.h leccion.h
elementosInterfaz.o: elementosInterfaz.h texto.h
elementosInterfaz_imagen.o: elementosInterfaz.h
elementosInterfaz_texto.o: elementosInterfaz.h texto.h
elementosInterfaz_combinado.o: elementosInterfaz.h texto.h
estadoMenuCanciones.o: estadoMenuCanciones.h estado.h juego.h estadoCancion.h
estadoCancion.o: estadoCancion.h estado.h juego.h nota.h claseTimer.h
global.o: global.h
estadoCalibrarMicro.o: estadoCalibrarMicro.h estado.h elementosInterfaz.h log.h juego.h configuracion.h

analizadorProxy.o: analizadorProxy.h
analizador.o: analizador.h configuracion.h analizadorProxy.h log.h

.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
	make -C pugixml clean
	make -C kissfft clean

