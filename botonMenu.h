// botonMenu.h --- Clase para los botones dinámicos del menú

// Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>

// Autor: José Tomás Tocino García

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.


#ifndef _BOTONMENU_H_
#define _BOTONMENU_H_

#include <boost/lexical_cast.hpp>

#include <Gosu/Gosu.hpp>
#include "customFont.h"

#include <string>
#include <iostream>

using namespace std;

#define TAMANYO 34

class BotonMenu{
    Gosu::Graphics& graphics;
    Gosu::Color color;
    std::string texto;

    boost::scoped_ptr<customFont> fuente, fuenteSombra;
    boost::scoped_ptr<Gosu::Image> imagen;

    int lastX, lastY;

public:
    BotonMenu (Gosu::Graphics &graphics,
	       std::string texto,
	       Gosu::Color color
	) : graphics(graphics), color(color), texto(texto), 
	    fuente(new customFont(graphics, L"media/fNormal.ttf", TAMANYO)),
	    fuenteSombra(new customFont(graphics, L"media/fNormal.ttf", TAMANYO)),
	    imagen(new Gosu::Image(graphics, L"media/btnTemplate.png")),
	    lastX(0), lastY(0)	{
	cout << ">>> [Constructor] BotonMenu" << endl;
    }

    void draw(int x, int y, Gosu::ZPos z){
	lastX = x;
	lastY = y;
	imagen -> draw(x, y, z, 1, 1, color);
	int ancho = fuente -> textWidth(texto);
	Gosu::Color p (255,255,255,255);

	int offsetShadow[] = {1,2};
	int altura = 5;
	fuente -> draw(texto, 800/2 - ancho/2, y+altura, z + 0.1, p);
	fuenteSombra -> draw(texto, 800/2 - ancho/2 + offsetShadow[0], y+altura + offsetShadow[1], z, Gosu::Color(80,0,0,0));
    }

    bool clicked(int x, int y){
	if((x >= lastX) && (x <= lastX + (int) imagen -> width()) &&
	   (y >= lastY) && (y <= lastY + (int) imagen -> height())){
	    return true;
	}else{
	    return false;
	}
    }

};

#endif /* _BOTONMENU_H_ */
