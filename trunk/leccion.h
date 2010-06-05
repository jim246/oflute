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

#include "pugixml.hpp"
#include "log.h"

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
    /// Índice de la lección en el listado de lecciones.
    unsigned indice;

    /// Nombre de la lección.
    string nombre;

    /// Referencia al contenedor gráfico.
    Gosu::Graphics& g;

    /// Contenedor de los elementos de la interfaz.
    vector<boost::shared_ptr<Elemento> > elementos;

    /// Contenedor de las animaciones de cada elemento de la interfaz.
    vector<boost::shared_ptr<Animacion> > animaciones;

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
	pugi::xml_document doc;
	pugi::xml_parse_result resultado;
	pugi::xml_node nodoActual, nodoVacio;
	pugi::xml_attribute atributo, atributoVacio;

	// Intentamos leer y cargar el fichero en el objeto XML
	resultado = doc.load_file(ruta.c_str());
	if(!resultado){
	    cerr << "#### ERROR al intentar abrir el fichero '" << ruta << "'." << endl;
	    /// @todo Arreglar el control de errores cuando no existe el XML
	    throw 42;
	}

	nodoActual = doc.child("Lec").child("elementos");

	///////////////////////////////////////
	// Iteramos sobre las imágenes definidas en el XML (nodos hijos img)
	for(pugi::xml_node elemento = nodoActual.child("img");
	    elemento;
	    elemento = elemento.next_sibling("img")){

	    // Leemos la ruta
	    string ruta = elemento.attribute("src").value();
		
	    // Posicióºn
	    int x = elemento.attribute("x").as_int();
	    int y = elemento.attribute("y").as_int();

	    int animar, wait, duracion;

	    if((atributo = elemento.attribute("animar")) == atributoVacio){
		animar = 1;
	    }else{
		animar = atributo.as_int();
	    }

	    if((atributo = elemento.attribute("wait")) == atributoVacio){
		wait = 0;
	    }else{
		wait = atributo.as_int();
	    }

	    if((atributo = elemento.attribute("duracion")) == atributoVacio){
		duracion = 20;
	    }else{
		duracion = atributo.as_int();
	    }	    
		
	    // Atributo z, profundidad.
	    double z = elemento.attribute("z").as_double();

	    lDEBUG << "Imagen (" << ruta << ") @ " << x << "," << y;

	    
	    // Creamos el elemento y lo introducimos en el vector de elementos
	    boost::shared_ptr<Elemento> E
	    	(new ElementoImagen(g, ruta, z, ((animar==1)?Animacion::tAlpha:Animacion::tNada)));
	    E -> setXY(x, y);
	    if(animar == 1){
		E -> animacion = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
		E -> animacion -> set(0, 0, 255);
	    }

	    

	    elementos.push_back(E);
	    //*/
	};
	    




	//////////////////////////////////////
	// TEXTOS
	for(pugi::xml_node elemento = nodoActual.child("texto");
	    elemento;
	    elemento = elemento.next_sibling("texto")){

	    string texto;
	    texto = elemento.first_child().value();

	    string rutaFuente;
	    if((atributo = elemento.attribute("fuente")) == atributoVacio){
		rutaFuente = "media/fNormal.ttf";
	    }else{
		rutaFuente = atributo.value();
	    }

	    // Posición
	    int x = elemento.attribute("x").as_int();
	    int y = elemento.attribute("y").as_int();
	    int tam = elemento.attribute("tam").as_int();
	    int align = elemento.attribute("align").as_int();
	    int sombra = elemento.attribute("sombra").as_int();
	    int opacSombra = elemento.attribute("opacSombra").as_int();

	    int animar, wait, duracion;

	    if((atributo = elemento.attribute("animar")) == atributoVacio){
		animar = 1;
	    }else{
		animar = atributo.as_int();
	    }

	    if((atributo = elemento.attribute("wait")) == atributoVacio){
		wait = 0;
	    }else{
		wait = atributo.as_int();
	    }

	    if((atributo = elemento.attribute("duracion")) == atributoVacio){
		duracion = 20;
	    }else{
		duracion = atributo.as_int();
	    }	    
		
	    // Atributo z, profundidad.
	    double z = elemento.attribute("z").as_double();

	    int ca = elemento.attribute("ca").as_int();
	    int cr = elemento.attribute("cr").as_int();
	    int cg = elemento.attribute("cg").as_int();
	    int cb = elemento.attribute("cb").as_int();
	    
	    lDEBUG << "Texto (" << ruta << ") @ " << x << "," << y << " :";

	    
	    boost::shared_ptr<Elemento> T
		( new ElementoTexto(g, texto, rutaFuente, tam, 
				    Gosu::Color(ca, cr, cg, cb), align,
				    sombra, opacSombra, z+3, 
				    (animar == 1)? Animacion::tAlpha:Animacion::tNada) );

	    T -> setXY(x, y);
	    if(animar == 1){
		T -> animacion = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
		T -> animacion -> set(0, 0, 255);
	    }

	    elementos.push_back(T);//*/

	} //*/
	
    }

    /**
     * @brief Dibuja cada uno de los elementos de la interfaz
     *
     */

    void draw(){

	BOOST_FOREACH(boost::shared_ptr<Elemento>& T, elementos)
	{
	    T -> draw();
	}
    }

};

#endif /* _LECCION_H_ */
