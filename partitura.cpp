#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp> // Makes life easier for Windows users compiling this.

#include <boost/scoped_ptr.hpp> // Used throughout Gosu and this tutorial.
#include <boost/shared_ptr.hpp> // Learn them, they're moving into standard C++!
#include <boost/lexical_cast.hpp> // Could also use <sstream>, just for int <-> string conversion
#include <boost/format.hpp>

#include <cmath>
#include <cstdlib>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>


#include "portaudio.h"

#ifdef STATIC_LINK

#include "pa_linux_alsa.h"
#include "src/common/pa_types.h"

#endif

#include "FFT.h"



#define AUDIO_ON

typedef int MY_TYPE;
#define TIPO paInt16;

class tipoBuffer{
public:
    tipoBuffer():pos(0){}
    int pos;
    float in[4096];
    float out[2048];
};

class GameWindow : public Gosu::Window
{
    Gosu::Image imagenR, imagenL, imagen3;
    Gosu::Font fuente;
    float mayores[5];

    std::map<double, std::string> notas;
    PaStream * stream;
    PaError err;
    bool silencio;
    
public:
    tipoBuffer miBuffer;
    std::ofstream outputLog;
    int numSamples;

    GameWindow()
	: Window(640, 480, false),
	  imagenR(graphics(), L"barra.png"),
	  imagenL(graphics(), L"barra.png"),
	  imagen3(graphics(), L"barra.png"),
	  fuente(graphics(), L"MusiQwik", 50),
	  silencio(false),
	  numSamples(2048)
	{

	    notas[523.25] = "Do 5";
	    notas[592.163] = "Re 5";
	    notas[656.763] = "Mi 5";
	    notas[699.829] = "Fa 5";
	    notas[785.692] = "Sol 5";
	    notas[893.628] = "La 5";
	    notas[1001.29] = "Si 5";
	    notas[1076.66] = "Do 6";
	    notas[1195.09] = "Re 6";

/*

	    notas["Do5"] = 523.25;
	    notas["Re5"] = 592.163;
	    notas["Mi5"] = 656.763;
	    notas["Fa5"] = 699.829;
	    notas["Sol5"] = 785.692;
	    notas["La5"] = 893.628;
	    notas["Si5"] = 1001.29;
	    notas["Do6"] = 106.66;
	    notas["Re6"] = 1195.09; //*/

	    //outputLog.open("lecturaFFT");

	    setCaption(L"oFlute");
	    std::wstring fichero = Gosu::sharedResourcePrefix();

#ifdef AUDIO_ON
	    PaStreamParameters inParameters, outParameters;

	    err = Pa_Initialize();
	    if(err != paNoError) std::cout << "ERROR: " << (int) err << std::endl;

/*	    PaAlsaStreamInfo info1;
	    PaAlsa_InitializeStreamInfo(&info1);  //*/

	    int numDevices;
	
	    numDevices = Pa_GetDeviceCount();
	    if( numDevices < 0 )
	    {
		std::cout << "ERROR: Pa_CountDevices returned 0x" << numDevices << std::endl;
		err = numDevices;
	    }

	    const   PaDeviceInfo *deviceInfo;

	    for( int i=0; i<numDevices; i++ )
	    {
		deviceInfo = Pa_GetDeviceInfo( i );
		std::cout << "Nombre: " << deviceInfo->name << std::endl
			  << "SampleRate:" << deviceInfo->defaultSampleRate << std::endl
			  << "MaxInputChannels: " << deviceInfo->maxInputChannels << std::endl << std::endl;
	    }
	

//*
	    outParameters.device = Pa_GetDefaultOutputDevice();
	    outParameters.channelCount = 2;
	    outParameters.sampleFormat = TIPO;
	    outParameters.hostApiSpecificStreamInfo = NULL;
	    outParameters.suggestedLatency = Pa_GetDeviceInfo( outParameters.device ) -> defaultLowOutputLatency; //*/

	    inParameters.device = Pa_GetDefaultInputDevice();
	    inParameters.channelCount = 2;
	    inParameters.sampleFormat = TIPO;
	    inParameters.hostApiSpecificStreamInfo = NULL;
	    inParameters.suggestedLatency = Pa_GetDeviceInfo( inParameters.device )->defaultLowInputLatency;

	    err = Pa_IsFormatSupported(&inParameters, &outParameters, 44100);
	
	    if(err != paNoError){
		std::cout << "ERROR: " << Pa_GetErrorText(err) << std::endl;
		exit(1);
	    }

	    err = Pa_OpenStream(
		&stream,
		&inParameters,
		NULL, // &outParameters,
		44100,
		256,
		paClipOff,
		updateBuffer,
		this);

	    std::cout << "* Duración del búffer: " << 256.0/44100.0*1000 << "ms" << std::endl;

#ifdef STATIC_LINK
	    std::cout << "SizeOf paInt16: " << sizeof(PaInt16) << std::endl;
	    PaAlsa_EnableRealtimeScheduling(stream, true);
#endif
	    if(err != paNoError) std::cout << "ERROR" << std::endl;
	    // controlAudio -> openStream(&outputParameters, &inputParameters, FORMAT,
	    // 			   44100, &framesDelBuffer, &(this->(*pointer)) );
#endif
	}

    ~GameWindow(){
	err = Pa_StopStream(stream);
	if(err != paNoError) std::cout << "ERROR" << std::endl;

	err = Pa_CloseStream(stream);
	if(err != paNoError) std::cout << "ERROR" << std::endl;

	err = Pa_Terminate();
	if(err != paNoError) std::cout << "ERROR" << std::endl;

	outputLog.close();

	std::cout << "Cerrando..." << std::endl;
    }

    void lanzarAudio(){
#ifdef AUDIO_ON
//	controlAudio -> startStream();
	err = Pa_StartStream(stream);
	if(err != paNoError) std::cout << "ERROR" << std::endl;
	std::cout << "UP and running" << std::endl;

	const PaStreamInfo * info = Pa_GetStreamInfo(stream);
	std::cout << "Input latency: " << info->inputLatency << std::endl
		  << "Output latency: " << info -> outputLatency << std::endl;
#endif
    }
    
#ifdef AUDIO_ON
    static int updateBuffer(const void * inB, 
			    void * outB, 
			    unsigned long nFrames, 
			    const PaStreamCallbackTimeInfo * timeInfo,
			    PaStreamCallbackFlags statusFlags,
			    void * data)
	{
	    //MY_TYPE * nOutB = (MY_TYPE *) outB;
	    const MY_TYPE * nInB = (const MY_TYPE *) inB;
	    GameWindow * puntero = (GameWindow *) data;
	    
/*	    double sumaR = 0, sumaL = 0;

	    for(unsigned int i = 0; i < nFrames; ++i){
	    sumaR += pow(*nOutB++ = *nInB++, 2);		
	    sumaL += pow(*nOutB++ = *nInB++, 2);		
	    }
	    // Marcamos 3000 como máximo 
	    puntero -> fR = sqrt(sumaR/nFrames) / 3000; // /32768.0 * 100;
	    puntero -> fL = sqrt(sumaL/nFrames) / 3000; // /32768.0 * 100; //*/

	    for(unsigned int i = 0; i < nFrames; i+=2){
		puntero->miBuffer.in[puntero->miBuffer.pos++] = *nInB++;
		nInB++;
		puntero->miBuffer.pos ++;
	    }
	    
	    if(puntero->miBuffer.pos > 4095){
		puntero->miBuffer.pos = 0;
		WindowFunc(3, 4096, puntero->miBuffer.in);
		PowerSpectrum(4096, puntero->miBuffer.in, puntero->miBuffer.out);
		float maxValue[] = {0,0,0};
		float maxPos[3],maxvalor=0;
		
		// Lo ponemos para que empiece a mirar frecuencias a partir de 450Hz
		// 
		for(int i = 450*2048/22050; i < 2048; ++i){
		    for (int j = 0; j < 3; j++)
		    {
			if(puntero->miBuffer.out[i] > maxValue[j]){
			    maxValue[j] = puntero->miBuffer.out[i];
			    maxPos[j] = i;
			    break;
			}
		    }			
		    if(i*22050/2048 > 1500) break;
		}
		
		std::cout << '\xd' << "Datos:" << std::setw(12) << maxPos[0]*22050/2048 
			  << std::setw(12) << maxPos[1]*22050/2048 
			  << std::setw(12) << maxPos[2]*22050/2048 
			  << std::setw(12) << maxValue[0]
			  << std::flush;		

		puntero -> mayores[0] = maxPos[0] * 22050 / 2048;
		puntero -> mayores[1] = maxPos[1] * 22050 / 2048;
		puntero -> mayores[2] = maxPos[2] * 22050 / 2048;
		//puntero->outputLog << maxPos << std::endl;

		puntero -> silencio = ((maxValue[0] < 1e+16)?true:false);
	    }

	    return paContinue;
	}
#endif
    void update()
	{
	}

    void draw()
	{

	    // fR y fL estarán entre 450 y 1500 que son las frecuencias que abarcamos
	    // el intervalo desplazado sería 0 - 1050
	    if(silencio) return;

	    imagenR.draw(50,
			 10 + 400 * ((mayores[0] - 450)/1050), // x, y
			 1, // Z
			 1, 0.05); // xscale, yscale

	    imagenR.draw(150,
			 10 + 400 * ((mayores[1] - 450)/1050), // x, y
			 1, // Z
			 1, 0.05); // xscale, yscaleç

	    imagenR.draw(250,
			 10 + 400 * ((mayores[2] - 450)/1050), // x, y
			 1, // Z
			 1, 0.05); // xscale, yscale

//	    fuente.draw(L"R: " + (boost::wformat(L"%-.2g") % (fR * 100)).str(), 10, 10, 1);
//	    fuente.draw(L"L: " + (boost::wformat(L"%-.2g") % (fL * 100)).str(), 10, 30, 1);
		  
	    fuente.draw(boost::lexical_cast<std::wstring>(asociarNota(mayores[0]).c_str()), 300, 30, 1);
	}
    

    std::string asociarNota(double frecuencia){
	std::map<double, std::string> diferencias;
	std::map<double, std::string>::iterator iter;
	for(iter = notas.begin();
	    iter != notas.end();
	    ++iter){
	    diferencias[abs(frecuencia - iter -> first)] = iter -> second;
	}

	iter = min_element(diferencias.begin(), diferencias.end());
	return iter -> second;
	
    }

    void buttonDown(Gosu::Button btn)
	{
	    if (btn == Gosu::kbEscape)
		close();
	}
};

int main(int argc, char* argv[])
{
    GameWindow window;
    window.lanzarAudio();
    window.show();

}
