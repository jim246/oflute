CC=g++
CFLAGS=-Igosu `gosu/bin/gosu-config --cxxflags`
LDFLAGS=-lrt -lasound -ljack -lpthread -Igosu `gosu/bin/gosu-config --libs --cxxflags` -lportaudio gosu/lib/libgosu.a
OBJECTS=FFT.o versionConGosu.o 
EXE=programa

actual: FFT.o versionConGosu.o
	$(CC) $? $(LDFLAGS) -o $(EXE)



FFT.o: FFT.cpp

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@


legacy:
	g++ FFT.cpp -c -o FFT.o 
	g++ -lrt -lasound -ljack -lpthread -Igosu \
	`gosu/bin/gosu-config --libs --cxxflags` \
	-o programa versionConGosu.cpp -lportaudio gosu/lib/libgosu.a FFT.o

clean:
	rm -rf $(OBJECTS) $(EXE)