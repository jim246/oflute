#include "estadoAutor.h"
#include "juego.h"

estadoAutor::estadoAutor (Juego * p, Gosu::Graphics * graphics) : estado(p, graphics){
    cout << "* Se crea estado autor" << endl;
}

void estadoAutor::lanzar(){
    cout << "* estadoAutor lanzado" << endl;
    lanzado = true;
    estadoAnim = 0;
    alphaActual = 0;
    // Poblamos el puntero de la imagen de fondo
    imgFondo.reset(new Gosu::Image(*graph, L"estadoAutor.png"));
}

void estadoAutor::update(){
    if(!lanzado) return;
    short step = 10;

    // 0: Haciendo el fade in
    if(estadoAnim == 0){
	alphaActual += step;

	if(alphaActual > 255){
	    alphaActual = 255;
	    estadoAnim = 1;
	}
    }

    // 1: Manteniendo
    else if(estadoAnim == 1){
	cout << "estadoAnim 1" << endl;
	Gosu::sleep(1000);
	estadoAnim = 2;
    }

    // 2: Haciendo el fadeout
    else if(estadoAnim == 2){
	alphaActual -= step;
	if(alphaActual < 0){
	    alphaActual = 0;
	    padre -> cambiarEstado("estadoIntro");
	}
    }
}

void estadoAutor::draw(){
    if(!lanzado) return;
    imgFondo -> draw(0,0,1,1,1,Gosu::Color(alphaActual,255,255,255));
}

void estadoAutor::buttonDown(Gosu::Button boton){
    if(!lanzado) return;
    if (boton == Gosu::kbEscape){
	padre -> cambiarEstado("estadoIntro");
//	padre -> close();
    }
}
