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


EstadoAnalizador::EstadoAnalizador (Juego * p) : 
    Estado(p),  firstFrame(true), running(false){
    cout << "+++ [Constructor] EstadoAnalizador" << endl;

    cartelCargando.reset(new Gosu::Image(padre -> graphics(), L"media/imgCargando.png"));

    cargarRecursos();
    lanzar();
}

void EstadoAnalizador::cargarRecursos(){
    partitura.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/baseAnalizador.png"));
    imgDo5.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/do5.png"));
    imgRe5.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/re5.png"));
    imgMi5.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/mi5.png"));
    imgFa5.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/fa5.png"));
    imgSol5.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/sol5.png"));
    imgLa5.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/la5.png"));
    imgSi5.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/si5.png"));
    imgDo6.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/do6.png"));
    imgRe6.reset(new Gosu::Image(padre -> graphics(), L"media/analizadorAssets/re6.png"));

}
void EstadoAnalizador::lanzar(){
    cout << "* EstadoAnalizador lanzado" << endl;
    lanzado = true;
}

void EstadoAnalizador::activar(){
    if(running) return;
    running = true;
    
    if (!controlSonido . configurarFlujo(analizador)){
	cout << "*** Error al configurar el flujo." << endl;
    }

    if(!controlSonido . iniciarFlujo()){
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
	cartelCargando -> draw(ANCHO/2 - 200/2,
			       ALTO/2 - 50/2, 1);
	firstFrame = false;
	return;
    }

    boost::shared_ptr<Gosu::Image> p;
    bool sil = false;
    switch(analizador . notaActual()){
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
	sil = true;
	break;
    }
    partitura -> draw(0,0,2);
//    if(!controlSonido . miBuffer.silencio){
    if(!sil)
	p -> draw(584,138,3);
//    } //*/


}

void EstadoAnalizador::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    if (boton == Gosu::kbEscape){
	controlSonido . detenerFlujo();
	padre -> cambiarEstado("estadoMenuSinFondo");

    }
}

EstadoAnalizador::~EstadoAnalizador(){
    cout << "EstadoAnalizador::~EstadoAnalizador()" << endl;
}
