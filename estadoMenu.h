#ifndef _ESTADOMENU_H_
#define _ESTADOMENU_H_

#include "estado.h"
#include "boost/scoped_ptr.hpp"
#include <string>

class Juego;

class EstadoMenu : public Estado{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo, btn1, btn2, btn3, btn4, btnUca;

    int estadoAnim;
    short alphaActual;
    unsigned long tiempoEsperaInicial;
    float posY[5]; //, posFinalesX[5];
public:
    EstadoMenu(Juego * p);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    ~EstadoMenu();
};

#endif