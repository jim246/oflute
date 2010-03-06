#include "estadoAnalizador.h"

#include <iostream>
#include <cmath>

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>


#include "FFT.h"

using namespace std;


typedef int MY_TYPE;
#define TIPO paInt16;

tipoBuffer estadoAnalizador::miBuffer;

//int posFinalesY[] = {281, 333, 386, 441, 494 };
estadoAnalizador::estadoAnalizador (Juego * p) : estado(p), numSamples(2048){
    cout << "estadoAnalizador::CONSTRUCTOR" << endl;
    lanzado = true;    
    lanzar();
    miBuffer.pos = 0;

}

void estadoAnalizador::lanzar(){
    cout << "* estadoAnalizador lanzado" << endl;
    lanzado = true;

    if (!configurarFlujo()){
	cout << "*** Error al configurar el flujo." << endl;
    }

    if(!iniciarAnalisis()){
	cout << "*** Error al iniciar el análisis." << endl;
    }//*/
}

void estadoAnalizador::update(){
    if(!lanzado) 
	lanzar();
}

void estadoAnalizador::draw(){
    if(!lanzado) 
	return;
}

void estadoAnalizador::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    if (boton == Gosu::kbEscape){
	padre -> close();
    }
}

estadoAnalizador::~estadoAnalizador(){
    cout << "estadoAnalizador::~estadoAnalizador()" << endl;
}

bool estadoAnalizador::configurarFlujo(){
//    PaStreamParameters inParameters, outParameters;

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

bool estadoAnalizador::iniciarAnalisis(){
    cout << "### estadoAnalizador::iniciarAnalisis ###" << endl;
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

bool estadoAnalizador::detenerAnalisis(){
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


int estadoAnalizador::updateBuffer(const void * inB, 
			     void * outB, 
			     unsigned long nFrames, 
			     const PaStreamCallbackTimeInfo * timeInfo,
			     PaStreamCallbackFlags statusFlags,
			     void * data)
{
    
    estadoAnalizador * puntero = (estadoAnalizador*) data;
    const MY_TYPE * nInB = (const MY_TYPE *) inB;
	    
    for(unsigned int i = 0; i < nFrames; i+=2){
//	cout << "posBuffer: " << miBuffer.pos << endl;

	 miBuffer.in[ miBuffer.pos++] = *nInB++;
	nInB++;
	miBuffer.pos++;
    }

/*
    if( miBuffer.pos > 4095){
	 miBuffer.pos = 0;
    }//*/

    if( miBuffer.pos > 4095){
	 miBuffer.pos = 0; 
	WindowFunc(3, 4096,  miBuffer.in);
	PowerSpectrum(4096,  miBuffer.in,  miBuffer.out);
	float maxValue[] = {0,0,0};
	float maxPos[3];
		
	// Lo ponemos para que empiece a mirar frecuencias a partir de 450Hz
	// 
	for(int i = 450*2048/22050; i < 2048; ++i){
	    for (int j = 0; j < 3; j++)
	    {
		if( miBuffer.out[i] > maxValue[j]){
		    maxValue[j] =  miBuffer.out[i];
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

/*
	 puntero -> mayores[0] = maxPos[0] * 22050 / 2048;
	 puntero -> mayores[1] = maxPos[1] * 22050 / 2048;
	 puntero -> mayores[2] = maxPos[2] * 22050 / 2048;
	//outputLog << maxPos << std::endl;

	 puntero -> silencio = ((maxValue[0] < 1e+16)?true:false);//*/
    }//*/

    return paContinue;

}


//t_altura estadoAnalizador::asociarNota(double frecuencia){
/*    std::map<double, t_altura> diferencias;
    std::map<double, t_altura>::iterator iter;

    for(iter = notas.begin();
	iter != notas.end();
	++iter)
    {
	diferencias[abs(frecuencia - iter -> first)] = iter -> second;
    }
    
    iter = min_element(diferencias.begin(), diferencias.end());
    return iter -> second;//*/
    
//}
