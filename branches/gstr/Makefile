CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall
CXXFLAGS  += `pkg-config --cflags gstreamermm-0.10`

LDFLAGS   := -Wall
LIBS      := `pkg-config --libs gstreamermm-0.10`

OUTPUT += programa

all: $(OUTPUT)

SRCS += main.cpp

OBJS += $(addsuffix .o,$(basename $(SRCS)))

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) -o $@ $^

$(OUTPUTLIB): $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf

