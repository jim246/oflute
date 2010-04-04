CC=g++
CFLAGS=-I. -Igosu `gosu/bin/gosu-config --cxxflags` -g -Itinyxml -ISDL_ttf
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a -lportaudiocpp -lSDL_ttf

#-lrt -lasound -ljack -lpthread portaudio/lib/.libs/libportaudio.a -g 
#tinyxml/tinyxml.a -lboost_regex -g

OBJECTS=main.o estadoAnalizador.o controlSonido.o analizador.o FFT.o


EXE=programa

actual: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)

m2: main2.o analizador.o controlSonido.o FFT.o
	$(CC) $? $(LDFLAGS) -o $(EXE)2

cdev: devs.o
	$(CC) $? $(LDFLAGS) -o exeDevs

csine: sine.o
	$(CC) $? $(LDFLAGS) -o exeSine

analizador.o: analizador.h analizador.cpp

FFT.o: FFT.h
estadoAnalizador.o: estadoAnalizador.h analizador.h
controlSonido.o: controlSonido.h

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) main2.o $(EXE) programa2
