#include "estadoCancion.h"

#include "log.h"

#include <pugixml.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>



Cancion::Cancion(Gosu::Graphics & g, string ruta) : g(g), ruta(ruta) {
    
    lanzado = false;
    lDEBUG << Log::CON("EstadoCanción") << " (" << ruta << ")";
    estadoActual = e1;
}

void Cancion::lanzar(){
    distanciaPulso = 90;
    margenIzquierdo = 100;
    esperaInicial = 3; // 3 tiempos

    resalteNotaActual.reset( new Gosu::Image(g, L"media/cancionesIndicadorNota.png"));

    barraProgresoFondo.reset( new ElementoImagen(g, "media/cancionesBarraProgreso.png",
						 3, Animacion::tAlpha));
    barraProgresoFondo -> animacion = new Animacion(1, 20, Animacion::tEaseOutQuad, 30);
    barraProgresoFondo -> animacion -> set(0,0,255);
    barraProgresoFondo -> setXY(180, 560);

    barraProgreso.reset(new Gosu::Image(g, L"media/cancionesBarraRelleno.png"));

    imagenPartitura.reset( new ElementoImagen(g, "media/partitura.png", 3, Animacion::tAlpha));
    imagenPartitura -> animacion = new Animacion(1, 20, Animacion::tEaseOutQuad, 20);
    imagenPartitura -> animacion -> set (0, 0, 255);
    imagenPartitura -> setXY(0, 200);


    barraSuperior.reset(new ElementoCombinado(g, Animacion::tPos, 3));
    barraSuperior -> setImagen("media/cancionesTopBar.png");
    barraSuperior -> setTexto("00000", "media/fNormal.ttf",
			      49, 0xffffffff,
			      Texto::alignCentro,
			      true, 33,
			      0, 0);
    
    barraSuperior -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 0);
    barraSuperior -> animacion -> set(0,0,0);
    barraSuperior -> animacion -> set(1, -139, 0);


    barraInferior.reset(new ElementoCombinado(g, Animacion::tPos, 3));
    barraInferior -> setImagen("media/cancionesBottomBar.png");
    barraInferior -> setTexto("Progreso total:", "media/fNormal.ttf",
			      32, 0xffffffff,
			      Texto::alignIzq,
			      true, 39,
			      20, 90);

    barraInferior -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 10);
    barraInferior -> animacion -> set(0,0,0);
    barraInferior -> animacion -> set(1, 600, 461); //*/

    parsear ();
}
void Cancion::parsear(){
    pugi::xml_document documento;
    pugi::xml_parse_result resultado;
    pugi::xml_node nodoActual, nodoVacio;

    resultado = documento.load_file(ruta.c_str());
    if(!resultado){
	lERROR << "ERROR";
    }

    bpm = boost::lexical_cast<int>(documento.child("Song").child("BPM").first_child().value());

    string cadenaNotas = documento.child("Song").child("Notes").first_child().value();

    // Expresión regular para cazar las notas
    boost::regex myRegExp("(do|re|mi|fa|sol|la|si)(5|6)(r|b|n|c)");

    // Iterador de regexp para iterar por las diferentes notas captadas
    boost::sregex_iterator myIt(cadenaNotas.begin(), cadenaNotas.end(), myRegExp), itEnd;

    for(;myIt != itEnd; myIt++){
	string figura = (*myIt)[3];
	string alturaRead = string((*myIt)[1]) + string((*myIt)[2]);

	t_altura alturaLocal = Do5;

	if(alturaRead == "do5") alturaLocal = Do5;
	else if(alturaRead == "re5") alturaLocal = Re5;
	else if(alturaRead == "mi5") alturaLocal = Mi5;
	else if(alturaRead == "fa5") alturaLocal = Fa5;
	else if(alturaRead == "sol5") alturaLocal = Sol5;
	else if(alturaRead == "la5") alturaLocal = La5;
	else if(alturaRead == "si5") alturaLocal = Si5;
	else if(alturaRead == "do6") alturaLocal = Do6;
	else if(alturaRead == "re6") alturaLocal = Re6;

    }


    lDEBUG << "BPM: " << bpm;
    milisegundosPorPulso = 1 / (bpm / 60.) * 1000;
    lDEBUG << "El espacio entre pulsos es " << milisegundosPorPulso << " ms";


    lDEBUG << "El intervalo de refresco es " << REFRESCO << " ms";
    frecuencia = 1000./REFRESCO;
    lDEBUG << "La frecuencia es de " << frecuencia << " Hz, es decir, salen " << frecuencia
	   << " fotogramas por segundo.";

    lDEBUG << "La distancia de un pulso (espacio entre dos negras) es " << distanciaPulso << " px";
    lDEBUG << "Con " << bpm << " pulsos por minuto, se recorren " 
	   << distanciaPulso * bpm << " píxeles por minuto, ó " 
	   << distanciaPulso * bpm / 60. << " píxeles por segundo.";

    
    conjNotas.push_back(boost::shared_ptr<Nota>(new Nota(g, Do5, Negra, 2)));
    px=0;
}

void Cancion::update(){
    if(estadoActual == e1){
	if(barraSuperior -> animacion -> finished() &&
	   barraInferior -> animacion -> finished() &&
	   imagenPartitura -> animacion -> finished() &&
	   barraProgresoFondo -> animacion -> finished() )
	{
	    lDEBUG << "Animaciones de interfaz terminadas.";
	    estadoActual = e2;

	    if (!controlSonido . configurarFlujo(analizador)){
		lERROR << " No se pudo configurar el flujo.";
	    }

	    if(!controlSonido . iniciarFlujo()){
		lERROR << " No se pudo iniciar el análisis.";
	    }
	}
    }else if (estadoActual == e2){
	notaLeida = analizador . notaActual();
    }

    
}



bool entorno(float a, float b, float e){
    return (a >= b - e) && (a <= b + e);
}

void Cancion::draw(){
    barraSuperior -> draw();
    barraInferior -> draw();
    imagenPartitura -> draw();
    barraProgresoFondo -> draw();

    if(estadoActual == e2){
	barraProgreso -> draw(184, 564, 5, 0.5, 1);
	
	if(notaLeida != Silencio){
	    resalteNotaActual -> draw(0, 260+(9-notaLeida)*20, 5);
	}
    }
    /*
    imagenPartitura -> draw(0, 200, 3);
    if(lanzado){
	double transcurrido = temporizador.elapsed();
	double pulsosTranscurridos = transcurrido / milisegundosPorPulso;

	//lDEBUG << transcurrido << " ms, " << transcurrido / milisegundosPorPulso << " pulsos";
	float estaNota, posHorizontal;
	foreach(boost::shared_ptr<Nota>& N, conjNotas){
	    estaNota = N -> tiemposDelante;
	    
	    posHorizontal = margenIzquierdo +
		(estaNota + esperaInicial - pulsosTranscurridos) * distanciaPulso;

	    N -> draw(posHorizontal, 200);
	}
    }//*/
}

void Cancion::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbP){
	temporizador.restart();
	lanzado = true;
    }

    else if(boton == Gosu::kbEscape){
	controlSonido . detenerFlujo();
    }

    else if(boton == Gosu::kbDown){
	px ++;
	lDEBUG << VARV(px);
    }
}

Cancion::~Cancion(){
    lDEBUG << Log::DES("EstadoCanción");
}
