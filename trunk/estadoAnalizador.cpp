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

tipoBuffer EstadoAnalizador::miBuffer;

//int posFinalesY[] = {281, 333, 386, 441, 494 };
EstadoAnalizador::EstadoAnalizador (Juego * p) : Estado(p), numSamples(2048){
    cout << "EstadoAnalizador::CONSTRUCTOR" << endl;
    lanzado = true;    
    lanzar();
    miBuffer.pos = 0;

    notas[523.25] = Do5;
    notas[592.163] = Re5;
    notas[656.763] = Mi5;
    notas[699.829] = Fa5;
    notas[785.692] = Sol5;
    notas[893.628] = La5;
    notas[1001.29] = Si5;
    notas[1076.66] = Do6;
    notas[1195.09] = Re6;

    imgFondo.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/baseAnalizador.png"));
    imgDo5.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/do5.png"));
    imgRe5.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/re5.png"));
    imgMi5.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/mi5.png"));
    imgFa5.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/fa5.png"));
    imgSol5.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/sol5.png"));
    imgLa5.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/la5.png"));
    imgSi5.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/si5.png"));
    imgDo6.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/do6.png"));
    imgRe6.reset(new Gosu::Image(padre -> graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/re6.png"));

}

void EstadoAnalizador::lanzar(){
    cout << "* EstadoAnalizador lanzado" << endl;
    lanzado = true;

    if (!configurarFlujo()){
	cout << "*** Error al configurar el flujo." << endl;
    }

    if(!iniciarAnalisis()){
	cout << "*** Error al iniciar el análisis." << endl;
    }//*/
}

void EstadoAnalizador::update(){
    if(!lanzado) 
	lanzar();
}

void EstadoAnalizador::draw(){
    if(!lanzado) 
	return;

    boost::shared_ptr<Gosu::Image> p;
    switch(notaActual()){
    case Do5:
	p = imgDo5; break;
    case Re5:
	p = imgRe5; break;
    case Mi5:
	p = imgMi5; break;
    case Fa5:
	p = imgFa5; break;
    case Sol5:
	p = imgSol5; break;
    case La5:
	p = imgLa5; break;
    case Si5:
	p = imgSi5; break;
    case Do6:
	p = imgDo6; break;
    case Re6:
	p = imgRe6; break;
    }

    if(!miBuffer.silencio)
	p -> draw(584,138,2);


    imgFondo -> draw(0,0,1);
}

void EstadoAnalizador::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    if (boton == Gosu::kbEscape){
	padre -> close();
    }
}

EstadoAnalizador::~EstadoAnalizador(){
    cout << "EstadoAnalizador::~EstadoAnalizador()" << endl;
}

bool EstadoAnalizador::configurarFlujo(){
//    PaStreamParameters inParameters, outParameters;

    cout << "- Intentando Pa_Initialize..." << flush;
    err = Pa_Initialize();
    if(err != paNoError) std::cout << "ERROR: " << (int) err << std::endl;

    cout << "OK" << endl;

    cout << "- Intentando Pa_OpenDefaultStream..." << flush;
    err = Pa_OpenDefaultStream(&stream,
			       2,
			       0,
			       paInt16,
			       44100,
			       256,
			       &updateBuffer,
			       (void*) this);

    if(err != paNoError) std::cout << "ERROR" << std::endl;

    cout << "OK" << endl;

    std::cout << "* Duración del búffer: " << 256.0/44100.0*1000 << "ms" << std::endl;



    return true;
} 

bool EstadoAnalizador::iniciarAnalisis(){
    cout << "### EstadoAnalizador::iniciarAnalisis ###" << endl;
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

bool EstadoAnalizador::detenerAnalisis(){
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


int EstadoAnalizador::updateBuffer(const void * inB, 
			     void * outB, 
			     unsigned long nFrames, 
			     const PaStreamCallbackTimeInfo * timeInfo,
			     PaStreamCallbackFlags statusFlags,
			     void * data)
{
    
    EstadoAnalizador * puntero = (EstadoAnalizador*) data;
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

t_altura EstadoAnalizador::notaActual(){
    return asociarNota(miBuffer .mayores[0]);
}

t_altura EstadoAnalizador::asociarNota(double frecuencia){
    std::map<double, t_altura> diferencias;
    std::map<double, t_altura>::iterator iter;

    for(iter = notas.begin();
	iter != notas.end();
	++iter)
    {
	diferencias[abs(frecuencia - iter -> first)] = iter -> second;
    }
    
    iter = min_element(diferencias.begin(), diferencias.end());
    return iter -> second;//*/
    
}
