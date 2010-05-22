/**
 * @file estadoLecciones.h
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

#ifndef _ESTADOLECCIONES_H_
#define _ESTADOLECCIONES_H_

#include <boost/scoped_ptr.hpp>

#include <Gosu/Gosu.hpp>

#include "estado.h"
#include "elementosInterfaz.h"

/**
 * @class EstadoMenuLecciones
 *
 * @brief 
 *
 * 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class Juego;

class EstadoMenuLecciones : public Estado{
    /// Imagen para el fondo
    boost::scoped_ptr<Gosu::Image> imgFondo;

    /// Título
    boost::scoped_ptr<elementoTexto> txtTitulo;

    /// Imagen de la pizarra
    boost::scoped_ptr<elementoImagen> pizarra;

    /// Subtítulo de información
    boost::scoped_ptr<elementoTexto> txtSubtitulo;
public:
    EstadoMenuLecciones(Juego * p);

    void update();
    
    void draw();

    void buttonDown(Gosu::Button boton);
};

#endif /* _ESTADOLECCIONES_H_ */
