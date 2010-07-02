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

    t_altura altura;

    t_figura figura;
    
    float x;

    Nota(Gosu::Graphics & g, t_altura altura, t_figura figura, float tiempos) : 
	altura(altura), figura(figura), tiemposDelante(tiempos){

	if(figura == Redonda){
	    imagen.reset ( new Gosu::Image (g, L"media/figuras/figRedonda.png"));
	}else if(figura == Blanca){
	    imagen.reset ( new Gosu::Image (g, L"media/figuras/figBlanca.png"));
	}else if(figura == Corchea){
	    imagen.reset ( new Gosu::Image (g, L"media/figuras/figCorchea.png"));
	}else{
	    imagen.reset ( new Gosu::Image (g, L"media/figuras/figNegra.png"));
	}

	lDEBUG << Log::CON("Nota") 
	       << boost::format(" %i %i %f") % altura % figura % tiempos;
    }
    
    /// Tiempos antes de la nota
    float tiemposDelante;

    static float devolverDuracion(t_figura f){
	if(f == Redonda){
	    return 4;
	}else if(f == Blanca){
	    return 2;
	}else if(f == Negra){
	    return 1;
	}else{
	    return 0.5;
	}
    }

    static float devolverAltura(t_altura t){
	return (9 - t) * 18.6;
    }

    void updatePos(float x_){
	x = x_;
    }

    void draw(){
	if(x > -100)
	    imagen -> draw(x, 162 + Nota::devolverAltura(altura), 5);
    }
};

#endif /* _NOTA_H_ */
