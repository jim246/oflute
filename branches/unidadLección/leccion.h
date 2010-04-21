// leccion.h --- Clase para las lecciones

// Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>

// Autor: José Tomás Tocino García

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.

#ifndef _LECCION_H_
#define _LECCION_H_

#include "Gosu/Gosu.hpp"

#include <vector>
#include <string>

using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>


#include "texto.h"
#include "animacion.h"

#define TIXML_USE_STL
#include "tinyxml.h"
#include "tinystr.h"


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

class Leccion{
    unsigned indice;
    string nombre;

    Gosu::Graphics& g;

    vector<boost::shared_ptr<elementoImagen> > elementosImg;
    vector<boost::shared_ptr<elementoTexto> > elementosTxt;
    

public:
    Leccion(Gosu::Graphics& g, string ruta) : g(g){
	cout << "Constructor de lección para el archivo >" << ruta << "<" << endl;
	TiXmlDocument doc;
	if(!doc.LoadFile(ruta)){
	    cerr << "#### ERROR al intentar abrir el fichero '" << ruta << "'." << endl;
	    throw 42;
	}


	TiXmlHandle manejador(&doc);
	TiXmlElement * elemento = manejador.FirstChild("Lec").FirstChild("index").ToElement();
	indice = boost::lexical_cast<int>(elemento -> GetText());

	cout << "Índice: " << indice << endl;

	elemento = manejador.FirstChild("Lec").FirstChild("nombre").ToElement();
	nombre = elemento -> GetText();

	cout << "Nombre: " << nombre << endl;

	// Leemos las imágenes
	elemento = manejador.FirstChild("Lec").FirstChild("elementos").FirstChild("img").ToElement();

	for(; elemento; elemento = elemento -> NextSiblingElement("img") ){
	    string ruta;
	    elemento -> QueryStringAttribute("src", &ruta);

	    int x, y;
	    elemento -> QueryIntAttribute("x", &x);
	    elemento -> QueryIntAttribute("y", &y);

	    int animar, wait, duracion;

	    // Se anima por defecto
	    if(elemento -> QueryIntAttribute("animar", &animar) != TIXML_SUCCESS){
		animar = 1;
	    }
	    
	    if(elemento -> QueryIntAttribute("wait", &wait) != TIXML_SUCCESS){
		wait = 0;
	    }

	    if(elemento -> QueryIntAttribute("duracion", &duracion) != TIXML_SUCCESS){
		duracion = 20;
	    }

	    double z;
	    elemento -> QueryDoubleAttribute("z", &z);

	    boost::shared_ptr<elementoImagen> E
		(new elementoImagen(g, ruta, x, y, z, ((animar==1)?true:false), wait, duracion) );
	    elementosImg.push_back(E);
	}



	// Leemos los textos
	elemento = manejador.FirstChild("Lec").FirstChild("elementos")
	    .FirstChild("texto").ToElement();

	for(; elemento; elemento = elemento -> NextSiblingElement("texto") ){
	    string texto, rutaFuente;
	    elemento -> QueryStringAttribute("str", &texto);


	    cout << texto << endl;
	    if(elemento -> QueryStringAttribute("fuente", &rutaFuente) != TIXML_SUCCESS){
		rutaFuente = "media/fNormal.ttf";
	    }

	    int tam, x, y, align, sombra, opacSombra;
	    elemento -> QueryIntAttribute("x", &x);
	    elemento -> QueryIntAttribute("y", &y);
	    elemento -> QueryIntAttribute("tam", &tam);
	    elemento -> QueryIntAttribute("align", &align);
	    elemento -> QueryIntAttribute("sombra", &sombra);

	    if(elemento -> QueryIntAttribute("opacSombra", &opacSombra) != TIXML_SUCCESS){
		opacSombra = 80;
	    }


	    int animar, wait, duracion;
	    if(elemento -> QueryIntAttribute("animar", &animar) != TIXML_SUCCESS){
		animar = 1;
	    }

	    if(elemento -> QueryIntAttribute("wait", &wait) != TIXML_SUCCESS){
		wait = 0;
	    }

	    if(elemento -> QueryIntAttribute("duracion", &duracion) != TIXML_SUCCESS){
		duracion = 20;
	    }

	    double z;
	    elemento -> QueryDoubleAttribute("z", &z);

	    // Componente alpha, red, green, blue
	    int ca, cr, cb, cg;
	    elemento -> QueryIntAttribute("ca", &ca);
	    elemento -> QueryIntAttribute("cr", &cr);
	    elemento -> QueryIntAttribute("cg", &cg);
	    elemento -> QueryIntAttribute("cb", &cb);

	    boost::shared_ptr<elementoTexto> T
		( new elementoTexto(g, texto, rutaFuente, tam, x, y, z,
				    animar, wait, duracion, Gosu::Color(ca, cr, cg, cb), align, 
				    ((sombra == 1) ? true : false), opacSombra));
	    elementosTxt.push_back(T);

	}
	
    }

    void draw(){
	BOOST_FOREACH(boost::shared_ptr<elementoTexto>& T, elementosTxt)
	{
	    T -> draw();
	}

	BOOST_FOREACH(boost::shared_ptr<elementoImagen>& E, elementosImg)
	{
	    E -> draw();
	}
    }

};

#endif /* _LECCION_H_ */
