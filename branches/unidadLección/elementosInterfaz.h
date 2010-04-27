#ifndef _ELEMENTOSINTERFAZ_H_
#define _ELEMENTOSINTERFAZ_H_

#include <boost/scoped_ptr.hpp>
#include <boost/format.hpp>

#include <Gosu/Gosu.hpp>

#include "animacion.h"
#include "texto.h"

class elementoImagen{
    boost::scoped_ptr<Gosu::Image> img;
    Gosu::Graphics& g;
    string ruta;
    int x, y, z;
    bool animar;

    Animacion * A;
public:
    elementoImagen(Gosu::Graphics& g, string ruta, int x, int y, int z, 
		   bool animar, int wait, int duracion)
	: 
	g(g), ruta(ruta), x(x), y(y), z(z), animar(animar){
	
	img.reset(new Gosu::Image(g, Gosu::widen(ruta)));	

	if(animar){
	    cout << "** Se animará. Duración: " << duracion << endl;
	    A = new Animacion(0, 0, 255, 0, duracion, Animacion::tEaseOutQuad, wait);
	}

	cout << boost::format("** Imagen - ruta:'%s', x:%i, y:%i, z:%i, wait:%i") % ruta % x % y % z % wait << endl;
	
    }

    void draw(){
	if(animar){
	    A -> update();
	    img -> draw(x,y,z,1,1,Gosu::Color(A -> getX(), 255, 255, 255));
	}else{
	    img -> draw(x,y,z);
	}
    }    
};

class elementoTexto{
    boost::scoped_ptr<Texto> texto;
    bool animar;
    Animacion * A;
public:
    elementoTexto(Gosu::Graphics& g, string str, string rutaFuente, unsigned tam, 
		  int x, int y, double z, 
		  bool animar, int wait, int duracion, 
		  Gosu::Color color, unsigned alineacion, bool sombra, int opacidadSombra) 
	: animar(animar){

	texto.reset(new Texto(g, str, rutaFuente, tam, color, alineacion, sombra, opacidadSombra, x, y, z));
	if(animar){
	    A = new Animacion(0, 0, 255, 0, duracion, Animacion::tEaseOutQuad, wait);
	}

	cout << boost::format("** Texto - fuente:%s, tam:%i, x:%i, y:%i, z:%i, wait:%i, align: %i, sombra: %i\ntexto: %s") % rutaFuente % tam % x % y % z % wait % alineacion % sombra % str << endl;
    }

    void draw(){
	if(animar){
	    A -> update();
	    texto -> drawAlpha(A -> getX());
	}else{
	    texto -> draw();
	}
    }


};


#endif /* _ELEMENTOSINTERFAZ_H_ */
