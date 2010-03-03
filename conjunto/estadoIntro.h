#ifndef _ESTADOINTRO_H_
#define _ESTADOINTRO_H_

#include "estado.h"

#include "boost/scoped_ptr.hpp"

class Juego;

class estadoIntro : public estado{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo;
public:
    estadoIntro(Juego * p, Gosu::Graphics * graphics);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
};

#endif /* _ESTADOINTRO_H_ */
