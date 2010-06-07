/**
 * @file estadoMenuCanciones.h
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


#ifndef _ESTADOMENUCANCIONES_H_
#define _ESTADOMENUCANCIONES_H_

#include "estado.h"


class Juego;
class Cancion;
/**
 * @class EstadoMenuCanciones
 *
 * @brief Menú de elección de canción.
 *
 * Permite al usuario elegir la canción, y lanzarla.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class EstadoMenuCanciones : public Estado{
    Cancion * cancion;
public:
    EstadoMenuCanciones(Juego * p);

    void update();
    void draw();
    void buttonDown(Gosu::Button boton);

    ~EstadoMenuCanciones();
};

#endif /* _ESTADOMENUCANCIONES_H_ */
