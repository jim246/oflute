#include "juego.h"
#include "estadoCancion.h"

#include "estadoMenuCanciones.h"

EstadoMenuCanciones::EstadoMenuCanciones(Juego * p)
    : Estado(p), cancion(0){

}

void EstadoMenuCanciones::update(){
    if(cancion != 0) cancion -> update();
}

void EstadoMenuCanciones::draw(){
    if(cancion != 0) cancion -> draw();
}

void EstadoMenuCanciones::buttonDown(Gosu::Button boton){
    if(cancion != 0)
	cancion -> buttonDown(boton);

    if(boton == Gosu::kbEscape){
	padre -> cambiarEstado("estadoMenuSinFondo");
    }

    else if(boton == Gosu::kbReturn){

	lDEBUG << "Se pulsó enter";
	if(cancion != 0)
	    delete cancion;

	cancion = new Cancion(padre -> graphics(), "song1.xml");
	cancion -> lanzar();

    }

   
}

EstadoMenuCanciones::~EstadoMenuCanciones(){
    if(cancion != 0){
	delete cancion;
    }
}
