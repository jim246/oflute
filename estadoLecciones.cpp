#include "juego.h"
#include "estadoLecciones.h"

EstadoMenuLecciones::EstadoMenuLecciones(Juego * p) : Estado(p) {
    imgFondo.reset (new Gosu::Image(padre -> graphics(),
				    L"media/fondoGenerico.png"));

    txtTitulo.reset(new elementoTexto(padre -> graphics(),
				      "Listado de lecciones",
				      "media/fLight.ttf",
				      92, // Tamaño
				      35, 15, 2, // X,Y,Z				      
				      true, 0, 30, // anim, wait, duracion
				      Gosu::Color(255, 1, 74, 29), 
				      Texto::alignIzq, 
				      true, 30));

    pizarra.reset(new elementoImagen(padre -> graphics(),
				     "media/pizarra.png",
				     35, 128, 2,
				     true, 10)
	);

    txtSubtitulo.reset(new elementoTexto(padre -> graphics(),
					 string("Usa los botones de la derecha para\n")
					 + "seleccionar la lección que más te\n"
					 + "interese.",
					 "media/fNormal.ttf",
					 30,
					 210, 400, 2,
					 true, 20, 30,
					 Gosu::Color(255, 1, 74, 29),
					 Texto::alignCentro, false) );
				     
}

void EstadoMenuLecciones::update(){

}

void EstadoMenuLecciones::draw() {
    imgFondo -> draw(0,0,1);
    txtTitulo -> draw();
    pizarra -> draw();
    txtSubtitulo -> draw();
}

void EstadoMenuLecciones::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbEscape){
	padre -> cambiarEstado("salir");
    }
}
