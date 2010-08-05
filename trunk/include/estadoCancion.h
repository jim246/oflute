/**
 * @file estadoCancion.h
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


#ifndef _CANCION_H_
#define _CANCION_H_

#include <boost/shared_ptr.hpp>
#include "global.h"

#include <vector>
#include <string>

using namespace std;

#include "nota.h"
#include "claseTimer.h"
#include "elementosInterfaz.h"
#include "particulas.h"

#include "analizador.h"

class Juego;

class Cancion{
    Analizador analizador;

    int bpm;

    float milisegundosPorPulso;

    float frecuencia;

    /// Número de píxeles que en pantalla ocupa una negra
    int distanciaPulso;

    int margenIzquierdo;

    /// Espera inicial antes de la primera nota
    float esperaInicial;

    myTimer temporizador;

    bool lanzado;

    vector<boost::shared_ptr<Nota> > conjNotas;
    t_altura notaEnLinea;

    t_altura notaLeida;

    int puntos;

    Gosu::Graphics & g;
    
    string ruta;

    enum {e1, e2, e3};

    int estadoActual;

    boost::scoped_ptr<Gosu::Image> resalteNotaActual;

    boost::scoped_ptr<ElementoImagen> imagenPartitura;
    boost::scoped_ptr<ElementoImagen> barraProgresoFondo;
    boost::scoped_ptr<Gosu::Image> barraProgreso;
    boost::scoped_ptr<ElementoCombinado> barraSuperior;
    boost::scoped_ptr<ElementoCombinado> barraInferior;

    void parsear();

    boost::scoped_ptr<SistemaParticulas> sistemaPartc;

public:
    Cancion(Gosu::Graphics & g, string ruta);

    void lanzar();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    
    ~Cancion();
};

#endif /* _CANCION_H_ */
