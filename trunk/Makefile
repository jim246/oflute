OBJDIR := obj
SRCDIR := src
INCDIR := include

CC       := g++
CXXFLAGS += -I. -I$(INCDIR)
CXXFLAGS += -Igosu `gosu/bin/gosu-config --cxxflags`
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

OUTPUT += oflute

SRCS := $(notdir $(shell ls -t $(SRCDIR)/*.cpp))

OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))

all: $(OUTPUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling..." $(notdir $<)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)	
	echo $(OBJS)
	@echo "Compiling pugixml..."
	@make -C pugixml
	@echo "Compiling kissfft..."
	@make -C kissfft
	@echo "Linking binary..."
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
	@echo "Done."

libgosu:
	cd gosu/linux ; make clean ; ./configure && make

regosu:
	make -C gosu/linux

$(OBJDIR)/FFT.o: $(INCDIR)/FFT.h
$(OBJDIR)/juego.o: $(INCDIR)/juego.h $(INCDIR)/estadoAnalizador.h $(INCDIR)/estadoCalibrarMicro.h $(INCDIR)/estadoLecciones.h $(INCDIR)/estadoMenuCanciones.h $(INCDIR)/estadoMenu.h $(INCDIR)/estado.h
$(OBJDIR)/main.o: $(INCDIR)/estado.h $(INCDIR)/juego.h $(INCDIR)/global.h
$(OBJDIR)/estado.o: $(INCDIR)/estado.h
$(OBJDIR)/log.o: $(INCDIR)/log.h
$(OBJDIR)/estadoImagenFija.o: $(INCDIR)/estadoImagenFija.h $(INCDIR)/estado.h $(INCDIR)/juego.h
$(OBJDIR)/estadoMenu.o: $(INCDIR)/estado.h $(INCDIR)/estadoMenu.h $(INCDIR)/juego.h $(INCDIR)/customFont.h $(INCDIR)/animacion.h $(INCDIR)/botonMenu.h
$(OBJDIR)/estadoAnalizador.o: $(INCDIR)/estado.h $(INCDIR)/estadoAnalizador.h $(INCDIR)/juego.h $(INCDIR)/analizador.h $(INCDIR)/controlSonido.h $(INCDIR)/analizadorProxy.h
$(OBJDIR)/texto.o: $(INCDIR)/texto.h
$(OBJDIR)/controlSonido.o: $(INCDIR)/controlSonido.h
$(OBJDIR)/animacion.o:$(INCDIR)/animacion.h
$(OBJDIR)/ecuaciones.o:$(INCDIR)/animacion.h
$(OBJDIR)/estadoLecciones.o: $(INCDIR)/estadoLecciones.h $(INCDIR)/elementosInterfaz.h $(INCDIR)/leccion.h
$(OBJDIR)/elementosInterfaz.o: $(INCDIR)/elementosInterfaz.h $(INCDIR)/texto.h
$(OBJDIR)/elementosInterfaz_imagen.o: $(INCDIR)/elementosInterfaz.h
$(OBJDIR)/elementosInterfaz_texto.o: $(INCDIR)/elementosInterfaz.h $(INCDIR)/texto.h
$(OBJDIR)/elementosInterfaz_combinado.o: $(INCDIR)/elementosInterfaz.h $(INCDIR)/texto.h
$(OBJDIR)/estadoMenuCanciones.o: $(INCDIR)/estadoMenuCanciones.h $(INCDIR)/estado.h $(INCDIR)/juego.h $(INCDIR)/estadoCancion.h
$(OBJDIR)/estadoCancion.o: $(INCDIR)/estadoCancion.h $(INCDIR)/estado.h $(INCDIR)/juego.h $(INCDIR)/nota.h $(INCDIR)/claseTimer.h $(INCDIR)/particulas.h $(INCDIR)/analizador.h $(INCDIR)/analizadorProxy.h
$(OBJDIR)/global.o: $(INCDIR)/global.h
$(OBJDIR)/estadoCalibrarMicro.o: $(INCDIR)/estadoCalibrarMicro.h $(INCDIR)/estado.h $(INCDIR)/elementosInterfaz.h $(INCDIR)/log.h $(INCDIR)/juego.h $(INCDIR)/configuracion.h
$(OBJDIR)/nota.o:$(INCDIR)/nota.h $(INCDIR)/global.h
$(OBJDIR)/analizadorProxy.o: $(INCDIR)/analizadorProxy.h
$(OBJDIR)/analizador.o: $(INCDIR)/analizador.h $(INCDIR)/configuracion.h $(INCDIR)/analizadorProxy.h $(INCDIR)/log.h

.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
	make -C pugixml clean
	make -C kissfft clean

