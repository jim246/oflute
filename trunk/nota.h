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
	wstring rutaImg = L" ";

	if(figura == Redonda){
	    if(altura == Silencio){
		rutaImg = L"media/figuras/silRedonda.png";
	    }else{
		rutaImg = L"media/figuras/figRedonda.png";
	    }
	}

	else if(figura == Blanca){
	    if(altura == Silencio){
		rutaImg = L"media/figuras/silBlanca.png";
	    }else if(altura <= Si5){
		rutaImg = L"media/figuras/figBlanca.png";
	    }else{
		rutaImg = L"media/figuras/figBlancaInv.png";
	    }
	}

	else if(figura == Corchea){
	    if(altura == Silencio){
		rutaImg = L"media/figuras/silCorchea.png";
	    }else if(altura <= Si5){
		rutaImg = L"media/figuras/figCorchea.png";
	    }else{
		rutaImg = L"media/figuras/figCorcheaInv.png";
	    }
	}

	else{
	    if(altura == Silencio){
		rutaImg = L"media/figuras/silNegra.png";
	    }else if(altura <= Si5){
		rutaImg = L"media/figuras/figNegra.png";
	    }else{
		rutaImg = L"media/figuras/figNegraInv.png";
	    }
	}

	imagen.reset ( new Gosu::Image (g, rutaImg));

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

    static float devolverAltura(t_altura t, t_figura fig = Nulo){

	if(t != Silencio){
	    return (9 - t) * 18.6;
	}else{
	    if(fig == Redonda ){
		return 18;
	    }

	    else if(fig == Blanca){
		return 19;
	    }

	    else if(fig == Negra || fig == Corchea){
		return 18.6 * 5;
	    }
	    return 0;
	}
    }

    void updatePos(float x_){
	x = x_;
    }

    void draw(){
	if(x > -100)
	    imagen -> draw(x, 162 + Nota::devolverAltura(altura, figura), 5);
    }
};

#endif /* _NOTA_H_ */
