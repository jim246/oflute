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
    Estado(p),  running(false){
    cout << "+++ [Constructor] EstadoAnalizador" << endl;


    // CONFIGURACIÓN DE LA IMAGEN DEL LOGOTIPO
    imgLogotipo.reset(new ElementoImagen(padre -> graphics(),
					"media/ofluteLogoGrande.png",
					3, Animacion::tAlpha));

    imgLogotipo -> setXY(55, 100);
    imgLogotipo -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic);
    imgLogotipo -> animacion -> set(0, 0, 255);



    // CONFIGURACIÓN DE LA IMAGEN DE LA PARTITURA
    imgPartitura.reset(new ElementoImagen(padre -> graphics(),
					 "media/secAnalizador/trozoPartitura.png",
					 3, Animacion::tPos));

    imgPartitura -> animacion = new Animacion(2, 40, Animacion::tEaseOutCubic, 10);
    imgPartitura -> animacion -> set(0, 800, 351);
    imgPartitura -> animacion -> set(1, 116, 116);



    // CONFIGURACIÓN DEL SUBTÍTULO
    txtSubtitulo.reset(new ElementoTexto(padre -> graphics(),
					 "Analizador de notas",
					 "media/fNormal.ttf",
					 34, Gosu::Color(0xffa4a4a4),
					 Texto::alignCentro,
					 true, 10, 3, 
					 Animacion::tAlpha));

    txtSubtitulo -> setXY(160, 425);
    txtSubtitulo -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 10);
    txtSubtitulo -> animacion -> set(0, 0, 255);


    imgFigura.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/negraGrande.png"));
    cargarRecursos();
}

void EstadoAnalizador::cargarRecursos(){
    /*
    imgDo5.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/do5.png"));
    imgRe5.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/re5.png"));
    imgMi5.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/mi5.png"));
    imgFa5.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/fa5.png"));
    imgSol5.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/sol5.png"));
    imgLa5.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/la5.png"));
    imgSi5.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/si5.png"));
    imgDo6.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/do6.png"));
    imgRe6.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/re6.png"));
    //*/
}
void EstadoAnalizador::lanzar(){
    cout << "* EstadoAnalizador lanzado" << endl;
    lanzado = true;
    running = true;
    analizador . iniciar();
}

void EstadoAnalizador::update(){

}

void EstadoAnalizador::draw(){
    if(!lanzado){
	return;
    }

    imgPartitura -> draw();
    imgLogotipo -> draw();
    txtSubtitulo -> draw();


    float posY = 76 + 27 * (9 - analizador . notaActual());

    if(analizador.notaActual() != Silencio){
	imgFigura -> draw(637, posY, 4);
    }
}

void EstadoAnalizador::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    if (boton == Gosu::kbEscape){
	lDEBUG << "Deteniendo flujo...";
//	controlSonido . detenerFlujo();
	analizador . detener();
	padre -> cambiarEstado("estadoMenuSinFondo");

    }
}

EstadoAnalizador::~EstadoAnalizador(){
    analizador.detener();
    cout << "EstadoAnalizador::~EstadoAnalizador()" << endl;
}
