#include "juego.h"

#include "estado.h"

#include "estadoIntro.h"
#include "estadoAutor.h"
#include "estadoMenu.h"
#include "estadoAnalizador.h"

Juego::Juego() : Gosu::Window (ANCHO, ALTO, FULLSCREEN, FPS){
    cout << "********* Juego::CONSTRUCTOR" << endl;

    estadoActual.reset ( new estadoAutor(this) );
    estadoActual -> lanzar();
}

void Juego::update(){
    estadoActual -> update();
}

void Juego::draw(){
    estadoActual -> draw();
}


void Juego::cambiarEstado(std::string destino){
    cout << "**** juego::cambiarEstado(" << destino << ")" << endl;

    if(destino == "estadoIntro"){
	estadoActual.reset(new estadoIntro(this));
    }
	
    else if(destino == "estadoMenu"){
	estadoActual.reset(new estadoMenu(this));
    }

    else if(destino == "estadoAnalizador"){
	estadoActual.reset(new estadoAnalizador(this));
    }
	
    estadoActual -> lanzar();
}
    
void Juego::buttonDown(Gosu::Button boton){
    estadoActual -> buttonDown(boton);
}    

Juego::~Juego(){
    cout << "********* Juego::DESTRUCTOR" << endl;
}
