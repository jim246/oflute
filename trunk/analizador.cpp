#include "analizador.h"
#include "FFT.h"

#include <iostream>
#include <iomanip>

// Para usar abs
#include <cmath>

// Para usar min_element
#include <algorithm>
 
#include "configuracion.h"


using namespace std;

Analizador::Analizador() : iniciado(false){
    cout << "+++ [CONSTRUCTOR] Analizador" << endl;
    miBuffer = new tipoBuffer;

    lectorConfiguracion P;

    notas[523.25] = Do5;
    notas[592.163] = Re5;
    notas[656.763] = Mi5;
    notas[699.829] = Fa5;
    notas[785.692] = Sol5;
    notas[893.628] = La5;
    notas[1001.29] = Si5;
    notas[1076.66] = Do6;
    notas[1195.09] = Re6;

    /*
      Definimos dos constantes para hacer las conversiones desde 
      posición del vector a frecuencia y viceversa
    
    */
      
    //Para pasar de pos de vector a frecuencia, multiplicamos por 22050/2048
    int_to_hz = 22050./2048.; // ~ 10.76660156250000000000000

    // PAra pasar de frecuencia a posición de vector, multiplicamos por 2048/22050
    hz_to_int = 2048./22050.; // ~ 0.928798185941043083900226

}


int Analizador::funcionCallback(const void * inputBuffer, 
				void * outputBuffer, 
				unsigned long framesPerBuffer, 
				const PaStreamCallbackTimeInfo * timeInfo,
				PaStreamCallbackFlags statusFlags){

    if(!iniciado){
	cout << "### Analizador::Callback llamado por primera vez" << endl;
	iniciado = true;
    }
    const int **nInB = (const int **)(inputBuffer);
    //

    /*   
    // ######################
    // Paso transparente de input a output
    // Para pruebas.

    int **out = static_cast<int **>(outputBuffer);
    
    for (unsigned int i = 0; i < framesPerBuffer; ++i)
    {
    out[0][i] = nInB[0][i];
    out[1][i] = nInB[1][i];
    }
    
    //*/
	    

    for (unsigned int i = 0; i < framesPerBuffer; i++){
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

	/*
	  En el vector devuelto por la función de la FFT, cada posición i 
	  representa la amplitud de la componente con frecuencia i.
	  
	  Realmente i no es directamente la frecuencia. Para conocer la frecuencia 
	  real, hacemos una regla de tres: Si 2048 (el máximo del vector) es 22050 (la mayor frecuencia que se puede captar)
	  entonces i es x.

	  En nuestro caso, comenzamos el análisis en 450Hz, que es el límite
	  inferior que hemos seleccionado empíricamente.
	  22050 => 2048
	  450   => x
	  x = 450*2048/22050 = 41.79591 ~ 41

	*/
	  

	for(int i = 41; i < 2048; ++i){
	    for (int j = 0; j < 3; j++)
	    {
		if( miBuffer -> out[i] > maxValue[j]){
		    maxValue[j] =  miBuffer -> out[i];
		    maxPos[j] = i;
		    break;
		}
	    }			
	    
	    /*
	      Hemos seleccionado como límite superior 1500Hz
	      22050 => 2048
	      x     => i
	      x = i * 22050 / 2048 = i * 10.766
	    */

	    if(i * int_to_hz > 1500.) break;
	}

	miBuffer -> mayores[0] = maxPos[0]  * int_to_hz;
	miBuffer -> mayores[1] = maxPos[1]  * int_to_hz;
	miBuffer -> mayores[2] = maxPos[2]  * int_to_hz;

		
	std::cout << '\xd' << "Datos:" 
		  << std::setw(12) << miBuffer -> mayores[0] 
		  << std::setw(12) << miBuffer -> mayores[1]  
		  << std::setw(12) << miBuffer -> mayores[2]  
		  << std::setw(12) << maxValue[0]
		  << std::flush;	//



	//outputLog << maxPos << std::endl;

	miBuffer -> silencio = ((maxValue[0] < 1e+18)?true:false);
    } //*/

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
