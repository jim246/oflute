/**
 * @file texto.cpp
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


#include "texto.h"

int Texto::dividirTexto(){
	
    string::size_type lastPos = texto.find_first_not_of('\n', 0);
    // Find first "non-delimiter".
    string::size_type pos     = texto.find_first_of('\n', lastPos);
	
    lineas.clear();
    while (string::npos != pos || string::npos != lastPos)
    {
	// Found a token, add it to the vector.
	lineas.push_back(texto.substr(lastPos, pos - lastPos));
	// Skip '\n'.  Note the "not_of"
	lastPos = texto.find_first_not_of('\n', pos);
	// Find next "non-delimiter"
	pos = texto.find_first_of('\n', lastPos);
    }	
    return lineas.size();
}

Texto::Texto(Gosu::Graphics& graphics, 
      string texto, string rutaFuente, unsigned tam, Gosu::Color color,
      unsigned alineacion, 
      bool sombra, unsigned opSombra, int x, int y, int z) 
    : 
    graphics(graphics), texto(texto), tam(tam), color(color), 
    alineacion(alineacion), sombra(sombra), opacidadSombra(opSombra), 
    x(x), y(y), z(z), rutaFuente(rutaFuente){
	
    poblarVectores();
}

void Texto::poblarVectores(){
    dividirTexto();

    fuente.reset(new Gosu::Font(graphics, Gosu::widen(rutaFuente), tam));

    offsetShadow[0] = 1;
    offsetShadow[1] = 2;
}

void Texto::update(){ }

void Texto::draw(){
    drawAlpha(255);
}

void Texto::setText(string s){
    texto = s;
    poblarVectores();
}


void Texto::drawAlpha(int a){
	
    int salto = tam + 5;
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
	    destX = x - fuente -> textWidth(Gosu::widen(s));
	}

	// Centrado
	else{
	    destX = x - fuente -> textWidth(Gosu::widen(s)) / 2;
	}

	color.setAlpha(a);
	fuente -> draw(Gosu::widen(s), destX, y + salto * i, z + 0.1, 1, 1, color);
	    
	if(sombra){
	    fuente -> draw(Gosu::widen(s), destX + offsetShadow[0], y + salto * i + offsetShadow[1],
			   z, 1, 1, Gosu::Color(opacidadSombra * a / 255, 0, 0, 0));
	}

	i++;
    } 

    //*/
	
}

void Texto::draw(int z_){
    z = z_;
    draw();
}

void Texto::draw(int x_, int y_, int z_, int a_){
    x = x_;
    y = y_;
    z = z_;
    drawAlpha(a_);
}
