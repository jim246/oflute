#include "analizador.h"
#include "FFT.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "colores.h"


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
    PaStreamParameters inParameters, outParameters;

    err = Pa_Initialize();

    if(err != paNoError) std::cout << "ERROR: " << (int) err << std::endl;

    err = Pa_OpenDefaultStream(&stream,
			       2,
			       0,
			       paInt16,
			       44100,
			       256,
			       updateBuffer,
			       (void*) this);

    std::cout << "* Duración del búffer: " << 256.0/44100.0*1000 << "ms" << std::endl;

    if(err != paNoError) std::cout << "ERROR" << std::endl;

    return true;
} 




bool Analizador::iniciarAnalisis(){
    cout << Colores::Rojo + "### Analizador::iniciarAnalisis ###" + Colores::Reset << endl;
    err = Pa_StartStream(stream);
    if(err != paNoError){
	std::cout << "ERROR" << std::endl;
	return false;
    }
    std::cout << "UP and running" << std::endl;
    
    const PaStreamInfo * info = Pa_GetStreamInfo(stream);
    std::cout << "Input latency: " << info->inputLatency << std::endl
	      << "Output latency: " << info -> outputLatency << std::endl;

    return true;
} // Fin de iniciarAnalisis

t_altura Analizador::notaActual(){
    if(!iniciado) return Silencio;
    return Do5;
}


bool Analizador::detenerAnalisis(){
    if(iniciado){
	// Paramos el flujo
	PaError err = Pa_StopStream(stream);
	if(err != paNoError){
	    cerr << "ERROR al detener el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;
	    return false;
	}

	// Cerramos el flujo
	err = Pa_CloseStream(stream);
	if(err != paNoError){
	    cerr << "ERROR al cerrar el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;
	    return false;
	}

	iniciado = false;
    }

    return true;
}


int Analizador::updateBuffer(const void * inB, 
			     void * outB, 
			     unsigned long nFrames, 
			     const PaStreamCallbackTimeInfo * timeInfo,
			     PaStreamCallbackFlags statusFlags,
			     void * data)
{
    
    Analizador * puntero = (Analizador*) data;

    return puntero -> updateBuffer2(inB, outB, nFrames, timeInfo, statusFlags);
}

int Analizador::updateBuffer2(const void * inB, 
			     void * outB, 
			     unsigned long nFrames, 
			     const PaStreamCallbackTimeInfo * timeInfo,
			     PaStreamCallbackFlags statusFlags)
{
    const MY_TYPE * nInB = (const MY_TYPE *) inB;
	    
    /*	
	double sumaR = 0, sumaL = 0;

	for(unsigned int i = 0; i < nFrames; ++i){
	sumaR += pow(*nOutB++ = *nInB++, 2);		
	sumaL += pow(*nOutB++ = *nInB++, 2);		
	}
	// Marcamos 3000 como máximo 
	puntero -> fR = sqrt(sumaR/nFrames) / 3000; // /32768.0 * 100;
	puntero -> fL = sqrt(sumaL/nFrames) / 3000; // /32768.0 * 100; //*/
    
//    cout << miBuffer.pos << endl;
    
    for(unsigned int i = 0; i < nFrames; i+=2){
	miBuffer.in[miBuffer.pos++] = *nInB++;
	nInB++;
	miBuffer.pos ++;
    }
   
    if(miBuffer.pos > 4095){
	WindowFunc(3, 4096, miBuffer.in);
	PowerSpectrum(4096, miBuffer.in, miBuffer.out);
	float maxValue[] = {0,0,0};
	float maxPos[3];
		
	// Lo ponemos para que empiece a mirar frecuencias a partir de 450Hz
	// 
	for(int i = 450*2048/22050; i < 2048; ++i){
	    for (int j = 0; j < 3; j++)
	    {
		if(miBuffer.out[i] > maxValue[j]){
		    maxValue[j] = miBuffer.out[i];
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
		  << std::flush;	//

	 mayores[0] = maxPos[0] * 22050 / 2048;
	 mayores[1] = maxPos[1] * 22050 / 2048;
	 mayores[2] = maxPos[2] * 22050 / 2048;
	//outputLog << maxPos << std::endl;

	silencio = ((maxValue[0] < 1e+16)?true:false);
    }//*/

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
