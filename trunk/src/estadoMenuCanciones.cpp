#include "juego.h"
#include "estadoCancion.h"

#include "estadoMenuCanciones.h"

EstadoMenuCanciones::EstadoMenuCanciones(Juego * p)
    : Estado(p), cancion(0){

    estadoTransicion = transIn;

    // CONFIGURACIÓN DE LA IMAGEN DEL LOGOTIPO
    imgLogotipo.reset(new ElementoImagen(padre -> graphics(),
					"media/ofluteLogoGrande.png",
					3, Animacion::tAlpha));

    imgLogotipo -> setXY(75, 100);
    imgLogotipo -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic);
    imgLogotipo -> animacion -> set(0, 0, 255);

    // CONFIGURACIÓN DEL SUBTÍTULO
    txtSubtitulo.reset(new ElementoTexto(padre -> graphics(),
					 "Seleccione una canción",
					 "media/fNormal.ttf",
					 34, Gosu::Color(0xffa4a4a4),
					 Texto::alignCentro,
					 true, 10, 3, 
					 Animacion::tAlpha));

    txtSubtitulo -> setXY(180, 425);
    txtSubtitulo -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 10);
    txtSubtitulo -> animacion -> set(0, 0, 255);

}

void EstadoMenuCanciones::update(){
    if(estadoTransicion == transIn){
	if(imgLogotipo -> animacion -> finished() &&
	   txtSubtitulo -> animacion -> finished()){
	    estadoTransicion = transHold;
	}
    }

    if(cancion != 0) {
	cancion -> update();
    }
}

void EstadoMenuCanciones::draw(){
    if(estadoTransicion == mostrandoCancion){
	cancion -> draw();
    }else{
	imgLogotipo -> draw();
	txtSubtitulo -> draw();
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

	cancion.reset(new Cancion(padre -> graphics(), "song1.xml"));
	cancion -> lanzar();

	estadoTransicion = mostrandoCancion;
    }

   
}

EstadoMenuCanciones::~EstadoMenuCanciones(){

}
