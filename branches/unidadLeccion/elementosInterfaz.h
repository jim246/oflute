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


class elementoImagen{
    /// Contenedor de la imagen.
    boost::scoped_ptr<Gosu::Image> img;

    /// Destino gráfico
    Gosu::Graphics& g;

    /// Ruta de la imagen.
    string ruta;

    /// Posición de la imagen.
    int x, y, z;

    /// Flag que indica si hay que animar la imagen o no.
    bool animar;

    /// Puntero a la animación
    Animacion * A;
public:
    /**
     * @brief Crea un nuevo elementoImagen a partir de una ruta, una posición y unos atributos.
     *
     * @param g Destino gráfico.
     * @param ruta Ruta del fichero.
     * @param x Posición horizontal.
     * @param y Posición vertical.
     * @param z Profundidad.
     * @param animar Flag que indica si hay que animar el elemento.
     * @param wait Espera inicial de la animación.
     * @param duracion Duración de la animación.
     *
     */

    elementoImagen(Gosu::Graphics& g, string ruta, int x, int y, int z, 
		   bool animar = true, int wait = 0, int duracion = 30)
	: 
	g(g), ruta(ruta), x(x), y(y), z(z), animar(animar){
	
	img.reset(new Gosu::Image(g, Gosu::widen(ruta)));	

	if(animar){
	    lDEBUG << "** Se animará. Duración: " << duracion << endl;
	    A = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
	    A -> set (0, 0, 255);
	}

	lDEBUG << boost::format("** Imagen - ruta:'%s', x:%i, y:%i, z:%i, wait:%i") % ruta % x % y % z % wait << endl;
	
    }
    
    /**
     * @brief Dibuja el elemento en pantalla
     */

    void draw(){
	if(animar){
	    A -> update();
	    img -> draw(x,y,z,1,1,Gosu::Color(A -> get(0), 255, 255, 255));
	}else{
	    img -> draw(x,y,z);
	}
    }    

    ~elementoImagen(){
	if(animar)
	    delete A;
    }
};

class elementoTexto{
    boost::scoped_ptr<Texto> texto;
    bool animar;
    Animacion * A;
public:
    elementoTexto(Gosu::Graphics& g, string str, string rutaFuente, 
		  unsigned tam, 
		  int x, int y, double z, 
		  bool animar, int wait, int duracion, 
		  Gosu::Color color, unsigned alineacion=1, bool sombra=true, int opacidadSombra=80) 
	: animar(animar){

	texto.reset(new Texto(g, str, rutaFuente, tam, color, alineacion, sombra, opacidadSombra, x, y, z));
	if(animar){
	    A = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
	    A -> set (0, 0, 255);
	}

	lDEBUG << boost::format("** Texto - fuente:%s, tam:%i, x:%i, y:%i, z:%i, wait:%i, align: %i, sombra: %i\ntexto: %s") % rutaFuente % tam % x % y % z % wait % alineacion % sombra % str << endl;
    }

    void draw(){
	if(animar){
	    A -> update();
	    texto -> drawAlpha(A -> get(0));
	}else{
	    texto -> draw();
	}
    }


};


#endif /* _ELEMENTOSINTERFAZ_H_ */
