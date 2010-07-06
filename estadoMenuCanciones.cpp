#include "juego.h"
#include "estadoCancion.h"

#include "estadoMenuCanciones.h"

EstadoMenuCanciones::EstadoMenuCanciones(Juego * p)
    : Estado(p), cancion(0){
    imgLogotipo.reset(new ElementoImagen(padre -> graphics(),
					 "media/ofluteLogoGrande.png",
					 3, Animacion::tPos));

    // 351, 116
    imgLogotipo -> animacion = new Animacion(2, 20, Animacion::tEaseOutCubic);
    imgLogotipo -> animacion -> set(0, 800, 351);
    imgLogotipo -> animacion -> set(1, 116, 116);
}

void EstadoMenuCanciones::update(){
    if(cancion != 0) {
	cancion -> update();
    }else{
	imgLogotipo -> draw();
    }
}

void EstadoMenuCanciones::draw(){
    if(cancion != 0){
	cancion -> draw();
    }
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
