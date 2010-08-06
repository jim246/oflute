OBJDIR := obj
SRCDIR := src
INCDIR := include
DEPFILE := obj/dependencias.d

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

all: $(DEPFILE) $(OUTPUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling..." $(notdir $<)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)	
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


depend: $(DEPFILE)

$(DEPFILE): $(shell ls -t $(SRCDIR)/*.cpp) $(shell ls -t $(INCDIR)/*.h)
	gcc -MM $(CXXFLAGS) $(shell ls -t $(SRCDIR)/*.cpp) | sed 's/^\([a-zA-Z]\+.o\)/$(OBJDIR)\/\1/g' > $(DEPFILE)


-include $(DEPFILE)

clean:
	rm -rf $(OBJS) $(EXE) $(DEPFILE)
	make -C pugixml clean
	make -C kissfft clean


