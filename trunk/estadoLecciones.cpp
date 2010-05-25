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

    tConfAnim * confBtn = new tConfAnim();
    confBtn -> animar = Animacion::tPos;
    confBtn -> inicialX = 800;
    confBtn -> finalX = 400;
    confBtn -> inicialY = confBtn -> finalY = 69;
    confBtn -> wait = 10;
    confBtn -> duracion = 20;
    confBtn -> z = 2;
    btn1.reset(new ElementoCombinado(padre -> graphics(), *confBtn));

    btn1 -> setImagen("media/menuLecciones/mBtn1.png");

    tConfTexto * confBtnTexto = new tConfTexto;
    confBtnTexto -> cadena = "Lección #1";
    confBtnTexto -> rutaFuente = "media/fNormal.ttf";
    confBtnTexto -> tam = 36;
    confBtnTexto -> sombra = false;
    confBtnTexto -> alineacion = Texto::alignDer;
    btn1 -> setTexto(*confBtnTexto, -20, 7);




    ///////////////////////////////
    // Descripción
    confBtn -> inicialY = confBtn -> finalY = 127;
    confBtn -> wait = 20;
    btnDescripcion.reset(new ElementoCombinado(padre -> graphics(), *confBtn));

    btnDescripcion -> setImagen("media/menuLecciones/mBtn2.png");

    confBtnTexto -> cadena = "Descripción:";
    confBtnTexto -> sombra = true;
    confBtnTexto -> color = Gosu::Color(255, 227, 253, 94);
    btnDescripcion -> setTexto(*confBtnTexto, -20, 10);




    ///////////////////////////////
    // Botón comenzar 127
    confBtn -> inicialY = confBtn -> finalY = 351;
    confBtn -> wait = 30;
    btnComenzar.reset(new ElementoCombinado(padre -> graphics(), *confBtn));

    btnComenzar -> setImagen("media/menuLecciones/mBtn3.png");
    confBtnTexto -> color = Gosu::Color(255,255,255,255);
    confBtnTexto -> cadena = "Comenzar lección";
    confBtnTexto -> alineacion = Texto::alignCentro;
    btnComenzar -> setTexto(*confBtnTexto, 10, 10);


    ///////////////////////////////
    // Botón Siguiente Lección
    confBtn -> inicialY = confBtn -> finalY = 417;
    confBtn -> wait = 40;
    btnSigLec.reset(new ElementoCombinado(padre -> graphics(), *confBtn));
    btnSigLec -> setImagen("media/menuLecciones/mBtn4.png");

    confBtnTexto -> cadena = "Siguiente lección";
    btnSigLec -> setTexto(*confBtnTexto, 10, 13);


    /////////////////////////////
    // Botón Anterior Lección
    confBtn -> inicialY = confBtn -> finalY = 487;
    confBtn -> wait = 50;
    btnAntLec.reset(new ElementoCombinado(padre -> graphics(), *confBtn));
    btnAntLec -> setImagen("media/menuLecciones/mBtn5.png");

    confBtnTexto -> cadena = "Anterior lección";
    btnAntLec -> setTexto(*confBtnTexto, 10, 10);


    delete confBtn;
    delete confBtnTexto;

			      
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
    btnComenzar -> draw();
    btnAntLec -> draw();
    btnSigLec -> draw();
    btnDescripcion -> draw();
    // txtSubtitulo -> draw();
}

void EstadoMenuLecciones::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbEscape){
	padre -> cambiarEstado("salir");
    }
}
