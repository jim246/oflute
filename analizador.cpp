#include "analizador.h"
#include "FFT.h"

#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

Analizador::Analizador() : iniciado(false)
{
    notas[523.25] = Do5;
    notas[592.163] = Re5;
    notas[656.763] = Mi5;
    notas[699.829] = Fa5;
    notas[785.692] = Sol5;
    notas[893.628] = La5;
    notas[1001.29] = Si5;
    notas[1076.66] = Do6;
    notas[1195.09] = Re6;
}

bool Analizador::configurarFlujo(){
    if(iniciado) return false;
    iniciado = true;

    // Inicializamos PortAudio
    PaError err = Pa_Initialize();

    // Comprobamos que se ha inicialiazado
    if(err != paNoError){
	cerr << "ERROR: " 
	     << Pa_GetErrorText(err) 
	     << "(" << (int) err << ")" << endl;
	return false;
    }

    cout << "* PortAudio inicializado" << endl;

    // Listamos los dispositivos compatibles
    int numDevices;	
    numDevices = Pa_GetDeviceCount();

    // Comprobamos el número de dispositivos
    if( numDevices < 0 ){
	cerr << "ERROR en Pa_GetDeviceCount: " 
	     << Pa_GetErrorText(err) 
	     << "(" << (int) err << ")" << endl;
	return false;
    }

    /*
      const   PaDeviceInfo *deviceInfo;
      for( int i=0; i<numDevices; i++ )
      {
      deviceInfo = Pa_GetDeviceInfo( i );
      std::cout << "Nombre: " << deviceInfo->name << std::endl
      << "SampleRate:" << deviceInfo->defaultSampleRate << std::endl
      << "MaxInputChannels: " << deviceInfo->maxInputChannels << std::endl << std::endl;
      } //*/
    


    // Parámetros para el flujo de salida - NO UTILIZADO

    /*
      PaStreamParameters outParameters;
      outParameters.device = Pa_GetDefaultOutputDevice();
      outParameters.channelCount = 2;
      outParameters.sampleFormat = paInt16;
      outParameters.hostApiSpecificStreamInfo = NULL;
      outParameters.suggestedLatency = Pa_GetDeviceInfo( outParameters.device ) -> defaultLowOutputLatency; 
      // */

    // Parámetros para el flujo de entrada
    PaStreamParameters inParameters;

    // Dispositivo de entrada por defecto
    inParameters.device = Pa_GetDefaultInputDevice();

    // Entrada estéreo aunque el micrófono sea mono
    inParameters.channelCount = 2;

    // Tipo de datos para los samples
    inParameters.sampleFormat = paInt16;
    
    inParameters.hostApiSpecificStreamInfo = NULL;

    // Latencia, la menor posible
    inParameters.suggestedLatency = Pa_GetDeviceInfo( inParameters.device )->defaultLowInputLatency;

    // Comprobamos que el sistema acepta esta configuración
    err = Pa_IsFormatSupported(&inParameters, NULL, 44100);
	
    if(err != paNoError){
	cout << "ERROR en Pa_IsFormatSupported: " << Pa_GetErrorText(err) << std::endl;
	return false;
    }

    // Abrimos el flujo
    err = Pa_OpenStream(
	&stream,
	&inParameters,
	NULL, // &outParameters,
	44100, // Frecuencia de muestreo
	256, // Capacidad del buffer
	paClipOff,
	updateBuffer,
	this);
    
    std::cout << "* Duración del búffer: " << 256.0/44100.0*1000 << "ms" << std::endl;

    if(err != paNoError){
	cerr << "ERROR: " 
	     << Pa_GetErrorText(err) 
	     << "(" << (int) err << ")" << endl;
	return false;
    }

} //




bool Analizador::iniciarAnalisis(){
    if(!iniciado) return false;
    PaError err;
    // Hacemos andar el flujo
    err = Pa_StartStream(stream);

    // Comprobamos si hay errores
    if(err != paNoError){
	cerr << "ERROR al iniciar el flujo: " 
	     << Pa_GetErrorText(err) 
	     << "(" << (int) err << ")" << endl;
	return false;
    }

    cout << "* Flujo UP AND RUNNING" << endl;

    const PaStreamInfo * info = Pa_GetStreamInfo(stream);
    std::cout << "** Input latency: " << info->inputLatency << std::endl
	      << "** Output latency: " << info -> outputLatency << std::endl;
} // Fin de iniciarAnalisis

t_altura Analizador::notaActual(){
    if(!iniciado) return Silencio;
    if(mayores[0] == 0){
	return Silencio;
    }else{
	return asociarNota(mayores[0]);
    }
}


bool Analizador::detenerAnalisis(){
    if(iniciado){
	// Paramos el flujo
	PaError err = Pa_StopStream(stream);
	if(err != paNoError)
	    cerr << "ERROR al detener el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

	// Cerramos el flujo
	err = Pa_CloseStream(stream);
	if(err != paNoError)
	    cerr << "ERROR al cerrar el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

	iniciado = false;
    }
}


int Analizador::updateBuffer(const void * inB, 
			     void * outB, 
			     unsigned long nFrames, 
			     const PaStreamCallbackTimeInfo * timeInfo,
			     PaStreamCallbackFlags statusFlags,
			     void * data)
{

    const int * nInB = (const int *) inB;
    Analizador * puntero = (Analizador*) data;

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
	float maxPos[3];
		
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
	
	/*
	std::cout << '\xd' << "Datos:" << std::setw(12) << maxPos[0]*22050/2048 
		  << std::setw(12) << maxPos[1]*22050/2048 
		  << std::setw(12) << maxPos[2]*22050/2048 
		  << std::setw(12) << maxValue[0]
		  << std::flush;		
	//*/

	if( maxValue[0] < 1e+16){
	    puntero -> mayores[0] = 0;
	}else{
	    puntero -> mayores[0] = maxPos[0] * 22050 / 2048;
	    puntero -> mayores[1] = maxPos[1] * 22050 / 2048;
	    puntero -> mayores[2] = maxPos[2] * 22050 / 2048;
	}
	//puntero->outputLog << maxPos << std::endl;


	//
    }

    return paContinue;


}


t_altura Analizador::asociarNota(double frecuencia){
    std::map<double, t_altura> diferencias;
    std::map<double, t_altura>::iterator iter;

    for(iter = notas.begin();
	iter != notas.end();
	++iter)
    {
	diferencias[abs(frecuencia - iter -> first)] = iter -> second;
    }
    
    iter = min_element(diferencias.begin(), diferencias.end());
    return iter -> second;
    
}

Analizador::~Analizador(){
    PaError err;
    if(iniciado){
	// Paramos el flujo
	err = Pa_StopStream(stream);
	if(err != paNoError)
	    cerr << "ERROR al detener el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

	// Cerramos el flujo
	err = Pa_CloseStream(stream);
	if(err != paNoError)
	    cerr << "ERROR al cerrar el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

	iniciado = false;
    }

    // Cerramos portaudio
    err = Pa_Terminate();
    if(err != paNoError)
	cerr << "ERROR al cerrar PortAudio: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

    cout << "Borrando Analizador..." << endl;
}
