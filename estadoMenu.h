/**
 * @file estadoMenu.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Archivo para la clase que gestiona el menú
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



#ifndef _ESTADOMENU_H_
#define _ESTADOMENU_H_

#include "estado.h"
#include "customFont.h"

#include "botonMenu.h"

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
    /// Flag que indica si el estado ha sido lanzado
    bool lanzado;

    /// Imagen de fondo
    boost::scoped_ptr<Gosu::Image> imgFondo;

    /// Adorno rojo inferior
    boost::scoped_ptr<Gosu::Image> barraRoja;

    /// Logotipo
    boost::scoped_ptr<Gosu::Image> logotipo;

    /// Botón de "Universidad de Cádiz"
    boost::scoped_ptr<Gosu::Image> btnUca;

    /// Imagen del logo del CUSL
    boost::scoped_ptr<Gosu::Image>  logoCusl;

    /// Botones del menú
    boost::scoped_ptr<BotonMenu> btn1, btn2, btn3, btn4;
    
    /// Animaciones para los botones del menú
    boost::scoped_ptr<Animacion> animaciones[6];

    /// Animaciones para la imagen del CUSL
    boost::scoped_ptr<Animacion> animLogoCusl;

    /// Animación para el logo de oflute
    boost::scoped_ptr<Animacion> animLogotipo;

    /// Animación para la opacidad del fondo
    boost::scoped_ptr<Animacion> animOpacidadFondo;

    /// Contador para controlar el flujo del menú 
    int estadoAnim;

    std::string estadoDestino;

    enum {eFADEIN, eBOTONESIN, eESTATICO, eBOTONESOUT, eANIMOUT, eANIMEND};

    bool animarFondo;
    
    //float posY[5]; //, posFinalesX[5];
public:
    /// Constructor. Crea un nuevo menú para el juego p.
    EstadoMenu(Juego * p);

    /// 
    void lanzar ();
    void update();
    void draw();
    void noAnimarFondo(){ animarFondo = false; }

    void buttonDown(Gosu::Button boton);
    ~EstadoMenu();
};

#endif
