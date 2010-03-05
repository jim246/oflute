#ifndef _ESTADOANALIZADOR_H_
#define _ESTADOANALIZADOR_H_

#include "estado.h"
#include "analizador.h"


#include "boost/scoped_ptr.hpp"
#include <string>

class Juego;

class estadoAnalizador : public estado{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo;
    Analizador * analizador;
    
public:
    estadoAnalizador(Juego * p);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    ~estadoAnalizador();
};

#endif
