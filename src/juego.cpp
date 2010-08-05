#include "juego.h"

#include "estado.h"

#include "estadoImagenFija.h"
#include "estadoMenu.h"
#include "estadoAnalizador.h"
#include "estadoLecciones.h"
#include "estadoMenuCanciones.h"
#include "estadoCalibrarMicro.h"

#include "log.h"

#include <boost/lexical_cast.hpp>


Juego::Juego() : Gosu::Window (ANCHO, ALTO, FULLSCREEN, REFRESCO){
    lDEBUG << Log::CON("Juego");
    setCaption(L"oFlute .:.");


    cursor.reset( new Gosu::Image(graphics(), L"media/pointerCursor.png"));

    fondoComun.reset( new Gosu::Image(graphics(), L"media/fondoGenerico.png"));
    animacionFondo.reset (new Animacion(1, 50, Animacion::tEaseOutQuad));
    animacionFondo -> set(0, 0, 255);

    cambiarEstado("estadoAutor");

}

void Juego::update(){
    estadoActual -> update();
    
    if(estadoCadena != "estadoAutor" && estadoCadena != "estadoIntro"){
	animacionFondo -> update();
    }
}

void Juego::draw(){
    // Dibujamos el cursor en la posición del ratón
    // Usamos Z=999 para que esté encima de todo

    cursor -> draw(input().mouseX(), input().mouseY(), 999);
    estadoActual -> draw();
    if(estadoCadena != "estadoAutor" && estadoCadena != "estadoIntro"){
	fondoComun -> draw(0,0,1, 1,1, Gosu::Color(animacionFondo -> get(0), 255, 255, 255));
    }
}


void Juego::cambiarEstado(std::string destino){
    lDEBUG << "\t>>>>>>>>>>>>> Nuevo estado: " << destino;
    estadoCadena = destino;
    
    if (destino == "estadoAutor"){
	estadoActual.reset( 
	    new EstadoImagenFija(this, L"media/estadoAutor.png", "estadoIntro"));
	estadoActual -> lanzar();	
    }

    else if(destino == "estadoIntro"){
	estadoActual.reset(
	    new EstadoImagenFija(this, L"media/estadoIntro.png", "estadoMenu"));
	estadoActual -> lanzar();
    }
	
    else if(destino == "estadoMenu"){
	estadoActual.reset(new EstadoMenu(this));
	estadoActual -> lanzar();
    }
    
    else if(destino == "estadoMenuSinFondo"){
	estadoActual.reset(new EstadoMenu(this));
	static_cast<EstadoMenu * >(estadoActual . get()) -> quitarDemoraInicial();
	estadoActual -> lanzar();
    }

    else if(destino == "estadoAnalizador"){
	estadoActual.reset(new EstadoAnalizador(this));
	estadoActual -> lanzar();
    }

    else if(destino == "estadoLecciones"){
	estadoActual.reset(new EstadoMenuLecciones(this));
    }

    else if(destino == "estadoCancion"){
	estadoActual.reset(new EstadoMenuCanciones(this));
	estadoActual -> lanzar();
    }

    else if(destino == "estadoCalibrar"){
	estadoActual.reset(new EstadoCalibrarMicro(this));
    }
	
    else if(destino == "salir"){
	close();
    }
}
    
void Juego::buttonDown(Gosu::Button boton){
    if(estadoCadena != "estadoAutor" && estadoCadena != "estadoIntro" && boton == Gosu::kbEscape){
	animacionFondo -> end();
    }
    estadoActual -> buttonDown(boton);
}    

Juego::~Juego(){
    lDEBUG << Log::DES("Juego");
}
