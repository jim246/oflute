/**
 * @file configuracion.h
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


#ifndef _CONFIGURACION_H_
#define _CONFIGURACION_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "log.h"

#include <iostream>
using namespace std;
/**
 * @class lectorConfiguracion
 *
 * @brief Lee la configuración de un archivo ini estándar.
 *
 * Aún por desarrollar
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class lectorConfiguracion{
    float limiteSonido;
    boost::property_tree::ptree arbol;

public:
    lectorConfiguracion(){
//	try{
	    read_ini("config.ini", arbol);
	    limiteSonido = arbol.get<float>("sonido.limite", 1e+17);

/*	}catch(boost::property_tree::ini_parser::ini_parser_error & E){
	    limiteSonido = 1e+17;
	} //*/

	lDEBUG << "Configuración leída. Sonido.límite: " << limiteSonido; 
    }

    float sonidoLimite(){
	return limiteSonido;
    }

    void setSonidoLimite(float s){
	limiteSonido = s;
	arbol.put<float>("sonido.limite", s);
	write_ini("config.ini", arbol);
    }

};

#endif /* _CONFIGURACION_H_ */
