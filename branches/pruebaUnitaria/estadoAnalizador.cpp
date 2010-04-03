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

//tipoBuffer EstadoAnalizador::miBuffer;

//int posFinalesY[] = {281, 333, 386, 441, 494 };
EstadoAnalizador::EstadoAnalizador () : 
    Gosu::Window(800,600,false),  firstFrame(true), running(false){
    cout << "+++ [CONSTRUCTOR] EstadoAnalizador" << endl;

    cartelCargando.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/imgCargando.png"));
    analizador.reset(new Analizador);

//    draw();
    cargarRecursos();
    lanzar();


}

void EstadoAnalizador::cargarRecursos(){

/*
    imgFondo.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/baseAnalizador.png"));

    imgDo5.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/do5.png"));
    imgRe5.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/re5.png"));
    imgMi5.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/mi5.png"));
    imgFa5.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/fa5.png"));
    imgSol5.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/sol5.png"));
    imgLa5.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/la5.png"));
    imgSi5.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/si5.png"));
    imgDo6.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/do6.png"));
    imgRe6.reset(new Gosu::Image( graphics(), Gosu::resourcePrefix() + L"media/analizadorAssets/re6.png"));

    //*/
}
void EstadoAnalizador::lanzar(){
    cout << "* EstadoAnalizador lanzado" << endl;
    lanzado = true;
}

void EstadoAnalizador::activar(){
    if(running) return;
    running = true;
    
    if (!analizador -> configurarFlujo()){
	cout << "*** Error al configurar el flujo." << endl;
    }

    if(!analizador -> iniciarAnalisis()){
	cout << "*** Error al iniciar el análisis." << endl;
    }//*/
}


void EstadoAnalizador::update(){
    if(!firstFrame && !running)
	activar();
}

void EstadoAnalizador::draw(){
    if(!lanzado){

	return;
    }

    if(firstFrame){
//	cartelCargando -> draw(ANCHO/2 - 200/2, ALTO/2 - 50/2, 1);
	firstFrame = false;
	return;
    }
/*
    boost::shared_ptr<Gosu::Image> p;
    switch(analizador -> notaActual()){
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
    case Silencio:
	break;
    }

    if(!analizador -> miBuffer.silencio){
	p -> draw(584,138,2);
    } //*/

/*
    imgFondo -> draw(0,0,1); //*/
}

void EstadoAnalizador::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    if (boton == Gosu::kbEscape){
	cout << "PRESSED ESCAPE" << endl;
	analizador -> detenerAnalisis();
	cout << "After detenerAnalisis()" << endl;
	close();
    }
}

EstadoAnalizador::~EstadoAnalizador(){
//    analizador -> detenerAnalisis();
    cout << "EstadoAnalizador::~EstadoAnalizador()" << endl;
}
