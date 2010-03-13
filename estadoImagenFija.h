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
   Como es un comportamiento que es probable que se repita, esta clase se puede heredar para 

 */
class EstadoImagenFija : public Estado{
    bool lanzado;
    wstring nombreImagen;
    string estadoSiguiente;
    boost::scoped_ptr<Gosu::Image> imgFondo;

    int estadoAnim;
    short alphaActual;
    unsigned long tiempoEsperaInicial;
public:
    EstadoImagenFija(Juego * p, wstring nombreImagen, string estadoSiguiente);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    virtual void accionPosterior();
    virtual ~EstadoImagenFija();
};

#endif /* _ESTADOIMAGENFIJA_H_ */
