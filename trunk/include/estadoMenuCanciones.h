/**
 * @file estadoMenuCanciones.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
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


#ifndef _ESTADOMENUCANCIONES_H_
#define _ESTADOMENUCANCIONES_H_

#include "estado.h"

#include "elementosInterfaz.h"

#include <vector>
using std::vector;

class Juego;
class Cancion;
/**
 * @class EstadoMenuCanciones
 * @ingroup estadosPrincipales
 *
 * @brief Menú de elección de canción.
 *
 * Permite al usuario elegir la canción, y lanzarla.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class EstadoMenuCanciones : public Estado{
public:
    EstadoMenuCanciones(Juego * p);

	/// Gestiona las transiciones
    void update();

	/// Dibuja los elementos gráficos
    void draw();

	/// Responde a la entrada del usuario
    void buttonDown(Gosu::Button boton);

	/// Liberación de recursos
    ~EstadoMenuCanciones();

private:
	/// Diferentes estados de transición
    enum tTrans{ transIn, transHold, mostrandoCancion, transOut };

	/// Estado de transición actual
    tTrans estadoTransicion;

	/// Canción actualmente cargada
    boost::scoped_ptr<Cancion> cancion;

	/// Imagen del logotipo
    boost::scoped_ptr<ElementoImagen> imgLogotipo;

	boost::scoped_ptr<ElementoImagen> imgSeleccion;

	boost::scoped_ptr<ElementoImagen> imgBtnUp;
	boost::scoped_ptr<ElementoImagen> imgBtnDown;
	boost::scoped_ptr<ElementoImagen> imgBtnOk;

	/// Subtítulo
    boost::scoped_ptr<ElementoTexto> txtSubtitulo;

	class EntradaMenuCanciones{
	public:
		EntradaMenuCanciones(Gosu::Graphics & g, string titulo, 
		                     string descripcion, string ruta, int pos);

		void draw();
	private:
		Gosu::Graphics & g;

		string titulo;

		string descripcion;

		string ruta;

		int pos;

		boost::scoped_ptr<Gosu::Font> txtTitulo, txtDescripcion;
	};

	vector<boost::shared_ptr<EntradaMenuCanciones> > conjuntoCanciones;
};

#endif /* _ESTADOMENUCANCIONES_H_ */
