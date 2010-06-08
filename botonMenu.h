/**
 * @file botonMenu.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
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


#ifndef _BOTONMENU_H_
#define _BOTONMENU_H_

#include <string>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include <Gosu/Gosu.hpp>

#include "customFont.h"
#include "log.h"

using namespace std;

/**
 * @class BotonMenu
 *
 * @brief Clase para los botones dinámicos del menú
 *
 * Encapsula los elementos gráficos que forman un botón del menú: el fondo, el texto en blanco y su sombra.
 *
 * El botón tiene un fondo al que se le aplica una tinta de color.
 * Por defecto, el botón tiene una altura de 51 píxeles y un tamaño de texto de 34 puntos, centrado verticalmente, pero es posible indicar un tamaño de texto menor. En ese caso,
 * la altura del botón se ajustará de forma acorde.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class BotonMenu{
    /// Referencia al objeto gráficos en el que pintar el botón.
    Gosu::Graphics& graphics;

    /// Color del fondo del botón.
    Gosu::Color color;

    /// Texto del botón.
    std::string texto;

    /// Tamaño del texto, por defecto 34.
    int tamanyo;

    /// Altura del botón, por defecto 51.
    int altura;

    /// Margen superior del botón (espacio desde el borde al texto)
    int margenSup;

    /// Fuentes del texto.
    boost::scoped_ptr<customFont> fuente;
    
    /// Fuente de la sombra.
    boost::scoped_ptr<customFont>fuenteSombra;

    /// Imagen del fondo.
    boost::scoped_ptr<Gosu::Image> imagen;

    // Coordenadas para controlar la última posición.
    int lastX, lastY; ///< WAT

    /// Indica si hay sombra o no
    bool sombra;

public:
    /**
     * @brief Crea un nuevo botón para el menú
     *
     * Recibe una referencia al destino gráfico, el texto y el botón del color. Inicializa las fuentes para el texto y la sombra, y la imagen de fondo.
     * 
     */

    BotonMenu (Gosu::Graphics &graphics,
	       std::string texto,
	       Gosu::Color color,
	       int altura = 51,
	       bool sombra = true
	) : graphics(graphics), color(color), texto(texto), lastX(0), lastY(0), sombra(sombra) {

	// El tamaño máximo de un botón, por ahora, es de 51 píxeles
//	if(altura > 51) altura = 51;

	// El tamaño del texto será dos tercios la altura del botón
	tamanyo = 2 * 51 / 3;

	// El 1/3 de espacio que sobra se reparte arriba y abajo, por lo que el margen superior será un sexto (y pico ;) )
	margenSup = 51 / 6 - 2;

	fuente.reset(new customFont(graphics, L"media/fNormal.ttf", tamanyo));
	if(sombra) fuenteSombra.reset(new customFont(graphics, L"media/fNormal.ttf", tamanyo));
	imagen.reset(new Gosu::Image(graphics, L"media/btnTemplate.png", 0, 0, 800, altura));

	lDEBUG << Log::CON("BotonMenu");	    
    }

    /**
     * @brief Dibuja el botón en la posición indicada.
     */

    void draw(int x, int y, Gosu::ZPos z){
	lastX = x;
	lastY = y;
	imagen -> draw(x, y, z, 1, 1, color);

	int ancho = fuente -> textWidth(texto);

	fuente -> draw(texto, 800/2 - ancho/2, y+margenSup, z + 0.1, Gosu::Color(255,255,255,255));

	if(sombra){
	    int offsetShadow[] = {1,2};
	    fuenteSombra -> draw(texto, 800/2 - ancho/2 + offsetShadow[0], y+margenSup + offsetShadow[1], z, Gosu::Color(80,0,0,0));
	}
    }
    
    /**
     * @brief Comprueba si el botón ha sido pulsado
     *
     * Teniendo en cuenta el último lugar en el que fue dibujado el botón en pantalla, comprueba si el click definido 
     * por los parámetros x e y tuvo lugar dentro del botón.
     *
     * @param x Posición horizontal del click.
     * @param y Posición vertical del click.
     *
     */

    bool clicked(int x, int y){
	if((x >= lastX) && (x <= lastX + (int) imagen -> width()) &&
	   (y >= lastY) && (y <= lastY + (int) imagen -> height())){
	    return true;
	}else{
	    return false;
	}
    }

    ~BotonMenu(){
	lDEBUG << Log::DES("BotonMenu");
    }

};

#endif /* _BOTONMENU_H_ */
