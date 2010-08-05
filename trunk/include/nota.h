#ifndef _NOTA_H_
#define _NOTA_H_

#include <Gosu/Gosu.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

#include "global.h"
#include "log.h"

struct Nota{
    /// Imagen 
    boost::shared_ptr<Gosu::Image> imagen;

    static boost::shared_ptr<Gosu::Image> imgPuntillo;

    static boost::shared_ptr<Gosu::Image> silRedonda;
    static boost::shared_ptr<Gosu::Image> silBlanca;
    static boost::shared_ptr<Gosu::Image> silNegra;
    static boost::shared_ptr<Gosu::Image> silCorchea;

    static boost::shared_ptr<Gosu::Image> figRedonda;
    static boost::shared_ptr<Gosu::Image> figBlanca;
    static boost::shared_ptr<Gosu::Image> figNegra;
    static boost::shared_ptr<Gosu::Image> figCorchea;

    static boost::shared_ptr<Gosu::Image> figBlancaInv;
    static boost::shared_ptr<Gosu::Image> figNegraInv;
    static boost::shared_ptr<Gosu::Image> figCorcheaInv;

    t_altura altura;

    t_figura figura;
    
    float x;

    static void initImagenes(Gosu::Graphics & g);

    Nota(Gosu::Graphics & g, t_altura altura, t_figura figura, float tiempos);
    
    /// Tiempos antes de la nota
    float tiemposDelante;

    static float devolverDuracion(t_figura f);

    static float devolverAltura(t_altura t, t_figura fig = Nulo);

    void updatePos(float x_);

    void draw();
};

#endif /* _NOTA_H_ */
