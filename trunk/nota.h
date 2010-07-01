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
    

    Nota(Gosu::Graphics & g, t_altura altura, t_figura figura, float tiempos) : 
	altura(altura), figura(figura), tiemposDelante(tiempos){
	imagen.reset ( new Gosu::Image (g, L"media/negra.png"));

	lDEBUG << Log::CON("Nota") 
	       << boost::format(" %i %i %f") % altura % figura % tiempos;
    }
    
    /// Tiempos antes de la nota
    float tiemposDelante;
    

    static float devolverAltura(t_altura t){
	return (9 - t) * 18.6;
    }

    void draw(int x){
	imagen -> draw(x, 160 + Nota::devolverAltura(altura), 5);
    }
};

#endif /* _NOTA_H_ */
