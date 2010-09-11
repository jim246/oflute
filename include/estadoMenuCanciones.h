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
	enum tTrans{ transIn, transHold, transToCancion, transCancion, transOut };

    /// Estado de transición actual
    tTrans estadoTransicion;

    /// Canción actualmente cargada
    boost::scoped_ptr<Cancion> cancion;
    
    /// Indica si hay una canción cargada
    bool cancionCargada;

    /// Imagen del logotipo
    boost::scoped_ptr<ElementoImagen> imgLogotipo;

    /// Imagen para el marco de selección
    boost::scoped_ptr<ElementoImagen> imgSeleccion;

    /// Imagen para el botón de arriba
    boost::scoped_ptr<ElementoImagen> imgBtnUp;

    /// Imagen para el botón de abajo
    boost::scoped_ptr<ElementoImagen> imgBtnDown;

    /// Imagen para el botón de OK
    boost::scoped_ptr<ElementoImagen> imgBtnOk;

    /// Subtítulo
    boost::scoped_ptr<ElementoTexto> txtSubtitulo;

    /// Botón volver
    boost::scoped_ptr<ElementoCombinado> btnVolver;

    class EntradaMenuCanciones{
    public:
	EntradaMenuCanciones(Gosu::Graphics & g, string titulo, 
			     string descripcion, string ruta, int pos);

	void draw();
	void mover(int a);
	string getRuta();

    private:
	Gosu::Graphics & g;

	string titulo;

	string descripcion;

	string ruta;

	int pos;

	float y_final, y_actual, pasos;

	int posInicial;

	int saltoEntreEntradas;

	boost::scoped_ptr<Gosu::Font> txtTitulo, txtDescripcion;
    };

    /// Conjunto de canciones listadas
    vector<boost::shared_ptr<EntradaMenuCanciones> > conjuntoCanciones;

    /// Indicador de la canción actualmente seleccionada
    int cancionSeleccionada;

    /// Lista las canciones
    void listarCanciones();
    
    /// Pasa a la canción siguiente, moviendo el menú.
    void listaSiguiente();

    /// Pasa a la canción anterior, moviendo el menú.
    void listaAnterior();

    /// Iniverte las animaciones de todos los elementos
    void invertirAnimaciones();
};

#endif /* _ESTADOMENUCANCIONES_H_ */
