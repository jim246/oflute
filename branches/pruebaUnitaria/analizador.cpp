#include "analizador.h"
#include "FFT.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

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

    portaudio::System &sys = portaudio::System::instance();

    std::cout << "PortAudio version number = " << sys.version() << std::endl;
    std::cout << "PortAudio version text = '" << sys.versionText() << "'" << std::endl;

    portaudio::DirectionSpecificStreamParameters paramSalida(
	sys.defaultInputDevice(),  // dispositivo
	2, // número de canales
	portaudio::INT16, // formato
	false, // entrelazado
	sys.defaultInputDevice().defaultLowInputLatency(), // latencia sugerida
	NULL);

    portaudio::StreamParameters parametros(
	paramSalida,
	portaudio::DirectionSpecificStreamParameters::null(),
	44100.0,
	256,
	paClipOff);

    flujo.open(parametros, *this);

    return true;
} 




bool Analizador::iniciarAnalisis(){
    cout << "### Analizador::iniciarAnalisis ###" << endl;

    flujo.start();

    std::cout << "UP and running" << std::endl;
    

    return true;
} // Fin de iniciarAnalisis

bool Analizador::detenerAnalisis(){
    try{
    if(iniciado){
	// Paramos el flujo
	flujo.stop();
	flujo.close();
    }

    portaudio::System::instance().terminate();
    
//    return true;
}
	catch (const portaudio::PaException &e)
	{
		std::cout << "A PortAudio error occured: " << e.paErrorText() << std::endl;
	}
	catch (const portaudio::PaCppException &e)
	{
		std::cout << "A PortAudioCpp error occured: " << e.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "A generic exception occured: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "An unknown exception occured." << std::endl;
	}

    return true;
}


int Analizador::paCallbackFun(const void * inB, 
			     void * outB, 
			     unsigned long nFrames, 
			     const PaStreamCallbackTimeInfo * timeInfo,
			      PaStreamCallbackFlags statusFlags)
			     
{
    cout << "YO!" << endl;
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
		  << std::endl;	//


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
    cout << "Analizador::notaActual" << endl;
    return asociarNota(miBuffer . mayores[0]);
}

Analizador::~Analizador(){
    cout << "--- [DESTRUCTOR] Analizador" << endl;

//    detenerAnalisis();

    cout << "----- Analizador: PortAudio terminado" << endl;

    cout << "Borrando Analizador..." << endl;
}
