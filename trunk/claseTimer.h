/**
 * @file claseTimer.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Archivo para la clase Timer
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


#ifndef _CLASETIMER_H_
#define _CLASETIMER_H_

#include <Gosu/Gosu.hpp>

/**
 * @class myTimer
 *
 * @brief Basada en Boost::Timer pero adaptada para Gosu.
 *
 * Utiliza los temporizadores de Gosu (Gosu::milliseconds()) para controlar el tiempo.
 * El funcionamiento es sencillo:
 * \code
 * myTimer T;
 * cout << "Tiempo transcurrido: " << T.elapsed() << "ms" << endl;
 * T.restart();
 * \endcode
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class myTimer{
    /// Guarda el momento en el que se inicia el temporizador.
    unsigned long inicial;
public:
    /// Crea un nuevo temporizador.
    myTimer(){
	restart();
    }

    /// Reinicia el temporizador.
    void restart(){
	inicial = Gosu::milliseconds();
    }

    /// Devuelve el tiempo transcurrido desde el último reinicio del temporizador.
    unsigned long elapsed(){
	return Gosu::milliseconds() - inicial;
    }
    
};

#endif /* _CLASETIMER_H_ */
