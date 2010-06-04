/**
 * @file estadoLecciones.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * 
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

#ifndef _ESTADOLECCIONES_H_
#define _ESTADOLECCIONES_H_

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <Gosu/Gosu.hpp>

#include "estado.h"
#include "elementosInterfaz.h"

#include <string>
#include <vector>
#include <algorithm>

using namespace std;



class Leccion;

class Juego;

/**
 * @class EstadoMenuLecciones
 *
 * @brief Clase que modela el menú de selección de las lecciones.
 *
 * 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */
class EstadoMenuLecciones : public Estado{
    /// Imagen para el fondo
    boost::scoped_ptr<Gosu::Image> imgFondo;


    boost::scoped_ptr<ElementoImagen> pizarra;

    boost::scoped_ptr<ElementoCombinado> barraSuperior;

    boost::scoped_ptr<ElementoCombinado> barraInferior;

    boost::scoped_ptr<ElementoCombinado> btn1;
    boost::scoped_ptr<ElementoCombinado> btnDescripcion;

    boost::scoped_ptr<ElementoTexto> textoDesc;

    boost::scoped_ptr<ElementoCombinado> btnComenzar;
    boost::scoped_ptr<ElementoCombinado> btnAntLec;
    boost::scoped_ptr<ElementoCombinado> btnSigLec;

    struct infoLeccion{ 
	int indice;
	string nombre, descrip, ruta;
    };

    struct ordenarLecciones{
	bool operator()(infoLeccion a, infoLeccion b){
	    return b.indice > a.indice;
	}
    };

    int leccionActual;

    vector<infoLeccion> leccionesCargadas;

    enum {eSaliendo, eEsperando, eGuardando, eMostrandoLec};

    int estadoActual;

    Leccion * leccionMostrada;
public:
    EstadoMenuLecciones(Juego * p);

    void update();
    
    void draw();

    void listarLecciones();

    void buttonDown(Gosu::Button boton);

    void anteriorLec();
    void siguienteLec();

    void cambiarLeccion(unsigned n);

    ~EstadoMenuLecciones();
};

#endif /* _ESTADOLECCIONES_H_ */
