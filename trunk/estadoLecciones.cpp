#include "juego.h"
#include "estadoLecciones.h"

EstadoMenuLecciones::EstadoMenuLecciones(Juego * p) : Estado(p) {
    imgFondo.reset (new Gosu::Image(padre -> graphics(),
				    L"media/fondoGenerico.png"));

    txtTitulo.reset(new elementoTexto(padre -> graphics(),
				      "Listado de lecciones",
				      "media/fNormal.ttf",
				      40,
				      10, 10, 2,				      
				      true, 0, 30,
				      Gosu::Color(255, 234, 123, 200), Texto::alignIzq, 1, 80));
}

void EstadoMenuLecciones::update(){

}

void EstadoMenuLecciones::draw() {
    imgFondo -> draw(0,0,1);
    txtTitulo -> draw();
}

void EstadoMenuLecciones::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbEscape){
	padre -> cambiarEstado("salir");
    }
}
