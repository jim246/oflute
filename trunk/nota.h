#ifndef _NOTA_H_
#define _NOTA_H_

#include <Gosu/Gosu.hpp>

#include <boost/shared_ptr.hpp>

class Nota{
public:
    /// Imagen 
    boost::shared_ptr<Gosu::Image> imagen;

    Nota(Gosu::Graphics & g, float tiempos) : tiemposDelante(tiempos){
	imagen.reset ( new Gosu::Image (g, L"media/negra.png"));
    }
    
    /// Tiempos antes de la nota
    float tiemposDelante;
    
    void draw(int x, int y){
	imagen -> draw(x, y, 5);
    }
};

#endif /* _NOTA_H_ */
