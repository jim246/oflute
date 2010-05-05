/**
 * @file leccion.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Fichero para la clase Lección
 * 
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _LECCION_H
#define _LECCION_H_

#include "Gosu/Gosu.hpp"

#include <vector>
#include <string>

using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include "elementosInterfaz.h"
#include "texto.h"
#include "animacion.h"

#define TIXML_USE_STL
#include "tinyxml.h"
#include "tinystr.h"

/**
 * @class Leccion
 *
 * @brief Lee una lección de un xml pasado como argumento, y genera una interfaz atendiendo a los elementos leídos del XML.
 *
 * Recibe la ruta de un archivo XML, que contendrá los elementos que deberán aparecer en la interfaz. Los elementos posibles son
 * cuadros de texto e imágenes. 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Leccion{
    /// Índice de la lección en el listado de lecciones
    unsigned indice;

    /// Nombre de la lección
    string nombre;

    /// Referencia al contenedor gráfico
    Gosu::Graphics& g;

    /// Contenedor de las imágenes de la interfaz
    vector<boost::shared_ptr<elementoImagen> > elementosImg;

    /// Contenedor de los cuadros de texto de la interfaz
    vector<boost::shared_ptr<elementoTexto> > elementosTxt;
    
public:
    /**
     * @brief Construye una nueva lección a partir de un XML.
     *
     * @param g El destino gráfico en que se dibujará la interfaz
     * @param ruta La ruta del fichero XML
     *
     */

    Leccion(Gosu::Graphics& g, string ruta) : g(g){
	cout << "Constructor de lección para el archivo >" << ruta << "<" << endl;

	// Creamos un nuevo objeto XML
	TiXmlDocument doc;

	// Intentamos leer y cargar el fichero en el objeto XML
	if(!doc.LoadFile(ruta)){
	    cerr << "#### ERROR al intentar abrir el fichero '" << ruta << "'." << endl;
	    /// @todo Arreglar el control de errores cuando no existe el XML
	    throw 42;
	}

	// Los manejadores TiXmlHandle facilitan el control de errores al leer XML's inválidos
	TiXmlHandle manejador(&doc);

	/// @todo Implementar control de errores para archivos XML mal formados

	// Leemos el nodo <index>
	TiXmlElement * elemento = manejador.FirstChild("Lec").FirstChild("index").ToElement();
	indice = boost::lexical_cast<int>(elemento -> GetText());

	cout << "Índice: " << indice << endl;

	// Leemos el nodo <nombre>
	elemento = manejador.FirstChild("Lec").FirstChild("nombre").ToElement();
	nombre = elemento -> GetText();

	cout << "Nombre: " << nombre << endl;

	// Leemos las imágenes
	elemento = manejador.FirstChild("Lec").FirstChild("elementos").FirstChild("img").ToElement();

	// Iteramos sobre las imágenes definidas en el XML (nodos hijos img)
	for(; elemento; elemento = elemento -> NextSiblingElement("img") ){

	    // Leemos la ruta
	    string ruta;
	    elemento -> QueryStringAttribute("src", &ruta);

	    // Posición
	    int x, y;
	    elemento -> QueryIntAttribute("x", &x);
	    elemento -> QueryIntAttribute("y", &y);

	    int animar, wait, duracion;

	    // Atributo animar. Si no existe, se anima por defecto
	    if(elemento -> QueryIntAttribute("animar", &animar) != TIXML_SUCCESS){
		animar = 1;
	    }
	    
	    // Atributo tiempo de espera. Si no existe, la espera es 0
	    if(elemento -> QueryIntAttribute("wait", &wait) != TIXML_SUCCESS){
		wait = 0;
	    }

	    // Atributo duración de la animación. Si no existe, duración = 20
	    if(elemento -> QueryIntAttribute("duracion", &duracion) != TIXML_SUCCESS){
		duracion = 20;
	    }

	    // Atributo z, profundidad.
	    double z;
	    elemento -> QueryDoubleAttribute("z", &z);

	    // Creamos el elemento y lo introducimos en el vector de imágenes.
	    boost::shared_ptr<elementoImagen> E
		(new elementoImagen(g, ruta, x, y, z, ((animar==1)?true:false), wait, duracion) );
	    elementosImg.push_back(E);
	};



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

    /**
     * @brief Dibuja cada uno de los elementos de la interfaz
     *
     */

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
