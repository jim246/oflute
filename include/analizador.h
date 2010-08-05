/**
 * @file analizador.h
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



#ifndef _ANALIZADOR_H_
#define _ANALIZADOR_H_

#include <portaudiocpp/PortAudioCpp.hxx>
#include <map>

#include "global.h"
#include "configuracion.h"
#include "analizadorProxy.h"

#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>


class Analizador{
    lectorConfiguracion lectorConfig;
    AnalizadorProxy proxy;
    boost::scoped_ptr<boost::thread> hilo;

    t_altura asociarNota (double frecuencia);
    std::map<double, t_altura> notas;

    bool detenido;
public:
    Analizador();
    void iniciar();
    void detener();

    t_altura notaActual();
    float volumenActual();
    
};

#endif /* _ANALIZADOR_H_ */
