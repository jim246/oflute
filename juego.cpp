#include "juego.h"

#include "estado.h"

#include "estadoImagenFija.h"
// #include "estadoIntro.h"
// #include "estadoAutor.h"

#include "estadoMenu.h"
#include "estadoAnalizador.h"

Juego::Juego() : Gosu::Window (ANCHO, ALTO, FULLSCREEN, FPS){
    cout << "+++ [CONSTRUCTOR] Juego" << endl;

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
    cursor -> draw(input().mouseX(), input().mouseY(), 999);
    estadoActual -> draw();
}


void Juego::cambiarEstado(std::string destino){
    cout << "**** juego::cambiarEstado(" << destino << ")" << endl;

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
	

}
    
void Juego::buttonDown(Gosu::Button boton){
    estadoActual -> buttonDown(boton);
}    

Juego::~Juego(){
    cout << "--- [DESTRUCTOR] Juego" << endl;
}
