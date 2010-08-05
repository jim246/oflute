// estadoImagenFija.h --- Clase EstadoImagenFija

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

#ifndef _ESTADOIMAGENFIJA_H_
#define _ESTADOIMAGENFIJA_H_

#include "estado.h"
#include "boost/scoped_ptr.hpp"
#include <string>

class Juego;

/**
   @class EstadoImagenFija

   @brief Clase simple, que hereda de #Estado, para hacer fadein y fadeout de una imagen fija.

   En muchos casos, principalmente en las pantallas de introducción inicial, nos interesa una forma fácil de
   hacer aparecer una imagen y luego hacerla desvanecer, simplemente para mostrarla durante un instante de forma elegante.
   Como es un comportamiento que es probable que se repita, he creado esta clase a la que se le pasa el nombre de la imagen a mostrar y el estado siguiente, y simplemente hace aparecer y desaparecer la imagen, y luego pasa al siguiente estado indicado.

   El funcionamiento se basa en un pequeño autómata con los siguientes estados:
\dot
digraph afd{
      node [shape=box, fontsize=11];
      edge [fontsize=9];
      e0 [ label="estadoAnim=0" ];
      p1 [ shape=diamond, label="¿lanzado=1?" ];
      e0 -> p1 [ label="update()" ];
      p1 -> e0 [ label="No" ];
      p1 -> e01 [ label="Sí" ];

      e01 [ label="estadoAnim=0" ];
      e02 [ label="Aumentamos la opacidad" ];
      e01 -> e02;
      p2 [ shape=diamond, label="¿opacidad == 255?" ];
      e02 -> p2;
      p2 -> e02 [ constraint=false, label = "No" ];
      p2 -> e1 [ label="Sí" ];
      e1 [ label="estadoAnim=1"];
      e1 -> e11;
      e11 [ label="Esperamos" ];
      e11 -> p3 ;
      p3 [ shape=diamond, label="¿Se ha esperado tiempoEspera?"];
      p3 -> e11 [label = "No",constraint=false ];

      e2 [ label="estadoAnim=2" ];

      B [ label="lanzado=1\nestadoAnim=0\nalphaActual=0"];
      C [ label="lanzado=1\nestadoAnim=0\nalphaActual=255"];
      D [ label="lanzado=1\nestadoAnim=1\nalphaActual=255"];
      E [ label="lanzado=1\nestadoAnim=1\nalphaActual=0"];



}
\enddot

 */
class EstadoImagenFija : public Estado{
    /// Flag que indica si se ha lanzado ya o no.
    bool lanzado;

    /// Nombre de la imagen a cargar.
    wstring nombreImagen;

    /// Estado que sigue a éste.
    string estadoSiguiente;

    /// Objeto para la imagen.
    boost::scoped_ptr<Gosu::Image> imgFondo;

    /// Estado actual en la animación.
    int estadoAnim;

    /// Opacidad actual de la imagen.
    short alphaActual;

    /// Momento inicial para calcular la parada en la que la imagen está al 100% de opacidad.
    unsigned long tiempoEsperaInicial;

    /// Tiempo que está la imagen al 100% de opacidad.
    unsigned tiempoEspera;
public:

    /**
     * @brief Crea un estado para hacer aparecer y desaparecer la imagen.
     *
     * @param p La clase juego de la que forma parte
     * @param nombreImagen El nombre de la imagen a cargar
     * @param estadoSiguiente Texto con la información del siguiente estado
     * @param tiempoEspera Tiempo a esperar mostrando la imagen
     */
    EstadoImagenFija(Juego * p, wstring nombreImagen, string estadoSiguiente, unsigned tiempoEspera = 1000);

    /// Inicializa la imagen y comienza la animación en el primer estado
    void lanzar ();

    /**
     * @brief Actualiza la opacidad de la imagen según corresponda.
     *
     *

     **/
    void update();

    /// Dibuja la imagen con la opacidad que le corresponda en ese momento
    void draw();

    /**
     * @brief Actúa frente a la pulsación de una tecla.
     *
     * La acción por defecto es ejecutar #accionPosterior() al pulsar escape.
     **/
    virtual void buttonDown(Gosu::Button boton);

    /**
     * @brief Acción a ejecutar tras terminar de mostrarse la imagen.
     *
     * Por defecto, se salta al Estado estadoSiguiente.
     **/
    virtual void accionPosterior();

    
    virtual ~EstadoImagenFija();
};

#endif /* _ESTADOIMAGENFIJA_H_ */
