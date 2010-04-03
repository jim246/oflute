#include "analizador.h"
#include "FFT.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "colores.h"


using namespace std;

tipoBuffer Analizador::miBuffer;

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
//    PaStreamParameters inParameters, outParameters;

    cout << "*** [Analizador] Intentando Pa_Initialize... " << flush;
    err = Pa_Initialize();

    if(err != paNoError) std::cout << "ERROR: " << (int) err << std::endl;

    cout << "OK" << endl;

    cout << "*** [Analizador] Intentando Pa_OpenDefaultStream..." << flush;

    err = Pa_OpenDefaultStream(&stream,
			       2,
			       0,
			       paInt16,
			       44100,
			       256,
			       updateBuffer,
			       NULL);

    if(err != paNoError) std::cout << "ERROR" << std::endl;

    cout << "OK" << endl;

    std::cout << "* Duración del búffer: " << 256.0/44100.0*1000 << "ms" << std::endl;

    return true;
} 




bool Analizador::iniciarAnalisis(){
    cout << "### Analizador::iniciarAnalisis ###" << endl;
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

bool Analizador::detenerAnalisis(){
    if(iniciado){
	// Paramos el flujo
	err = Pa_StopStream(stream);
	if(err != paNoError)
	    cerr << "ERROR al detener el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

	cout << "----- Analizador: Flujo parado" << endl;

	// Cerramos el flujo
	err = Pa_CloseStream(stream);
	if(err != paNoError)
	    cerr << "ERROR al cerrar el flujo: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

	cout << "----- Analizador: Flujo cerrado" << endl;
	
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
    
//    EstadoAnalizador * puntero = (EstadoAnalizador*) data;
    const MY_TYPE * nInB = (const MY_TYPE *) inB;
	    
    for(unsigned int i = 0; i < nFrames; i+=2){
//	cout << "posBuffer: " << miBuffer.pos << endl;

	 miBuffer.in[ miBuffer.pos++] = *nInB++;
	nInB++;
	miBuffer.pos++;
    }

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


	 miBuffer . mayores[0] = maxPos[0] * 22050 / 2048;
	 miBuffer . mayores[1] = maxPos[1] * 22050 / 2048;
	 miBuffer . mayores[2] = maxPos[2] * 22050 / 2048;
	//outputLog << maxPos << std::endl;

	 miBuffer . silencio = ((maxValue[0] < 1e+16)?true:false);//*/
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

t_altura Analizador::notaActual(){
    return asociarNota(miBuffer . mayores[0]);
}

Analizador::~Analizador(){
    PaError err;
    cout << "--- [DESTRUCTOR] Analizador" << endl;

    detenerAnalisis();
    // Cerramos portaudio
    err = Pa_Terminate();
    if(err != paNoError)
	cerr << "ERROR al cerrar PortAudio: " << Pa_GetErrorText(err) << "(" << (int) err << ")" << endl;

    cout << "----- Analizador: PortAudio terminado" << endl;

    cout << "Borrando Analizador..." << endl;
}
