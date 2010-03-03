#include "estadoImagenFija.h"
#include "juego.h"

estadoImagenFija::estadoImagenFija (Juego * p, Gosu::Graphics * graphics, wstring nombreImagen) : estado(p, graphics), nombreImagen(nombreImagen){
    cout << "* Se crea estadoImagenFija" << endl;
}

void estadoImagenFija::lanzar(){
    cout << "* estadoImagenFija lanzado" << endl;
    lanzado = true;
    estadoAnim = 0;
    alphaActual = 0;

    // Poblamos el puntero de la imagen de fondo
    imgFondo.reset(new Gosu::Image(*graph, nombreImagen));
}

void estadoImagenFija::update(){
    if(!lanzado) return;
    short step = 6;

    // 0: Haciendo el fade in
    if(estadoAnim == 0){
	alphaActual += step;

	if(alphaActual > 255){
	    alphaActual = 255;
	    estadoAnim = 1;
	    tiempoEsperaInicial = Gosu::milliseconds();
	}
    }

    // 1: Manteniendo
    else if(estadoAnim == 1){
	if(Gosu::milliseconds() - tiempoEsperaInicial > 1000){
	    estadoAnim = 2;
	}
    }

    // 2: Haciendo el fadeout
    else if(estadoAnim == 2){
	alphaActual -= step;
	if(alphaActual < 0){
	    alphaActual = 0;
	    // padre -> cambiarEstado("estadoIntro");
	    accionPosterior();
	}
    }
}

void estadoImagenFija::draw(){
    if(!lanzado) 
	return;
    
    imgFondo -> draw(0,0,1,1,1,Gosu::Color(alphaActual,255,255,255));
}

void estadoImagenFija::buttonDown(Gosu::Button boton){
    if(!lanzado) return;
    if (boton == Gosu::kbEscape){
//	padre -> cambiarEstado("estadoIntro");
//	padre -> close();
	accionPosterior();
    }else{
	cout << "KABOOM" << endl;
    }
}
