#include "estadoAnalizador.h"

#include <iostream>
#include <cmath>

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "FFT.h"
#include "juego.h"

using namespace std;


typedef int MY_TYPE;
#define TIPO paInt16;


EstadoAnalizador::EstadoAnalizador (Juego * p) : Estado(p){
    cout << "+++ [Constructor] EstadoAnalizador" << endl;

    estadoTransicion = transIn;

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
					 _("Analizador de notas"),
					 "media/fNormal.ttf",
					 34, Gosu::Color(0xffa4a4a4),
					 Texto::alignCentro,
					 true, 10, 3, 
					 Animacion::tAlpha));

    txtSubtitulo -> setXY(160, 425);
    txtSubtitulo -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 10);
    txtSubtitulo -> animacion -> set(0, 0, 255);


    imgFigura.reset(new Gosu::Image(padre -> graphics(), L"media/secAnalizador/negraGrande.png"));

    btnVolver.reset(new ElementoCombinado(padre -> graphics(),
					  Animacion::tPos, 2));
    btnVolver -> setImagen("media/btnVolver.png");

    btnVolver -> animacion = new Animacion(2, 30, Animacion::tEaseOutQuad, 0);
    btnVolver -> animacion -> set(0, 0, 0);
    btnVolver -> animacion -> set(1, 600, 547);

    tConfTexto configuracionTexto;
    configuracionTexto.cadena = _("Volver");
    configuracionTexto.rutaFuente = "media/fNormal.ttf";
    configuracionTexto.tam = 25;
    configuracionTexto.sombra = true;
    configuracionTexto.opacidadSombra = 40;
	
    btnVolver -> setTexto(configuracionTexto, 48, 16);
}

void EstadoAnalizador::lanzar(){
    cout << "* EstadoAnalizador lanzado" << endl;
    lanzado = true;
    analizador . iniciar();
}

void EstadoAnalizador::update(){
    if(estadoTransicion == transIn && imgPartitura -> animacion -> finished()){
	estadoTransicion = transHold;
    }

    else if(estadoTransicion == transOut && imgPartitura -> animacion -> finished()){
	padre -> cambiarEstado("estadoMenuSinFondo");
    }
}

void EstadoAnalizador::draw(){
    if(!lanzado){
	return;
    }

    imgPartitura -> draw();
    imgLogotipo -> draw();
    txtSubtitulo -> draw();
    btnVolver -> draw();

    float posY = 76 + 27 * (9 - analizador . notaActual());

    if(analizador.notaActual() != Silencio){
	imgFigura -> draw(637, posY, 4);
    }
}

void EstadoAnalizador::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;

    if (boton == Gosu::kbEscape){
	salir();
    }

    else if(boton == Gosu::msLeft){
	int x = padre -> input().mouseX();
	int y = padre -> input().mouseY();

	if(btnVolver -> clicked(x, y)){
	    salir();
	}
    }
}

void EstadoAnalizador::salir(){
    if(estadoTransicion == transHold){
	lDEBUG << "Deteniendo flujo...";
	
	analizador . detener();
	
	imgLogotipo -> animacion -> reverse();
	imgLogotipo -> animacion -> init();

	imgPartitura -> animacion -> reverse();
	imgPartitura -> animacion -> init();

	txtSubtitulo -> animacion -> reverse();
	txtSubtitulo -> animacion -> init();
	    
	btnVolver -> animacion -> reverse();
	btnVolver -> animacion -> init();
	
	estadoTransicion = transOut;
    }
}


EstadoAnalizador::~EstadoAnalizador(){
    analizador.detener();
    cout << "EstadoAnalizador::~EstadoAnalizador()" << endl;
}