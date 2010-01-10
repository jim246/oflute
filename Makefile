all: actual

actual:
	g++ FFT.cpp -c -o FFT.o 
	g++ -lrt -lasound -ljack -lpthread -Igosu \
	`gosu/bin/gosu-config --libs --cxxflags` \
	-o programa versionConGosu.cpp -lportaudio gosu/lib/libgosu.a FFT.o

