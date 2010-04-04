#include "analizador.h"
#include "FFT.h"

#include <iostream>
#include <iomanip>

// Para usar abs
#include <cmath>

// Para usar min_element
#include <algorithm>
 


using namespace std;

Analizador::Analizador(){
    cout << "+++ [CONSTRUCTOR] Analizador" << endl;
    miBuffer = new tipoBuffer;

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


int Analizador::funcionCallback(const void * inputBuffer, 
				void * outputBuffer, 
				unsigned long framesPerBuffer, 
				const PaStreamCallbackTimeInfo * timeInfo,
				PaStreamCallbackFlags statusFlags){


    const int **nInB = (const int **)(inputBuffer);
    //int **out = static_cast<int **>(outputBuffer);

    /*
    // ######################
    // Paso transparente de input a output
    // Para pruebas.

    for (unsigned int i = 0; i < framesPerBuffer; ++i)
    {
    out[0][i] = in[0][i];
    out[1][i] = in[1][i];
    }
    
    */
	    

    for (unsigned int i = 0; i < framesPerBuffer; ++i){
//    for(unsigned int i = 0; i < nFrames; i+=2){
//	cout << "posBuffer: " << miBuffer.pos << endl;

	// in[0][i] es el sonido en el canal izquierdo
	// in[1][i] es el sonido en el canal derecho

	miBuffer -> in[ miBuffer -> pos++] = nInB[0][i];
    }

    if( miBuffer -> pos > 4095){
	miBuffer -> pos = 0; 
	WindowFunc(3, 4096,  miBuffer -> in);
	PowerSpectrum(4096,  miBuffer -> in,  miBuffer -> out);
	float maxValue[] = {0,0,0};
	float maxPos[3];
		
	// Lo ponemos para que empiece a mirar frecuencias a partir de 450Hz
	// 
	for(int i = 450*2048/22050; i < 2048; ++i){
	    for (int j = 0; j < 3; j++)
	    {
		if( miBuffer -> out[i] > maxValue[j]){
		    maxValue[j] =  miBuffer -> out[i];
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


	miBuffer -> mayores[0] = maxPos[0] * 22050 / 2048;
	miBuffer -> mayores[1] = maxPos[1] * 22050 / 2048;
	miBuffer -> mayores[2] = maxPos[2] * 22050 / 2048;
	//outputLog << maxPos << std::endl;

	miBuffer -> silencio = ((maxValue[0] < 1e+16)?true:false);
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

t_altura Analizador::notaActual(){
//    cout << "Analizador::notaActual" << endl;
    return asociarNota(miBuffer -> mayores[0]);
}


Analizador::~Analizador(){
    delete miBuffer;
    miBuffer = NULL;
}
