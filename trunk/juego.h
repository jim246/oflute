#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "Gosu/Gosu.hpp"
#include "boost/scoped_ptr.hpp"

#include "estado.h"
#include "estadoIntro.h"
#include "estadoAutor.h"
#include "estadoMenu.h"


#define ANCHO 800
#define ALTO 600
#define FULLSCREEN false
#define FPS 30

class Juego : public Gosu::Window{
    boost::scoped_ptr <estado> estadoActual;
public:
    Juego() : Window(ANCHO, ALTO, FULLSCREEN, FPS){
	estadoActual.reset(new estadoAutor(this));
	cout << "Juego()" << endl;
	estadoActual -> lanzar();
    }

    void update(){
//	cout << "Update" << endl;
	estadoActual -> update();
    }

    void draw(){
	estadoActual -> draw();
    }

    void cambiarEstado(std::string destino){
	if(destino == "estadoIntro"){
	    estadoActual.reset(new estadoIntro(this));
	}
	else if(destino == "estadoMenu"){
	    estadoActual.reset(new estadoMenu(this));
	}
	estadoActual -> lanzar();
    }
    
    void buttonDown(Gosu::Button boton){
	estadoActual -> buttonDown(boton);
    }    
};

#endif /* _JUEGO_H_ */
