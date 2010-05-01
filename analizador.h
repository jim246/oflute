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

/**
 * @class tipoBuffer
 *
 * @brief Búffer en el que se guardan los datos de la captura.
 *
 * El sistema de audio va capturando audio y volcando los datos en este búffer, que luego se pasa a la función de Fourier
 * para calcular la frecuencia. 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class tipoBuffer{
public:
    tipoBuffer():pos(0), silencio(false){}
    int pos;
    float in[4096];
    float out[2048];

    float mayores[5];
    bool silencio;
};


/**
 * @class Analizador
 *
 * @brief Clase que hace el análisis general.
 *
 * Partiendo de los datos del búffer, apli
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Analizador{

    t_altura asociarNota (double frecuencia);
    std::map<double, t_altura> notas;
    bool iniciado;

    float int_to_hz, hz_to_int;

public:

    tipoBuffer * miBuffer;

    Analizador();

    t_altura notaActual();

    int funcionCallback(const void * inB, 
			void * outB, 
			unsigned long nFrames, 
			const PaStreamCallbackTimeInfo * timeInfo,
			PaStreamCallbackFlags statusFlags);

    ~Analizador();

};

#endif /* _ANALIZADOR_H_ */
