#include "juego.h"

#include "estado.h"

#include "estadoIntro.h"
#include "estadoAutor.h"
#include "estadoMenu.h"
#include "estadoAnalizador.h"

Juego::Juego() : Gosu::Window (ANCHO, ALTO, FULLSCREEN, FPS){
    cout << "********* Juego::CONSTRUCTOR" << endl;

    estadoActual.reset ( new EstadoAutor(this) );
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
	estadoActual.reset(new EstadoIntro(this));
    }
	
    else if(destino == "estadoMenu"){
	estadoActual.reset(new EstadoMenu(this));
    }

    else if(destino == "estadoAnalizador"){
	estadoActual.reset(new EstadoAnalizador(this));
    }
	
    estadoActual -> lanzar();
}
    
void Juego::buttonDown(Gosu::Button boton){
    estadoActual -> buttonDown(boton);
}    

Juego::~Juego(){
    cout << "********* Juego::DESTRUCTOR" << endl;
}
