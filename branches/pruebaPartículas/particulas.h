#ifndef _PARTICULAS_H_
#define _PARTICULAS_H_

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "animacion.h"

#include <ctime>


class SistemaParticulas{
    Gosu::Graphics & g;
    unsigned cantidadParticulas, duracion, distancia;
    float * angulos, * distancias, * tamanyo;
    bool * tipo;

    Gosu::Color color;

    boost::scoped_ptr<Gosu::Image> partc1, partc2;
    boost::scoped_ptr<Animacion> anim;
public:
    SistemaParticulas(Gosu::Graphics& g, unsigned n, unsigned d, unsigned distancia=200, Gosu::Color color = Gosu::Color::WHITE) : 
	g(g), cantidadParticulas(n), duracion(d), distancia(distancia), color(color){

	std::srand(std::clock());
	
	partc1 . reset(new Gosu::Image(g, L"partc1.png"));
	partc2 . reset(new Gosu::Image(g, L"partc2.png"));

	anim . reset(new Animacion(0, 0, 1, 1, duracion, Animacion::tEaseOutCubic));
		     
	// Si tenemos n partículas, tenemos que crear un vector
	// con el ángulo de cada partícula,
	// y la distancia de la misma
	angulos = new float[cantidadParticulas];
	distancias = new float[cantidadParticulas];
	tipo = new bool[cantidadParticulas];
	tamanyo = new float[cantidadParticulas];

	inicializar();
    }

    void inicializar(){
	for (unsigned i = 0; i < cantidadParticulas; ++i)
	{
	    angulos[i] = Gosu::random(0, 360);
	    distancias[i] = Gosu::random(0,1);
	    tipo[i] = (Gosu::random(0,1) < 0.5)?true:false;
	    tamanyo[i] = Gosu::random(0,2);
	}

	anim . reset(new Animacion(0, 0, 1, 1, duracion, Animacion::tEaseOutQuart));
    }
    void draw(int origX, int origY){
	float pos = anim -> getX();

	    // Lo suyo es que se vayan desvaneciendo cuando esté ya algo alejado del centro, es decir, cuando pos se acerque a 1

	float lim = 0.70;

	if(pos >= lim){
 
	    color.setAlpha ( 255 * (1 - (pos - lim) / (1 - lim)));
	}else{
	    color.setAlpha(255);
	}

	for (unsigned i = 0; i < cantidadParticulas; ++i)
	{
	    // Coeficiente del tamaño
	    float coefTam = tamanyo[i] * (1 - pos);
	    
	    if(tipo[i]){
		partc1 -> draw(origX + Gosu::offsetX(angulos[i], pos * distancias[i] * distancia) - partc1 -> width() * coefTam / 2,
			       origY + Gosu::offsetY(angulos[i], pos * distancias[i] * distancia) - partc1 -> height() * coefTam / 2,
			       1,
			       coefTam, coefTam,
			       color, Gosu::amAdditive);
	    }else{
		partc2 -> draw(origX + Gosu::offsetX(angulos[i], pos * distancias[i] * distancia) - partc1 -> width() * coefTam / 2,
			       origY + Gosu::offsetY(angulos[i], pos * distancias[i] * distancia) - partc1 -> height() * coefTam / 2,
			       1,
			       coefTam, coefTam,
			       color, Gosu::amAdditive);

	    }
	}

	anim -> update();
    }

    ~SistemaParticulas(){
	delete angulos;
	delete distancias;
	delete tipo;
    }
};

#endif /* _PARTICULAS_H_ */
