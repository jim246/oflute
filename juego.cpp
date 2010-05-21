#include "juego.h"

#include "estado.h"

#include "estadoImagenFija.h"
#include "estadoMenu.h"
#include "estadoAnalizador.h"
#include "estadoLecciones.h"

#include "log.h"

#include <boost/lexical_cast.hpp>


Juego::Juego() : Gosu::Window (ANCHO, ALTO, FULLSCREEN, FPS){
    lDEBUG << Log::CON("Juego");
    setCaption(L"oFlute .:.");
    estadoActual.reset ( 
	new EstadoImagenFija(this,
			     Gosu::resourcePrefix() + L"media/estadoAutor.png",
			     "estadoIntro")
	);

    cursor.reset( new Gosu::Image(graphics(), Gosu::resourcePrefix() + L"media/pointerCursor.png"));
    estadoActual -> lanzar();
}

void Juego::update(){
    estadoActual -> update();
}

void Juego::draw(){
    // Dibujamos el cursor en la posición del ratón
    // Usamos Z=999 para que esté encima de todo

    cursor -> draw(input().mouseX(), input().mouseY(), 999);
    estadoActual -> draw();
}


void Juego::cambiarEstado(std::string destino){
    lDEBUG << "\t>>>>>>>>>>>>> Nuevo estado: " << destino;

    if(destino == "estadoIntro"){
	estadoActual.reset(
	    new EstadoImagenFija(this,
				 Gosu::resourcePrefix() + L"media/estadoIntro.png",
				 "estadoMenu")
	    );
	estadoActual -> lanzar();
    }
	
    else if(destino == "estadoMenu"){
	estadoActual.reset(new EstadoMenu(this));
	estadoActual -> lanzar();
    }

    else if(destino == "estadoAnalizador"){
	estadoActual.reset(new EstadoAnalizador(this));
    }

    else if(destino == "estadoLecciones"){
	estadoActual.reset(new EstadoMenuLecciones(this));
    }
	
    else if(destino == "salir"){
	close();
    }
}
    
void Juego::buttonDown(Gosu::Button boton){
    estadoActual -> buttonDown(boton);
}    

Juego::~Juego(){
    lDEBUG << Log::DES("Juego");
}
