#include "estadoCancion.h"
#include "juego.h"
#include "log.h"

#include <pugixml.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>



EstadoCancion::EstadoCancion(Juego * p)
    : Estado(p){
    
    lanzado = false;
    lDEBUG << Log::CON("EstadoCanción");
}

void EstadoCancion::lanzar(){
    distanciaPulso = 90;
    pugi::xml_document documento;
    pugi::xml_parse_result resultado;
    pugi::xml_node nodoActual, nodoVacio;

    resultado = documento.load_file("song1.xml");
    if(!resultado){
	lERROR << "ERROR";
    }

    bpm = boost::lexical_cast<int>(documento.child("Song").child("BPM").first_child().value());
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

    margenIzquierdo = 100;

    esperaInicial = 3; // 3 tiempos
    
    conjNotas.push_back(boost::shared_ptr<Nota>(new Nota(padre -> graphics(), 2)));
    
    
}

void EstadoCancion::update(){

}
bool entorno(float a, float b, float e){
    return (a >= b - e) && (a <= b + e);
}

void EstadoCancion::draw(){
    if(lanzado){
	double transcurrido = temporizador.elapsed();
	double pulsosTranscurridos = transcurrido / milisegundosPorPulso;

	//lDEBUG << transcurrido << " ms, " << transcurrido / milisegundosPorPulso << " pulsos";
	float estaNota, posHorizontal;
	(conjNotas[0]) ->  draw(margenIzquierdo, 300);
	(conjNotas[0]) ->  draw(margenIzquierdo + distanciaPulso, 300);
	(conjNotas[0]) ->  draw(margenIzquierdo + distanciaPulso * 2, 300);

	foreach(boost::shared_ptr<Nota>& N, conjNotas){
	    estaNota = N -> tiemposDelante;
	    
	    posHorizontal = margenIzquierdo +
		(estaNota + esperaInicial - pulsosTranscurridos) * distanciaPulso;

	    N -> draw(posHorizontal, 200);
	}//*/
    }
}

void EstadoCancion::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbP){
	temporizador.restart();
	lanzado = true;
    }
}

EstadoCancion::~EstadoCancion(){
    lDEBUG << Log::DES("EstadoCanción");
}
