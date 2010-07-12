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

#include "estado.h"
#include "juego.h"

#include <Gosu/Gosu.hpp>
#include "boost/scoped_ptr.hpp"

#include "global.h"

#include "controlSonido.h"
#include "analizador.h"

#include "elementosInterfaz.h"

#include <string>
#include <map>

class Juego;

class EstadoAnalizador : public Estado{
public:

    EstadoAnalizador(Juego * p);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    ~EstadoAnalizador();

private:

    enum tTrans{ transIn, transHold, transOut };
    tTrans estadoTransicion;

    bool lanzado;
    boost::scoped_ptr<ElementoImagen> imgLogotipo;
    boost::scoped_ptr<ElementoImagen> imgPartitura;
    boost::scoped_ptr<ElementoTexto> txtSubtitulo;

    boost::scoped_ptr<Gosu::Image> imgFigura;

    Analizador analizador;

    bool running;
};

#endif
