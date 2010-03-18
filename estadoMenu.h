// estadoMenu.h --- Menú principal del juego

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

#ifndef _ESTADOMENU_H_
#define _ESTADOMENU_H_

#include "estado.h"
#include "customFont.h"
#include "animacion.h"

#include "boost/scoped_ptr.hpp"
#include <string>

class Juego;

/**
 * @class EstadoMenu
 * 
 * @brief Menú principal del juego.
 *
 * Controla la aparición de los botones, su pulsación y demás.
 */
class EstadoMenu : public Estado{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo, btn1, btn2, btn3, btn4, btnUca;
    boost::scoped_ptr<customFont> miFuente;
    boost::scoped_ptr<Animacion> anim;
    int estadoAnim;
    short alphaActual;
    unsigned long tiempoEsperaInicial;
    float posY[5]; //, posFinalesX[5];
public:
    /// Constructor. Crea un nuevo menú para el juego p.
    EstadoMenu(Juego * p);

    /// 
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    ~EstadoMenu();
};

#endif
