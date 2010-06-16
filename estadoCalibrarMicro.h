/**
 * @file estadoCalibrarMicro.h
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

#ifndef _ESTADOCALIBRARMICRO_H_
#define _ESTADOCALIBRARMICRO_H_

#include "estado.h"
#include "elementosInterfaz.h"
#include "claseTimer.h"

#include <vector>

#include "controlSonido.h"
#include "analizador.h"
#include "configuracion.h"

using namespace std;

class Juego;

class EstadoCalibrarMicro : public Estado{
    lectorConfiguracion archivoConf;

    Analizador analizador;

    myTimer crono;

    boost::scoped_ptr<ElementoImagen> imgMicro;
    boost::scoped_ptr<ElementoTexto> textoDesc;
    boost::scoped_ptr<ElementoTexto> cartelCapturando;

    vector<float> valoresLeidos;
    float mediaValores;
    int estadoCaptura;

public:
    EstadoCalibrarMicro(Juego * p);
    void update();
    void draw();
    void buttonDown (Gosu::Button boton);

    ~EstadoCalibrarMicro();


};

#endif /* _ESTADOCALIBRARMICRO_H_ */
