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

#include "foreach.h"
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
    boost::shared_ptr<ElementoImagen> pizarra;

    boost::shared_ptr<ElementoCombinado> barraSuperior;

    boost::shared_ptr<ElementoCombinado> barraInferior;

    boost::shared_ptr<ElementoCombinado> btnTitular;
    boost::shared_ptr<ElementoCombinado> btnDescripcion;

    boost::shared_ptr<ElementoTexto> textoDesc;

    boost::shared_ptr<ElementoCombinado> btnComenzar;
    boost::shared_ptr<ElementoCombinado> btnAntLec;
    boost::shared_ptr<ElementoCombinado> btnSigLec;

    vector<boost::shared_ptr<Elemento> > conjuntoElementos;
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

    enum {eMostrando, eMenu, eOcultarInter, eMostrarInter, eLeccion, eOcultando};

    int estadoActual;

    Leccion * leccionMostrada;

    enum{dirMOSTRAR, dirOCULTAR};
    void iniciarAnimacionSalida(int dir, bool saltarBarraInferior = true);
public:
    EstadoMenuLecciones(Juego * p);

    void update();
    
    void draw();

    void listarLecciones();

    void buttonDown(Gosu::Button boton);

    void anteriorLec();
    void siguienteLec();

    void cambiarLeccion(unsigned n);
    void lanzarLeccion();

    ~EstadoMenuLecciones();
};

#endif /* _ESTADOLECCIONES_H_ */
