/**
 * @file elementosInterfaz.h
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

#ifndef _ELEMENTOSINTERFAZ_H_
#define _ELEMENTOSINTERFAZ_H_

#include <boost/scoped_ptr.hpp>
#include <boost/format.hpp>

#include <Gosu/Gosu.hpp>

#include "animacion.h"
#include "texto.h"
#include "log.h"

/**
 * @brief Bloque de configuración para un elemento de interfaz de cuadro de texto. 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

struct tConfTexto
{
    /// Cadena a escribir.
    string cadena;

    /// Ruta de la fuente a usar.
    string rutaFuente;

    /// Tamaño de la fuente.
    unsigned int tam;

    /// Color de la fuente.
    Gosu::Color color;

    /// Alineación del texto
    Texto::tAlign alineacion;

    /// Sombra
    bool sombra;

    /// Opacidad de la sombra
    int opacidadSombra;

    /// Constructor básico, inicializa algunos valores por defecto.
    tConfTexto ();
};

/**
 * @brief Bloque de configuración para las animaciones. 
 *
 * Se utiliza una estructura para encapsular la configuración
 * de cada animación, en lugar de pasar los parámetros de inicialización al constructor.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */
struct tConfAnim
{
    ///@{
    ///@name Valores iniciales

    /// Posición horizontal inicial
    int inicialX;

    /// Posición vertical inicial.
    int inicialY;

    /// Opacidad inicial
    int inicialA;
    ///@}
    
    ///@{
    ///@name Valores finales

    /// Posición horizontal final.
    int finalX;

    /// Posición vertical final.
    int finalY;

    /// Opacidad final.
    int finalA;

    /// Profundidad
    int z;
    ///@}


    /// Tipo de animación
    Animacion::atribAnim animar;

    /// Espera inicial de la animación
    int wait;

    /// Duración de la animación.

    int duracion;
    tConfAnim ();
};

/**
 * @class Elemento
 *
 * @brief Base para los elementos de la interfaz del menú.
 *
 * Ayuda a abstraer la animación de los elementos.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Elemento
{
protected:
    /// Tipo de animación a realizar.
    Animacion::atribAnim animar;

    ///@{
    ///@name Atributos con el valor final
    int finalX;
    int finalY;
    int finalAlpha;
    double z;
    ///@}

    ///@{
    ///@name Atributos con el valor inicial
    int inicialX;
    int inicialY;
    int inicialAlpha;
    ///@}
    
    ///@{
    ///@name Atributos con el valor actual
    int currentX;
    int currentY;
    int currentAlpha;
    ///@}

    /// Inicializa el objeto animación. 
    void setupAnimacion (int wait, int duracion);

    /// Actualiza la posición actual según la animación definida.
    void actualizarPosicion ();
public:
    Animacion * animacion;

    Elemento(Animacion::atribAnim animar, double z);

    /// Devuelve el ancho del elemento. Cada subclase devolverá el ancho que corresponda.
    virtual int getWidth () = 0;

    /// Devuelve la altura del elemento. Cada subclase devolverá la altura que corresponda.
    virtual int getHeight () = 0;

    /// Devuelve la posición horizontal actual.
    int currX ();

    /// Devuelve la posición vertical actual.
    int currY ();

    /// Ajsuta las posiciones finales para elementos no animados
    void setXY(int x, int y);

    /// Comprueba si el elemento ha sido clickeado, basándose en la posición actual y el tamaño.
    bool clicked (int x, int y);

    /// Método de dibujado, actualiza la posición y llama al método drawEnd.
    void draw ();

    /// Método final de dibujado. Cada subclase debe implementarlo según sea conveniente.
    virtual void drawEnd (int x, int y, double z, int a) = 0;

    ~ Elemento ();
};







class ElementoImagen : public Elemento
{
    boost::scoped_ptr <Gosu::Image> imagen;
    string ruta;
public:
    ElementoImagen (Gosu::Graphics & g, string ruta, double z, Animacion::atribAnim animar);

    void drawEnd (int x, int y, double z, int a);
    int getWidth ();
    int getHeight ();
};





class ElementoTexto : public Elemento
{
    boost::scoped_ptr <Texto> texto;
public:

    ElementoTexto (Gosu::Graphics & g,
		   string str, string rutaFuente,
		   unsigned int tam, Gosu::Color color,
		   unsigned int alineacion, bool sombra, int opacidadSombra,
		   double z,
		   Animacion::atribAnim animar);

    void drawEnd (int x, int y, double z, int a);
    void setText (string s);
    int getWidth ();
    int getHeight ();
};




//////////////////////////////////////////////

class ElementoCombinado : public Elemento
{
    boost::scoped_ptr <Texto> texto;
    int textoX;
    int textoY;
    boost::scoped_ptr <Gosu::Image> imagen;
    Gosu::Graphics & g;
public:
    ElementoCombinado (Gosu::Graphics & g, Animacion::atribAnim animar, double z);

    void setTexto (string str, string rutaFuente, 
		   unsigned int tam, Gosu::Color color, 
		   unsigned int alineacion, 
		   bool sombra, int opacidadSombra, 
		   int tX, int tY);

    void setTexto (tConfTexto t, int x, int y);
    void setTextoXY (int x, int y);
    void setImagen (string ruta);
    void drawEnd (int x, int y, double z, int a);
    int getWidth ();
    int getHeight ();
};
#endif /* _ELEMENTOSINTERFAZ_H_ */
