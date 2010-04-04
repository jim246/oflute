// estadoAnalizador.h --- Clase del estado del analizador de notas - aún por mejorar

// Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>

// Autor: José Tomás Tocino García

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.

#ifndef _ESTADOANALIZADOR_H_
#define _ESTADOANALIZADOR_H_

//#include "estado.h"
//#include "juego.h"

#include <Gosu/Gosu.hpp>
#include "boost/scoped_ptr.hpp"

#include <portaudio.h>


#include "global.h"

#include "controlSonido.h"
#include "analizador.h"

#include <string>
#include <map>

class Juego;

class EstadoAnalizador : public Gosu::Window{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo;
    boost::shared_ptr<Gosu::Image> imgDo5, imgRe5, imgMi5, imgFa5, imgSol5, imgLa5, imgSi5, imgDo6, imgRe6;
    boost::scoped_ptr<Gosu::Image> cartelCargando;

    ControlSonido  controlSonido;
    Analizador  analizador;

    bool firstFrame, running;

    void activar();

    void cargarRecursos();
public:

    EstadoAnalizador();
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    ~EstadoAnalizador();
};

#endif
