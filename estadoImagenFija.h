#ifndef _ESTADOIMAGENFIJA_H_
#define _ESTADOIMAGENFIJA_H_

#include "estado.h"
#include "boost/scoped_ptr.hpp"
#include <string>

class Juego;

class estadoImagenFija : public estado{
    bool lanzado;
    wstring nombreImagen;
    boost::scoped_ptr<Gosu::Image> imgFondo;

    int estadoAnim;
    short alphaActual;
    unsigned long tiempoEsperaInicial;
public:
    estadoImagenFija(Juego * p, wstring nombreImagen);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    virtual void accionPosterior(){}
    /*~estadoImagenFija(){
	cout << "FISIKITO" << endl;
    }//*/
};

#endif /* _ESTADOIMAGENFIJA_H_ */
