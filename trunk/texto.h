/**
 * @file texto.h
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

#ifndef _TEXTO_H_
#define _TEXTO_H_

#include <iostream>
#include <string>
#include <vector>

#include <Gosu/Gosu.hpp>
#include <boost/foreach.hpp>

#include "customFont.h"

using namespace std;

/**
 * @class Texto
 *
 * @brief Pinta un cuadro de texto
 *
 * 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Texto{

    /// Objeto que será el destino gráfico
    Gosu::Graphics& graphics;

    /// Objetos que pintan el texto
    boost::scoped_ptr<customFont> fuente, fuenteSombra;

    /// Texto a escribir
    string texto;

    /// Texto dividido en líneas
    vector<string> lineas;

    /// Tamaño del texto
    unsigned tam;

    /// Color del texto
    Gosu::Color color;

    /// Alineación, 1 = izquierda, 2 = centrado, 3 = derecha
    unsigned alineacion;

    /// Existencia de la sombra
    bool sombra;

    /// Opacidad de la sombra
    unsigned opacidadSombra;

    /** Posición del texto.
	Para el texto justificado a la izquierda, es la esquina sup izq.
	Para el texto justif. a la derecha, es la esquina sup der.
	Para el texto centrado, es la posición central superior
    **/
    unsigned x, y;

    /// Profundidad
    double z;

    ///Desplazamiento de la sombra respecto al texto
    int offsetShadow[2];


    // función adaptada de
    // http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
    void dividirTexto(){
	
	string::size_type lastPos = texto.find_first_not_of('\n', 0);
	// Find first "non-delimiter".
	string::size_type pos     = texto.find_first_of('\n', lastPos);
	
	while (string::npos != pos || string::npos != lastPos)
	{
	    // Found a token, add it to the vector.
	    lineas.push_back(texto.substr(lastPos, pos - lastPos));
	    // Skip '\n'.  Note the "not_of"
	    lastPos = texto.find_first_not_of('\n', pos);
	    // Find next "non-delimiter"
	    pos = texto.find_first_of('\n', lastPos);
	}	

    }

    
public:
    /**
     * @brief Crea un nuevo cuadro de texto
     *
     * @param graphics El objeto gráfico.
     * @param texto Texto a escribir.
     * @param rutaFuente Ruta a la fuente que se usará para pintar el texto.
     * @param tam Tamaño del texto.
     * @param color Color del texto.
     * @param alineacion Alineación del texto. 1 = izquierda, 2 = centrado, 3 = derecha.
     * @param sombra Si hay que imprimir sombra o no.
     * @param opSombra Opacidad de la sombra. Irrelevante si no hay sombra.
     * @param x Posición horizontal.
     * @param y Posición vertical.
     * @param z Profundidad.
     *
     */

    Texto(Gosu::Graphics& graphics, 
	  string texto, string rutaFuente, unsigned tam, Gosu::Color color = Gosu::Color::WHITE,
	  unsigned alineacion = 1, 
	  bool sombra = false, unsigned opSombra = 80, int x = 0, int y = 0, int z = 0) 
	: 
	graphics(graphics), texto(texto), tam(tam), color(color), 
	alineacion(alineacion), sombra(sombra), opacidadSombra(opSombra), x(x), y(y), z(z){
	
	fuente.reset ( new customFont(graphics, Gosu::widen(rutaFuente), tam));

	dividirTexto();


	if(sombra){
	    fuenteSombra.reset ( new customFont(graphics, Gosu::widen(rutaFuente), tam));
	}
	offsetShadow[0] = 1;
	offsetShadow[1] = 2;



	//*/
    }
    void update(){

    }

    /**
     * @brief Pinta el texto con la opacidad al máximo por defecto.
     *
     */

    void draw(){
	drawAlpha(255);
    }

    /**
     * @brief Pinta el texto con la opacidad indicada.
     *
     * @param a La opacidad (alpha) con la que pintar el texto.
     *
     */

    void drawAlpha(int a){
	
	int salto = fuente -> saltoLinea();
	short i = 0;
	BOOST_FOREACH(string& s, lineas)
	{

	    int destX = 0;

	    // Alineación a la izquierda
	    if(alineacion == 1){
		destX = x;
	    }
	    // Alineación a la derecha
	    else if(alineacion == 3){
		destX = x - fuente -> textWidth(s);
	    }

	    // Centrado
	    else{
		destX = x - fuente -> textWidth(s) / 2;
	    }
	    color.setAlpha(a);
	    fuente -> draw(s, destX, y + salto * i, z + 0.1, color);
	    
	    if(sombra){
		fuenteSombra -> draw(s, destX + offsetShadow[0], y + salto * i + offsetShadow[1],
				     z, Gosu::Color(opacidadSombra * a / 255, 0, 0, 0));
	    }

	    i++;
	} 

	//*/
	
    }

    /**
     * @brief Pinta el texto en la profundidad indicada.
     *
     * @param z_ La profundidad en la que pintae l texto.
     *
     */

    void draw(int z_){
	z = z_;
	draw();
    }

    /**
     * @brief Pinta el texto en la posición indicada
     *
     */

    void draw(int x_, int y_, int z_){
	x = x_;
	y = y_;
	z = z_;
	draw();
    }


};

#endif /* _TEXTO_H_ */