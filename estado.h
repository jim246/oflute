// estado.h --- Clase base estado

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

#ifndef _ESTADO_H_
#define _ESTADO_H_

#include <Gosu/Gosu.hpp>
#include <iostream>

using namespace std;

class Juego;

/**
 * @class Estado
 * 
 * @brief Clase base para los diferentes estados del juego.
 *
 * Esta clase abstracta tiene los métodos a los que llamará la clase de control (Juego).
 * Cada estado deberá implementar estos métodos con las acciones que crea conveniente.
*/

class Estado{
protected:
    /**
     @brief Puntero al padre creador.

     Nos sirve para poder cambiar de estado (llamando a #Juego::cambiarEstado()), acceder al sistema gráfico (con #Juego::graphics()) y otras acciones.
    **/
    Juego * padre;
public:
    Estado(Juego * p):padre(p){};

    /// Si es necesario lanzar acciones independientes del constructor, irán aquí.
    virtual void lanzar(){};

    /// Virtual puro. 
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void buttonDown(Gosu::Button){};
    virtual ~Estado(){
	cout << "** Estado::DESTRUCTOR" << endl;
    };
};

#endif /* _ESTADO_H_ */
