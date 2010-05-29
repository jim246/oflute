/**
 * @file juego.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Clase principal del juego
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

#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "Gosu/Gosu.hpp"
#include <boost/scoped_ptr.hpp>

#define ANCHO 800
#define ALTO 600
#define FULLSCREEN false
#define FPS 20

class Estado;

/**
 * @class Juego
 * @brief Clase principal del juego
 *
 * Sirve como pilar para el resto del juego. Hereda de la base 
 * Gosu::Window y se encarga de pasar de un estado a otro, así como
 * de pasarle los eventos al estado actual.
 *
 * Implementa las funciones update() y draw() para llevar a cabo el Game Loop,
 * ejecutándose ambas en cada iteración.
 */

class Juego : public Gosu::Window{
    /// Contenedor del estado actual
    boost::scoped_ptr <Estado> estadoActual;

    /// Imagen para el cursor del ratón
    boost::scoped_ptr <Gosu::Image> cursor;

public:
    /** 
     * @brief Constructor, inicio básico.
     *
     * Carga en memoria el primer estado y lo lanza.
     */
    Juego();

    /**
     * @brief Procesa la lógica del juego. 
     * 
     * Como la lógica de cada estado es controlada por la clase que 
     * corresponda a ese estado, este método simplemente llama
     * al update del estado actual.
     */
    void update();

    /**
     * @brief Procesa el dibujado de los gráficos.
     *
     * Igual que en el método #update, simplemente llama al método de 
     * dibujado de la clase del estado actual.
     */
    void draw();

    /**
     * @brief Cambia el estado al que se le indique.
     *
     * Recibe una cadena con el nombre del estado o la información
     * necesaria para pasar de un estado a otro.
     *
     * @param destino Una cadena con información sobre el estado al que cambiar
     *
     **/
    void cambiarEstado(std::string destino);

    /** @brief Evento de presión de un botón.
     * 
     * Lo mismo que en #update y #draw, paso transparente a la clase del estado actual.
     *
     * @param boton El botón que se ha pulsado.
     **/
    void buttonDown(Gosu::Button boton);

    /** 
     * @brief Destructor básico.
     *
     **/
    ~Juego();
};

#endif /* _JUEGO_H_ */
