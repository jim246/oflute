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

    imagenPartitura.reset( new Gosu::Image(padre -> graphics(),
					   L"media/partitura.png"));

    resultado = documento.load_file("song1.xml");
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

    margenIzquierdo = 100;

    esperaInicial = 3; // 3 tiempos
    
    conjNotas.push_back(boost::shared_ptr<Nota>(new Nota(padre -> graphics(), Do5, Negra, 2)));
    
    
}

void EstadoCancion::update(){

}
bool entorno(float a, float b, float e){
    return (a >= b - e) && (a <= b + e);
}

void EstadoCancion::draw(){
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
