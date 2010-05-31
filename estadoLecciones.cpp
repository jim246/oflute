#include "juego.h"
#include "estadoLecciones.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "pugixml.hpp"

EstadoMenuLecciones::EstadoMenuLecciones(Juego * p) : Estado(p) {

    leccionActual = -1;
    imgFondo.reset (new Gosu::Image(padre -> graphics(),
				    L"media/fondoGenerico.png"));

    
    tConfAnim * t = new tConfAnim;
    t -> animar = Animacion::tAlphaPos;
    t -> inicialX = -450;
    t -> finalX = 35;
    t -> inicialY = 128;
    t -> finalY = 128;

    t -> inicialA = 0;
    t -> finalA = 255;

    t -> z = 2;
    t -> wait = 0;
    t -> duracion = 30;


    pizarra.reset(new ElementoImagen(padre -> graphics(),
				     "media/menuLecciones/pizarra.png",
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

    tConfTexto tdConf;
    tdConf.cadena = " ";
    tdConf.rutaFuente = "media/fNormal.ttf";
    tdConf.tam = 36;
    tdConf.alineacion = Texto::alignDer;

    tConfAnim tdConfA;
    tdConfA.finalX = 780;
    tdConfA.finalY = 175;
    tdConfA.finalA = 255;
    tdConfA.z = 4;

    textoDesc . reset (new ElementoTexto(padre -> graphics(), tdConf, tdConfA));

    /*textoDesc.reset(new ElementoTexto(padre -> graphics(),
				      " ", "media/fNormal.ttf",
				      36, Gosu::Color(255,255,255,255),
				      Texto::alignDer, true, 80,
				      780, 175, 255, 4)); //*/


    ///////////////////////////////
    // Botón comenzar 
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

void EstadoMenuLecciones::listarLecciones(){


    boost::filesystem::path rutaDirectorio("./lecciones");
    boost::filesystem::directory_iterator inicial(rutaDirectorio), final;

    pugi::xml_document documento;
    pugi::xml_parse_result resultado;
    pugi::xml_node nodoActual, nodoVacio;
    pugi::xml_attribute atributo;

    for(; inicial != final ; ++ inicial){
	if(boost::to_lower_copy(inicial -> path() . extension()) == ".xml"){

	    EstadoMenuLecciones::infoLeccion lecActual;
	    string ruta = boost::lexical_cast<string>(inicial -> path());

	    lDEBUG << "Intentando cargar archivo " << ruta;

	    resultado = documento . load_file(ruta.c_str());

	    if(!resultado){
		lERROR << LOC() << " Error al leer el documento: " << ruta;
		lERROR << resultado.description(); 
		continue;
	    }


	    /////////////////////
	    // Leemos el número de lección

	    nodoActual = documento.child("Lec").child("index");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << ruta << " no está bien formado. "
		       << "(Falta índice)";
		continue;
	    }

	    lecActual.indice = boost::lexical_cast<int>(nodoActual.first_child().value());


	    /////////////////
	    // Leemos el nombre de la lección

	    nodoActual = documento.child("Lec").child("nombre");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << ruta << " no está bien formado. "
		       << "(Falta nombre)";
		continue;
	    }

	    lecActual.nombre = nodoActual.first_child().value();


	    /////////////////////
	    // Leemos la descripción
	    nodoActual = documento.child("Lec").child("descrip");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << ruta << " no está bien formado. "
		       << "(Falta descripción)";
		continue;
	    }

	    lecActual.descrip = nodoActual.first_child().value();

	    leccionesCargadas.push_back(lecActual);

	}
    }

    sort(leccionesCargadas.begin(), leccionesCargadas.end(), ordenarLecciones());
    leccionActual = 0;
    cambiarLeccion(leccionActual);
}

void EstadoMenuLecciones::update(){
    if((btn1 -> animacion -> finished()) && leccionActual == -1){
	listarLecciones();
    }
}

void EstadoMenuLecciones::cambiarLeccion(unsigned n){
    leccionActual = n;

    tConfTexto * confBtnTexto = new tConfTexto;
    confBtnTexto -> cadena = string("Lección nº") + boost::lexical_cast<string>(leccionesCargadas[n].indice);
    confBtnTexto -> rutaFuente = "media/fNormal.ttf";
    confBtnTexto -> tam = 36;
    confBtnTexto -> sombra = false;
    confBtnTexto -> alineacion = Texto::alignDer;
    btn1 -> setTexto(*confBtnTexto, -20, 7);

    delete confBtnTexto;

    textoDesc -> setText(leccionesCargadas[n] . descrip);
}

void EstadoMenuLecciones::draw() {
    imgFondo -> draw(0,0,1);
  
    // txtTitulo -> draw();
    pizarra -> draw();
    barraSuperior -> draw();
    barraInferior -> draw();
    btn1 -> draw();
    textoDesc -> draw();
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

    else if(boton == Gosu::msLeft){
	int x = padre -> input().mouseX();
	int y = padre -> input().mouseY();
	
	if(barraInferior -> clicked(x, y)){
	    padre -> cambiarEstado("estadoMenuSinFondo");
	}

    }
}
