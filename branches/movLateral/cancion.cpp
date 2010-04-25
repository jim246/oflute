#include "cancion.h"

#define TIXML_USE_STL
#include "tinyxml.h"
#include "tinystr.h"

#include "boost/regex.hpp"
#include "boost/lexical_cast.hpp"

#include <string>

float bpm = 60;

Cancion::Cancion(Gosu::Graphics * g){
    cout << "** Se crea una canción nueva" << endl;
    cout << "*** Aquí se leería la lista de Notas de un fichero o similar" << endl;

    momentoInicial = Gosu::milliseconds();
    float desplazamiento = 2;

    TiXmlDocument doc;
    doc.LoadFile( "song1.xml");

    TiXmlHandle manejador( &doc );
    
    // Leemos el título
    TiXmlElement * elemento = manejador.FirstChild("Song").FirstChild("Title").ToElement();
    if(elemento){
	cout << "* Canción leída: " << elemento -> GetText() << endl;
    }

    // Leemos los BPM
    elemento = manejador.FirstChild("Song").FirstChild("BPM").ToElement();
    if(elemento){
	bpm = boost::lexical_cast<float>(elemento -> GetText());
	cout << "* BPM: " << bpm << endl;
    }

    // Finalmente leemos las notas
    elemento = manejador.FirstChild("Song").FirstChild("Notes").ToElement();
    if(!elemento) { cerr << "ERROR" << endl; }
    string notas = elemento -> GetText();

    // Calculamos la duración de una negra en milisegundos
    // Si se tardan 60 segundos en dar bpm pulsos, 1 pulso tarda 60/bpm segundos
    duracionNegra = 60.0 * 1000.0 / bpm;

    // La distancia entre la señal de sonar y el límite de la derecha 
    // de la pantalla son unos 650 píxeles.
    // Hay que calcular el tiempo que se tardaría en recorrer ese tramo
    tiempoSeguridad = 650.0 / Nota::longitudNegra * duracionNegra;

    cout << "* Duración negra: " << duracionNegra << "ms\n"
	 << "* Tiempo lado a lado: " << tiempoSeguridad << "ms" << endl;

    // Expresión regular para cazar las notas
    boost::regex myRegExp("(do|re|mi|fa|sol|la|si)(5|6)(r|b|n|c)");

    // Iterador de regexp para iterar por las diferentes notas captadas
    boost::sregex_iterator myIt(notas.begin(), notas.end(), myRegExp), itEnd;

    for(;myIt != itEnd; myIt++){
	string figura = (*myIt)[3];
	string alturaRead = string((*myIt)[1]) + string((*myIt)[2]);

	Nota::t_altura alturaLocal = Nota::Do5;

	if(alturaRead == "do5") alturaLocal = Nota::Do5;
	else if(alturaRead == "re5") alturaLocal = Nota::Re5;
	else if(alturaRead == "mi5") alturaLocal = Nota::Mi5;
	else if(alturaRead == "fa5") alturaLocal = Nota::Fa5;
	else if(alturaRead == "sol5") alturaLocal = Nota::Sol5;
	else if(alturaRead == "la5") alturaLocal = Nota::La5;
	else if(alturaRead == "si5") alturaLocal = Nota::Si5;
	else if(alturaRead == "do6") alturaLocal = Nota::Do6;
	else if(alturaRead == "re6") alturaLocal = Nota::Re6;

		
	if(figura == "r"){
//	    pilaNotas.push(new 
	}else if(figura == "b"){
	    pilaNotas.push(new Blanca(alturaLocal, g, desplazamiento, this));
	    desplazamiento += 2;
	}else if(figura == "n"){
	    pilaNotas.push(new Negra(alturaLocal, g, desplazamiento, this));
	    desplazamiento += 1;
	}else if(figura == "c"){
	    pilaNotas.push(new Corchea(alturaLocal, g, desplazamiento, this));
	    desplazamiento += 0.5;
	}else{
	    cerr << "Figura desconocida: " << figura << endl;
	}

	cout << "Nota: " << (*myIt)[1]
	     << ", octava: " << (*myIt)[2] 
	     << ", figura: " << (*myIt)[3] << endl << endl;
    } //*/


    /*
    pilaNotas.push(new Negra(g, desplazamiento, this));  desplazamiento += 1;
    pilaNotas.push(new Corchea(g, desplazamiento, this)); desplazamiento += 0.5;
    pilaNotas.push(new Corchea(g, desplazamiento, this)); desplazamiento += 0.5;
    pilaNotas.push(new Negra(g, desplazamiento, this));  desplazamiento += 1;
    pilaNotas.push(new Negra(g, desplazamiento, this));  desplazamiento += 1;
    pilaNotas.push(new Negra(g, desplazamiento, this));  desplazamiento += 1;
    pilaNotas.push(new Negra(g, desplazamiento, this));  desplazamiento += 1;
    pilaNotas.push(new Negra(g, desplazamiento, this));  desplazamiento += 1;
    pilaNotas.push(new Negra(g, desplazamiento, this));  desplazamiento += 1;//*/



}

void Cancion::comenzarCancion(){
    //momentoInicial = Gosu::milliseconds();
}

void Cancion::update(){
    t_actual = Gosu::milliseconds();

    while((pilaNotas.size() != 0) 
	  && 
	  ((pilaNotas.front() -> posicionInicial) - t_actual < tiempoSeguridad)){
	vectorNotasInstanciadas.push_back(pilaNotas.front());	
	pilaNotas.front()->instanciar();
	pilaNotas.pop();
    }

    vector<Nota*>::iterator i;
    for (i = vectorNotasInstanciadas.begin(); i != vectorNotasInstanciadas.end(); ++i)
    {
	(*i)-> update();
    }
}

void  Cancion::draw(){
    vector<Nota*>::iterator i;

    for (i = vectorNotasInstanciadas.begin(); i != vectorNotasInstanciadas.end(); ++i)
    {
	(*i)-> draw();
    }
}

Cancion::~Cancion(){
    vector<Nota*>::iterator i;

    for (i = vectorNotasInstanciadas.begin(); i != vectorNotasInstanciadas.end(); ++i)
    {
//	delete (*i);
    }
}
