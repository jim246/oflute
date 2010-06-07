#ifndef _NOTA_H_
#define _NOTA_H_

#include <Gosu/Gosu.hpp>

#include <boost/shared_ptr.hpp>
#include "global.h"

class Nota{
public:
    /// Imagen 
    boost::shared_ptr<Gosu::Image> imagen;

    t_altura altura;

    t_figura figura;
    

    Nota(Gosu::Graphics & g, t_altura altura, t_figura figura, float tiempos) : 
	altura(altura), figura(figura), tiemposDelante(tiempos){
	imagen.reset ( new Gosu::Image (g, L"media/negra.png"));
    }
    
    /// Tiempos antes de la nota
    float tiemposDelante;
    
    void draw(int x, int y){
	imagen -> draw(x, y, 5);
    }
};

#endif /* _NOTA_H_ */
