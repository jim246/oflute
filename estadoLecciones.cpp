#include "juego.h"
#include "estadoLecciones.h"

EstadoMenuLecciones::EstadoMenuLecciones(Juego * p) : Estado(p) {
    imgFondo.reset (new Gosu::Image(padre -> graphics(),
				    L"media/fondoGenerico.png"));

    
    tConfAnim * t = new tConfAnim;
    t -> animar = Animacion::tAlphaPos;
//    t -> inicialX = 0;
    t -> finalX = 35;

//    t -> inicialY = 0;
    t -> finalY = 128;

    t -> inicialA = 0;
    t -> finalA = 255;

    t -> z = 2;
    t -> wait = 0;
    t -> duracion = 30;


    pizarra.reset(new elementoImagen(padre -> graphics(),
				     "media/pizarra.png",
				     *t));
    delete t;
    

    t = new tConfAnim;
    t -> animar = Animacion::tPos;
    t -> inicialY = -70;
    t -> z = 2;
    barraSuperior.reset(new ElementoCombinado( padre -> graphics(), *t));
    delete t;

    tConfTexto * cTexto = new tConfTexto();

    cTexto-> cadena = "Listado de lecciones";
    cTexto-> rutaFuente = "media/fLight.ttf";
    cTexto-> tam = 56;
    
    barraSuperior -> setTexto(*cTexto, 34, 0);
			
    delete cTexto;

    barraSuperior -> setImagen("media/menuLecciones/mTop.png");



    // Barra inferior

    tConfAnim * confInferior = new tConfAnim();
    confInferior -> animar = Animacion::tPos;
    confInferior -> inicialY = 600;
    confInferior -> finalY = 554;
    confInferior -> z = 2;
    barraInferior.reset(new ElementoCombinado(padre -> graphics(), *confInferior));

    barraInferior -> setImagen("media/menuLecciones/mBottom.png");

    tConfTexto * confInferiorTexto = new tConfTexto;
    confInferiorTexto -> cadena = "Volver al menú principal";
    confInferiorTexto -> rutaFuente = "media/fNormal.ttf";
    confInferiorTexto -> tam = 28;
    barraInferior -> setTexto(*confInferiorTexto, 52, 7);

    delete confInferior;
    delete confInferiorTexto;



    // Primer botón

    tConfAnim * confBtn1 = new tConfAnim();
    confBtn1 -> animar = Animacion::tPos;
    confBtn1 -> inicialX = 800;
    confBtn1 -> finalX = 400;
    confBtn1 -> inicialY = confBtn1 -> finalY = 69;
    confBtn1 -> wait = 10;
    confBtn1 -> duracion = 20;
    confBtn1 -> z = 2;
    btn1.reset(new ElementoCombinado(padre -> graphics(), *confBtn1));

    btn1 -> setImagen("media/menuLecciones/mBtn1.png");

    tConfTexto * confBtn1Texto = new tConfTexto;
    confBtn1Texto -> cadena = "Lección #1";
    confBtn1Texto -> rutaFuente = "media/fNormal.ttf";
    confBtn1Texto -> tam = 36;
    confBtn1Texto -> sombra = false;
    confBtn1Texto -> alineacion = Texto::alignDer;
    btn1 -> setTexto(*confBtn1Texto, -20, 7);

    delete confBtn1;
    delete confBtn1Texto;
			      
}

void EstadoMenuLecciones::update(){

}

void EstadoMenuLecciones::draw() {
    imgFondo -> draw(0,0,1);
  
    // txtTitulo -> draw();
    pizarra -> draw();
    barraSuperior -> draw();
    barraInferior -> draw();
    btn1 -> draw();
    // txtSubtitulo -> draw();
}

void EstadoMenuLecciones::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbEscape){
	padre -> cambiarEstado("salir");
    }
}
