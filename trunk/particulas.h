#ifndef _PARTICULAS_H_
#define _PARTICULAS_H_

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "animacion.h"

#include <ctime>
#include <vector>

#define lim 0.70

struct Particula{

    float angulo;

    float distancia;

    float tamanyo;

    int duracion;
    
    boost::shared_ptr<Gosu::Image> imagen;

    Gosu::Color color;

    int pasoActual;

    float posX;

    float posY;

    float posTemp;

    float coefTam;

    Particula(float angulo,
	      float distancia,
	      float tamanyo,
	      int duracion,
	      boost::shared_ptr<Gosu::Image> img,
	      Gosu::Color c) :
	angulo(angulo),
	distancia(distancia),
	tamanyo(tamanyo),
	duracion(duracion),
	imagen(img),
	pasoActual(0),
	posX(0),
	posY(0){

	color = Gosu::Color(Gosu::random(0, 1) * c.red(),
			    Gosu::random(0, 1) * c.green(),
			    Gosu::random(0, 1) * c.blue());
    }
    void update(){
	if(pasoActual != duracion) pasoActual ++;

	posTemp = Animacion::easeOutQuart(pasoActual, 0, 1, duracion); 

	if(posTemp >= lim){
	    color.setAlpha ( 255 * (1 - (posTemp - lim) / (1 - lim)));
	}else{
	    color.setAlpha(255);
	}

	coefTam = tamanyo * (1 - posTemp);
	
	posX = Gosu::offsetX(angulo, posTemp * distancia) 
	    - imagen -> width() * coefTam / 2;
	posY = Gosu::offsetY(angulo, posTemp * distancia) 
	    - imagen -> height() * coefTam / 2;
    }

    void draw(int oX, int oY){
	imagen -> draw(oX + posX, oY + posY, 7, coefTam, coefTam, color);//, Gosu::amAdditive);
    }

    float estado(){
	return (float)pasoActual / (float)duracion;
    }
};

class SistemaParticulas{
    Gosu::Graphics & g;
    unsigned cantidadParticulas, duracion, distancia;
    float escala;
    bool * tipo;

    Gosu::Color color;

    boost::shared_ptr<Gosu::Image> partc1, partc2;

    vector<boost::shared_ptr<Particula> > vectorParticulas;

    bool activo;
public:
    SistemaParticulas(Gosu::Graphics& g, unsigned n, unsigned d, 
		      unsigned distancia=200, float escala=1, 
		      Gosu::Color color = Gosu::Color::WHITE) : 
	g(g), cantidadParticulas(n), duracion(d), 
	distancia(distancia), escala(escala), color(color){

	activo = false;

	std::srand(std::clock());
	
	partc1 . reset(new Gosu::Image(g, L"media/particulas/partc1.png"));
	partc2 . reset(new Gosu::Image(g, L"media/particulas/partc2.png"));

//	vectorParticulas.resize(cantidadParticulas);

	for (size_t i = 0; i < cantidadParticulas; ++i)
	{
	    vectorParticulas.push_back(boost::shared_ptr<Particula>(nuevaPartc()));
	}
    }

    Particula * nuevaPartc(){
	return new Particula(Gosu::random(0,360),
			     Gosu::random(0, 1) * distancia,
			     Gosu::random(0, escala),
			     Gosu::random(0.1, 1) * duracion,
			     (Gosu::random(0,1)? partc1 : partc2),
			     color);
    }

    void update(){
	for (unsigned i = 0; i < cantidadParticulas; ++i){
	    vectorParticulas[i] -> update();
	    if(activo)
		if(vectorParticulas[i] -> estado() > 0.5){
		    vectorParticulas[i].reset(nuevaPartc());
		}
	}	//*/
    
    }

    void toggle(){ activo = !activo; }

    void off(){ activo = false; }
    
    void on(){ activo = true; }

    void draw(int origX, int origY){
	for (unsigned i = 0; i < cantidadParticulas; ++i){
	    vectorParticulas[i] -> draw(origX, origY);
	}
    }

    ~SistemaParticulas(){

    }
};

#endif /* _PARTICULAS_H_ */
