#include "nota.h"
#include "cancion.h"

#include <iomanip>


Nota::Nota(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c):
    altura(alt),
    duracion(negra),
    tiemposAcumulados(acum),
    cancionPadre(c)
{
    int margenIzquierdo = 181;		
    posY = 301 - (int)alt * 14.5;

//    double durNeg = 60 * 1000 / bpm; // en milisegundos

    // La posición en el momento inicial (medida en milisegundos que quedan para que suene)
    // Es una posición en el FUTURO
    posicionInicial = cancionPadre -> momentoInicial + 
	cancionPadre -> duracionNegra * tiemposAcumulados;

    // Cuántos píxeles se avanzan por milisegundo
    avanceMs = longitudNegra / cancionPadre -> duracionNegra;

    //posX = tiemposAcumulados * Nota::longitudNegra + margenIzquierdo;
    // assert(acumulado > Gosu::milliseconds());

    cout << "*** Creación de nota" << endl
	 << "* Duración de una negra: " << cancionPadre -> duracionNegra << "ms" << endl
	 << "* Momento inicial: " << cancionPadre -> momentoInicial << endl
	 << "* Tiempos acumulados: " << tiemposAcumulados << endl
	 << "* Avance por ms: " << avanceMs << endl
	;
}

void Nota::update(){

    // posX += cancionPadre -> diferencialHorizontal;
/*    cout << setprecision(30)
	 << "Posición inicial: " << posicionInicial << endl
	 << "Tiempo transcurrido: " <<  cancionPadre -> momentoTranscurrido << endl; //*/
    if(aparece){
	posX = 181 +
	    (posicionInicial - cancionPadre -> momentoTranscurrido) // tiempo que queda para que suene
	    * avanceMs;
	if(posX < 0){
	    cout << "llegué al límite: " << Gosu::milliseconds() << endl;
	    aparece=false;
	}
    }
}

void Nota::draw(){	     
    if(aparece) figura->draw( posX, posY, 1);		
}//*/

Negra::Negra(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c) : Nota(alt, g, acum, c){
    figura.reset(new Gosu::Image(*g, L"negra.png"));
    duracion = 1;  // Es decir, un tiempo = una negra
    cout << "** Se crea una negra en" << endl;
}   

Corchea::Corchea(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c) : Nota(alt, g, acum, c){
    figura.reset(new Gosu::Image(*g, L"corchea.png"));
    duracion = 0.5;  // Es decir, un tiempo = una negra
    cout << "** Se crea una corchea en" << endl;
}   


Blanca::Blanca(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c) : Nota(alt, g, acum, c){
    figura.reset(new Gosu::Image(*g, L"blanca.png"));
    duracion = 2;  // Es decir, un tiempo = una negra
    cout << "** Se crea una corchea en" << endl;
}

double Nota::longitudNegra = 150; // píxeles de ancho de una negra
//double Nota::duracionNegra = 1000;

double Nota::unidad = 1000;
double Nota::corchea = 0.5 * unidad;
double Nota::negra = 1 * unidad;
double Nota::blanca = 2 * unidad;
