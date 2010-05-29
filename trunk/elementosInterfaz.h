/**
 * @file elementosInterfaz.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * 
 * 
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef _ELEMENTOSINTERFAZ_H_
#define _ELEMENTOSINTERFAZ_H_

#include <boost/scoped_ptr.hpp>
#include <boost/format.hpp>

#include <Gosu/Gosu.hpp>

#include "animacion.h"
#include "texto.h"
#include "log.h"

struct tConfTexto{
    string cadena;
    string rutaFuente;
    unsigned tam;
    Gosu::Color color;
    unsigned alineacion;
    bool sombra;
    int opacidadSombra;
    tConfTexto() : color(Gosu::Color(255,255,255,255)), 
		   alineacion(Texto::alignIzq),
		   sombra(true),
		   opacidadSombra(80) { }
};

struct tConfAnim{
    int inicialX, inicialY, inicialA;
    int finalX, finalY, finalA;
    int z;
    Animacion::atribAnim animar;
    int wait, duracion;

    tConfAnim() :
	inicialX(0), inicialY(0), inicialA(0),
	finalX(0), finalY(0), finalA(255),
	z(0),
	animar(Animacion::tNada),
	wait(0), duracion(30) { }
};


class Elemento{

    Animacion::atribAnim animar;

    int finalX;
    int finalY;
    int finalAlpha;

    double z;

    int inicialX;
    int inicialY;
    int inicialAlpha;

    void setupAnimacion(int wait, int duracion){
	if(animar != Animacion::tNada){
	    lDEBUG << "** Se animará. Attrib: " << animar << endl;
	    
	    if(animar == Animacion::tAlpha){
		animacion = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
		animacion -> set (0, inicialAlpha, finalAlpha);
	    }
	    
	    else if(animar == Animacion::tPos){
		animacion = new Animacion(2, duracion, Animacion::tEaseOutQuad, wait);
		animacion -> set(0, inicialX, finalX);
		animacion -> set(1, inicialY, finalY);
	    }
	    
	    else if(animar == Animacion::tAlphaPos){
		animacion = new Animacion(3, duracion, Animacion::tEaseOutQuad, wait);
		animacion -> set(0, inicialAlpha, finalAlpha);
		animacion -> set(1, inicialX, finalX);
		animacion -> set(2, inicialY, finalY);
	    }
	}else{
	    animacion = 0;
	}
    }

public:
    Animacion * animacion;

    Elemento(Animacion::atribAnim animar,
	     int fX, int fY, int fA, double z,
	     int wait, int duracion,
	     int iX, int iY, int iA
	)

	: animar(animar), finalX(fX), finalY(fY), finalAlpha(fA), z(z),
	  inicialX(iX), inicialY(iY), inicialAlpha(iA)
	{
	    setupAnimacion(wait, duracion);
	} // Fin constructor

    Elemento(tConfAnim t) 
	: animar(t.animar),
	finalX(t.finalX), finalY(t.finalY), finalAlpha(t.finalA),
	z(t.z),
	inicialX(t.inicialX), inicialY(t.inicialY), inicialAlpha(t.inicialA)

	{
	    setupAnimacion(t.wait, t.duracion);
	}
    

    virtual void drawEnd(int x, int y, double z, int a) = 0;

    void draw(){
	int x1, y1, a1;

	if(animar != Animacion::tNada){
	    animacion -> update();

	    if(animar == Animacion::tAlpha){
		a1 = animacion -> get(0);
		x1 = finalX;
		y1 = finalX;
	    }

	    else if(animar == Animacion::tPos){
		a1 = finalAlpha;
		x1 = animacion -> get(0);
		y1 = animacion -> get(1);
	    }

	    else{
		a1 = animacion -> get(0);
		x1 = animacion -> get(1);
		y1 = animacion -> get(2);
	    }
	}else{
	    x1 = finalX;
	    y1 = finalY;
	    a1 = finalAlpha;
	}

	drawEnd(x1, y1, z, a1);
    }    

    ~Elemento(){
	if(animar != Animacion::tNada){
	    delete animacion;
	}
    }
};

/**
 * @class elementoImagen
 *
 * @brief Representa una imagen con una animación asociada.
 *
 * Útil para representar interfaces.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class elementoImagen : public Elemento{
    /// Contenedor de la imagen.
    boost::scoped_ptr<Gosu::Image> img;

    /// Ruta de la imagen.
    string ruta;

public:
    /**
     * @brief Crea un nuevo elementoImagen a partir de una ruta, una posición y unos atributos.
     *
     * @param g Destino gráfico.
     * @param ruta Ruta del fichero.
     * @param x Posición horizontal final.
     * @param y Posición vertical final.
     * @param z Profundidad.
     * @param animar 
     * @param wait Espera inicial de la animación.
     * @param duracion Duración de la animación.
     *
     */

    elementoImagen(Gosu::Graphics& g, string ruta, 
		   int fX, int fY, int fA,
		   double z, 
		   Animacion::atribAnim animar = Animacion::tNada,
		   int wait = 0, int duracion = 30,
		   int iX = 0, int iY = 0, int iA = 0
	)
	: 
	Elemento(animar, fX, fY, fA, 
		 z, wait, duracion, 
		 iX, iY, iA),
	ruta(ruta)
	
	{
	    img.reset(new Gosu::Image(g, Gosu::widen(ruta)));	
	}
    
    elementoImagen(Gosu::Graphics & g, string ruta, tConfAnim t)
	:
	Elemento(t.animar, t.finalX, t.finalY, t.finalA, t.z,
		 t.wait, t.duracion,
		 t.inicialX, t.inicialY, t.inicialA),
	ruta(ruta)

	{
	    img.reset(new Gosu::Image(g, Gosu::widen(ruta)));
	}

    /**
     * @brief Dibuja el elemento en pantalla
     */
    void drawEnd(int x, int y, double z, int a){
	img -> draw(x,y,z,1,1, Gosu::Color(a, 255, 255, 255));
    }
    
};

class elementoTexto : public Elemento{
    boost::scoped_ptr<Texto> texto;

public:
    elementoTexto(Gosu::Graphics& g, string str, string rutaFuente, 
		  unsigned tam, Gosu::Color color, 
		  unsigned alineacion, bool sombra, int opacidadSombra,

		  int fX, int fY, int fA, 
		  double z, 
		  Animacion::atribAnim animar = Animacion::tNada,
		  int wait = 0, int duracion = 30,
		  int iX = 0, int iY = 0, int iA = 0
	
	) : Elemento(animar, fX, fY, fA, z, wait, duracion, iX, iY, iA)	{
	
	texto.reset(new Texto(g, str, rutaFuente, 
			      tam, color, alineacion, 
			      sombra, opacidadSombra));
    }
    
    void drawEnd(int x, int y, double z, int a){
	texto -> draw(x, y, z, a);
    }

    void setText(string s){
	lDEBUG << LOC() << VARV(s);
	texto -> setText(s);
    }
    
};



/**
 * @class elementoCombinado
 *
 * @brief Combina una imagen de fondo con un texto encima
 *
 * 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class ElementoCombinado : public Elemento{
    boost::scoped_ptr<Texto> texto;
    
    int textoX, textoY;

    boost::scoped_ptr<Gosu::Image> imagen;

    Gosu::Graphics & g;

public:

    ElementoCombinado(Gosu::Graphics & g,
		      int fX, int fY, int fA,
		      double z,
		      Animacion::atribAnim animar = Animacion::tNada,
		      int wait = 0, int duracion = 30,
		      int iX = 0, int iY = 0, int iA = 0)
	: 
	Elemento(animar, fX, fY, fA, z, wait, duracion, iX, iY, iA), g(g) {

    }

    ElementoCombinado(Gosu::Graphics & g, tConfAnim t)
	:
	Elemento(t.animar, t.finalX, t.finalY, t.finalA, t.z,
		 t.wait, t.duracion,
		 t.inicialX, t.inicialY, t.inicialA), g(g){

    }

    void setTexto(string str, string rutaFuente,
		  unsigned tam, Gosu::Color color,
		  unsigned alineacion, bool sombra, int opacidadSombra,
		  int tX, int tY){

	texto.reset(new Texto(g, str, rutaFuente,
			      tam, color, alineacion,
			      sombra, opacidadSombra));

	textoX = tX;
	textoY = tY;
    }

    void setTexto(tConfTexto t, int x, int y){
	setTexto(t.cadena, t.rutaFuente,
		 t.tam, t.color,
		 t.alineacion, t.sombra, t.opacidadSombra,
		 x, y);

    }
    void setTextoXY(int x, int y){
	textoX = x;
	textoY = y;
    }

    void setImagen(string ruta){
	imagen.reset(new Gosu::Image(g, Gosu::widen(ruta)));
    }

    void drawEnd(int x, int y, double z, int a){
	imagen -> draw(x,y,z,1,1,Gosu::Color(a,255,255,255));
	switch(texto -> getAlineacion()){
	case Texto::alignIzq:
	    texto -> draw(x + textoX, y + textoY, z + 0.1, a);
	    break;

	case Texto::alignCentro:
	    texto -> draw(x + imagen -> width() / 2 + textoX, y + textoY, z + 0.1, a);
	    break;

	case Texto::alignDer:
	    texto -> draw(x + imagen -> width() + textoX, y + textoY, z + 0.1, a);
	    break;
	}
    }

};

#endif /* _ELEMENTOSINTERFAZ_H_ */
