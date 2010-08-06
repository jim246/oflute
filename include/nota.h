/**
 * @file nota.h
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


#ifndef _NOTA_H_
#define _NOTA_H_

#include <Gosu/Gosu.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

#include "global.h"
#include "log.h"

/**
 * @class Nota
 *
 * @brief Representa una nota en la partitura.
 *
 * Cada nota tiene su propia imagen, altura y figura.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


struct Nota{
    /// Imagen de la nota actual
    boost::shared_ptr<Gosu::Image> imagen;

    //@{
    /// @name Imágenes compartidas
    /// Se utilizan atributos estáticos para evitar que cada nota cargue su propia imagen

    static boost::shared_ptr<Gosu::Image> imgPuntillo;

    static boost::shared_ptr<Gosu::Image> silRedonda;
    static boost::shared_ptr<Gosu::Image> silBlanca;
    static boost::shared_ptr<Gosu::Image> silNegra;
    static boost::shared_ptr<Gosu::Image> silCorchea;

    static boost::shared_ptr<Gosu::Image> figRedonda;
    static boost::shared_ptr<Gosu::Image> figBlanca;
    static boost::shared_ptr<Gosu::Image> figNegra;
    static boost::shared_ptr<Gosu::Image> figCorchea;

    static boost::shared_ptr<Gosu::Image> figBlancaInv;
    static boost::shared_ptr<Gosu::Image> figNegraInv;
    static boost::shared_ptr<Gosu::Image> figCorcheaInv;

    //@}

    /// Altura de la nota
    t_altura altura;

    /// Figura de la nota
    t_figura figura;
    
    /// Posición horixontal
    float x;

    /// Carga inicial de los atributos estáticos en los que se guardan las imágenes
    static void initImagenes(Gosu::Graphics & g);

    /// Construye una nota con los atributos indicados
    Nota(Gosu::Graphics & g, t_altura altura, t_figura figura, float tiempos);
    
    /// Tiempos antes de la nota
    float tiemposDelante;

    /// Devuelve la duración de una figura en forma de número
    static float devolverDuracion(t_figura f);

    /// Devuelve la posición vertical de una nota concreta, teniendo en cuenta la figura
    static float devolverAltura(t_altura t, t_figura fig = Nulo);

    /// Actualiza la posición horizontal de la nota
    void updatePos(float x_);

    /// Pinta la nota
    void draw();
};

#endif /* _NOTA_H_ */
