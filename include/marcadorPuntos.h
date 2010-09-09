#ifndef _MARCADORPUNTOS_H_
#define _MARCADORPUNTOS_H_

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
using namespace std;

#include "elementosInterfaz.h"
#include "global.h"

class MarcadorPuntos{
public:
    MarcadorPuntos(Gosu::Graphics & g, string tituloCanc, string descCanc,
		   int puntosConseguidos, int puntosTotales){

	imgLogotipo.reset(new ElementoImagen(g,
					     "media/ofluteLogoGrande.png",
					     3, Animacion::tAlpha));
	
	imgLogotipo -> setXY(75, 100);
	imgLogotipo -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic);
	imgLogotipo -> animacion -> set(0, 0, 255);

	// CONFIGURACIÓN DEL SUBTÍTULO
	txtSubtitulo.reset(new ElementoTexto(g,
					     _("Puntuaciones"),
					     "media/fNormal.ttf",
					     34, Gosu::Color(0xffa4a4a4),
					     Texto::alignCentro,
					     true, 10, 3, 
					     Animacion::tAlpha));
	
	txtSubtitulo -> setXY(180, 425);
	txtSubtitulo -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 10);
	txtSubtitulo -> animacion -> set(0, 0, 255);

	// Título canción
	txtTituloCancion.reset(new ElementoTexto(g,
					     tituloCanc,
					     "media/fNormal.ttf",
					     54, Gosu::Color(0xffacc827),
					     Texto::alignIzq,
					     true, 10, 3, 
					     Animacion::tAlpha));
	
	txtTituloCancion -> setXY(379, 60);
	txtTituloCancion -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 20);
	txtTituloCancion -> animacion -> set(0, 0, 255);


	// Descripción de la canción
	txtDescCancion.reset(new ElementoTexto(g,
					     descCanc,
					     "media/fNormal.ttf",
					     20, Gosu::Color(0xff6a8800),
					     Texto::alignIzq,
					     true, 10, 3, 
					     Animacion::tAlpha));
	
	txtDescCancion -> setXY(379, 120);
	txtDescCancion -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 30);
	txtDescCancion -> animacion -> set(0, 0, 255);

	// Recuadro con el porcentaje
	imgRecuadroPorcentaje.reset(new ElementoImagen(g,
					     "media/marcoPuntos.png",
					     3, Animacion::tAlpha));
	
	imgRecuadroPorcentaje -> setXY(379, 152);
	imgRecuadroPorcentaje -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic, 40);
	imgRecuadroPorcentaje -> animacion -> set(0, 0, 255);

	float porcentaje = (float) puntosConseguidos / (float) puntosTotales * 100;
	// Descripción de la canción
	string cadenaPorcentaje = boost::lexical_cast<string>((int)porcentaje) + "%";
	txtPorcentaje.reset(new ElementoTexto(g,
					     cadenaPorcentaje,
					     "media/fNormal.ttf",
					     170, Gosu::Color(0xfffd7603),
					     Texto::alignCentro,
					     true, 10, 3, 
					     Animacion::tAlpha));
	
	txtPorcentaje -> setXY(558, 145);
	txtPorcentaje -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 50);
	txtPorcentaje -> animacion -> set(0, 0, 255);

	txtAciertos.reset(new ElementoTexto(g,
					    _("de aciertos"),
					    "media/fNormal.ttf",
					    40, Gosu::Color(0xfffd7603),
					     Texto::alignCentro,
					    true, 10, 3, 
					    Animacion::tAlpha));
	
	txtAciertos -> setXY(558, 300);
	txtAciertos -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 60);
	txtAciertos -> animacion -> set(0, 0, 255);

	string mensaje = "";
	if(porcentaje > 80){
	    mensaje = "¡Muy bien hecho! Eres un artista\nDebes estar orgulloso.";
	}
	else{
	    mensaje = "¡Debes esforzarte más!\nSé que puedes hacerlo mucho mejor";
	}

	txtMensaje.reset(new ElementoTexto(g,
					   mensaje,
					   "media/fNormal.ttf",
					   33, Gosu::Color(0xff05779d),
					   Texto::alignCentro,
					   true, 10, 3, 
					   Animacion::tAlpha));
	
	txtMensaje -> setXY(558, 375);
	txtMensaje -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 70);
	txtMensaje -> animacion -> set(0, 0, 255);
    }

    void draw(){
	imgLogotipo -> draw();
	txtSubtitulo -> draw();
	
	txtTituloCancion -> draw();
	txtDescCancion -> draw();
	
	imgRecuadroPorcentaje -> draw();
	txtPorcentaje -> draw();
	txtAciertos -> draw();
	txtMensaje -> draw();
    }
    
private:

    boost::scoped_ptr<ElementoImagen> imgLogotipo;
    boost::scoped_ptr<ElementoImagen> imgRecuadroPorcentaje;

    boost::scoped_ptr<ElementoTexto> txtSubtitulo;

    boost::scoped_ptr<ElementoTexto> txtTituloCancion;
    boost::scoped_ptr<ElementoTexto> txtDescCancion;
    boost::scoped_ptr<ElementoTexto> txtPorcentaje;
    boost::scoped_ptr<ElementoTexto> txtAciertos;
    boost::scoped_ptr<ElementoTexto> txtMensaje;
};

#endif /* _MARCADORPUNTOS_H_ */
