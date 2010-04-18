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


#include "texto.h"

#define TIXML_USE_STL
#include "tinyxml.h"
#include "tinystr.h"


class elementoImagen{
    boost::scoped_ptr<Gosu::Image> img;
    Gosu::Graphics& g;
    string ruta;
    int x, y, z, wait;
public:
    elementoImagen(Gosu::Graphics& g, string ruta, int x, int y, int z, int wait)
	: 
	g(g), ruta(ruta), x(x), y(y), z(z), wait(wait){
	img.reset(new Gosu::Image(g, Gosu::widen(ruta)));	
    }

    void draw(){
	img -> draw(x,y,z);
    }    
};

class elementoTexto{
    boost::scoped_ptr<Texto> texto;
    int  wait;

public:
    elementoTexto(Gosu::Graphics& g, string str, unsigned tam, int x, int y, double z,
		  int wait, Gosu::Color color, unsigned alineacion, bool sombra) 
	: wait(wait){
	texto.reset(new Texto(g, str, tam, color, alineacion, sombra, 80, x, y, z));
    }

    void draw(){
	texto -> draw();
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
	doc.LoadFile(ruta);

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

	    int x, y, wait;
	    elemento -> QueryIntAttribute("x", &x);
	    elemento -> QueryIntAttribute("y", &y);
	    elemento -> QueryIntAttribute("wait", &wait);

	    double z;
	    elemento -> QueryDoubleAttribute("z", &z);

	    boost::shared_ptr<elementoImagen> E
		(new elementoImagen(g, ruta, x, y, z, wait));
	    elementosImg.push_back(E);
	}


	elemento = manejador.FirstChild("Lec").FirstChild("elementos")
	    .FirstChild("texto").ToElement();

	for(; elemento; elemento = elemento -> NextSiblingElement("texto") ){
	    string texto;
	    elemento -> QueryStringAttribute("str", &texto);

	    int tam, x, y, wait, align, sombra;
	    elemento -> QueryIntAttribute("x", &x);
	    elemento -> QueryIntAttribute("y", &y);
	    elemento -> QueryIntAttribute("tam", &tam);
	    elemento -> QueryIntAttribute("wait", &wait);
	    elemento -> QueryIntAttribute("align", &align);
	    elemento -> QueryIntAttribute("sombra", &sombra);

	    double z;
	    elemento -> QueryDoubleAttribute("z", &z);

	    // Componente alpha, red, green, blue
	    int ca, cr, cb, cg;
	    elemento -> QueryIntAttribute("ca", &ca);
	    elemento -> QueryIntAttribute("cr", &cr);
	    elemento -> QueryIntAttribute("cg", &cg);
	    elemento -> QueryIntAttribute("cb", &cb);

	    boost::shared_ptr<elementoTexto> T
		( new elementoTexto(g, texto, tam, x, y, z,
				    wait, Gosu::Color(ca, cr, cg, cb), align, 
				    ((sombra == 1) ? true : false)));
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
