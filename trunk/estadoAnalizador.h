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

#include "portaudio.h"


#include "global.h"

#include <string>
#include <map>

class Juego;

class tipoBuffer{
public:
    tipoBuffer():pos(0),silencio(false){}
    int pos;
    float in[4200]; // 4096
    float out[2048];

    // Vector de harmónicos más importantes en la nota
    float mayores[5];
    bool silencio;
};

class EstadoAnalizador : public Estado{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo;
    boost::shared_ptr<Gosu::Image> imgDo5, imgRe5, imgMi5, imgFa5, imgSol5, imgLa5, imgSi5, imgDo6, imgRe6;
    boost::scoped_ptr<Gosu::Image> cartelCargando;

    bool iniciado, silencio, firstFrame, running;

    // Flujo principal
    PaStream * stream;

    PaError err;

    // Mapa de frecuencias y notas
    std::map<double, t_altura> notas;

    // Devuelve la nota asociada a una frecuencia
    t_altura asociarNota(double frecuencia);

    void activar();

    // Función callback    
    static int updateBuffer(const void * inB, 
			    void * outB, 
			    unsigned long nFrames, 
			    const PaStreamCallbackTimeInfo * timeInfo,
			    PaStreamCallbackFlags statusFlags,
			    void * data);
    int updateBuffer2(const void * inB, 
			    void * outB, 
			    unsigned long nFrames, 
			    const PaStreamCallbackTimeInfo * timeInfo,
		      PaStreamCallbackFlags statusFlags);
    
    void cargarRecursos();
public:
    int numSamples;

    static tipoBuffer miBuffer;
    EstadoAnalizador(Juego * p);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    bool configurarFlujo();
    bool iniciarAnalisis();
    t_altura notaActual();
    bool detenerAnalisis();
    ~EstadoAnalizador();
};

#endif
