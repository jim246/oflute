#include "estadoCancion.h"

#include "log.h"

#include <pugixml.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/format.hpp>
#include <boost/bind.hpp>

#include <algorithm>


Cancion::Cancion(Gosu::Graphics & g, string ruta) : g(g), ruta(ruta) {
    
    lanzado = false;
    lDEBUG << Log::CON("EstadoCanción") << " (" << ruta << ")";
    estadoActual = e1;
    puntos = 0;

}

void Cancion::lanzar(){
    distanciaPulso = 200;
    margenIzquierdo = 150;

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

    for (int i = 0; i < 10; ++i)
    {
	lDEBUG << boost::format("%i : %f") % i % Nota::devolverAltura((t_altura)i);
    }

    sistemaPartc . reset(new SistemaParticulas(g, 150, 150, // cantidad y duración
					       80, 0.5,  // distancia y escala
					       Gosu::Color(255,255,255)));


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
    boost::regex myRegExp("(do|re|mi|fa|sol|la|si|xx)(5|6|0)(r|b|n|c)");

    // Iterador de regexp para iterar por las diferentes notas captadas
    boost::sregex_iterator myIt(cadenaNotas.begin(), cadenaNotas.end(), myRegExp), itEnd;

    float acumulado = 2;
    
    for(;myIt != itEnd; myIt++){
	string figura = (*myIt)[3];
	string alturaRead = string((*myIt)[1]) + string((*myIt)[2]);

	t_altura alturaLocal = Do5;
	t_figura figuraLocal = Negra;
	float duracionLocal = 0;

	if(alturaRead == "do5") alturaLocal = Do5;
	else if(alturaRead == "re5") alturaLocal = Re5;
	else if(alturaRead == "mi5") alturaLocal = Mi5;
	else if(alturaRead == "fa5") alturaLocal = Fa5;
	else if(alturaRead == "sol5") alturaLocal = Sol5;
	else if(alturaRead == "la5") alturaLocal = La5;
	else if(alturaRead == "si5") alturaLocal = Si5;
	else if(alturaRead == "do6") alturaLocal = Do6;
	else if(alturaRead == "re6") alturaLocal = Re6;
	else if(alturaRead == "xx0") alturaLocal = Silencio;

	if(figura == "r"){
	    figuraLocal = Redonda;
	    duracionLocal = 4;
	}else if(figura == "b"){
	    figuraLocal = Blanca;
	    duracionLocal = 2;
	}else if(figura == "n"){
	    figuraLocal = Negra;
	    duracionLocal = 1;
	}else if(figura == "c"){
	    figuraLocal = Corchea;
	    duracionLocal = 0.5;
	}

	lDEBUG << boost::format("Nota: %s %s, durLocal: %f") % alturaRead % figura % duracionLocal;

	conjNotas.push_back(boost::shared_ptr<Nota>(new Nota(g, alturaLocal, figuraLocal, acumulado)));
	acumulado += duracionLocal;
	lDEBUG << boost::format("%|30| %||") % "Acumulado: " % acumulado;
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

	    analizador.iniciar();

	}
    }else if (estadoActual == e2){
	notaLeida = analizador . notaActual();

	if(lanzado){
	    sistemaPartc -> update();

	    double transcurrido = temporizador.elapsed();
	    double pulsosTranscurridos = transcurrido / milisegundosPorPulso;

	    float estaNota, posHorizontal;

	    foreach(boost::shared_ptr<Nota>& N, conjNotas){
		estaNota = N -> tiemposDelante;
		
		posHorizontal = (estaNota + esperaInicial - pulsosTranscurridos) * distanciaPulso;

		/*
		  Para ver qué nota corresponde en cada momento,
		  hacemos el siguiente cálculo.  MargenIzquierdo es el
		  punto en el que se empieza a tocar la nota. Así,
		  para que una nota sea la que debe tocarse en ese
		  momento, debe estar en, o a la izquierda del margen,
		  y su punto final (es decir, el punto inicial +
		  duración) debe estar a la derecha del margen (ya que
		  si está a la izquierda es que ya ha acabado su
		  tiempo.


		 */
		if(posHorizontal <= margenIzquierdo
		   &&
		   margenIzquierdo < (posHorizontal + Nota::devolverDuracion(N -> figura) * distanciaPulso) ){
		    notaEnLinea = N -> altura;
		}

		N -> updatePos(posHorizontal);		
		
	    }

	    if(notaEnLinea == notaLeida){
		puntos += 10;
		sistemaPartc -> on();
	    }else{
		sistemaPartc -> off();
	    }


	    barraSuperior -> setText(boost::lexical_cast<string>(puntos));
	}//*/
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
	    resalteNotaActual -> draw(0, Nota::devolverAltura(notaLeida)+258.5, 5);
	}
	if(lanzado){
	    sistemaPartc -> draw(margenIzquierdo, Nota::devolverAltura(notaEnLinea) + 283);
	    for_each(conjNotas.begin(), conjNotas.end(), boost::bind(&Nota::draw, _1));
	}
    }


}

void Cancion::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbP){
	temporizador.restart();
	lanzado = true;
	lDEBUG << "Lanzado!!";
    }

    else if(boton == Gosu::kbEscape){
	analizador.detener();
    }

}

Cancion::~Cancion(){
    lDEBUG << Log::DES("EstadoCanción");
}
