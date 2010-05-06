#include "juego.h"
#include "estadoLecciones.h"

EstadoMenuLecciones::EstadoMenuLecciones(Juego * p) : Estado(p) {
    imgFondo.reset (new Gosu::Image(padre -> graphics(),
				    L"media/fondoGenerico.png"));
}

void EstadoMenuLecciones::draw() {
    imgFondo -> draw(0,0,1);
}

void EstadoMenuLecciones::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbEscape){
	padre -> cambiarEstado("salir");
    }
}
