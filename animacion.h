/**
 * @file animacion.h
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



#ifndef _ANIMACION_H_
#define _ANIMACION_H_

#include <cmath>
#include <iostream>

using namespace std;

/**
 * @class Animacion
 *
 * @brief Calcula y devuelve valores para realizar animaciones.
 *
 * Contiene una serie de ecuaciones con las que lograr efectos de aceleración y deceleración en las animaciones.
 *
 * Por ahora hace una animación en dos variables simultáneamente, pero está pensado generalizarlo.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Animacion{
    
public:
    /// Diferentes tipos de animaciones
    enum tipoAnim {tEaseInQuad, tEaseOutQuad, tEaseInOutQuad,
		   tEaseInCubic, tEaseOutCubic, tEaseInOutCubic,
		   tEaseInQuart, tEaseOutQuart, tEaseInOutQuart,
		   tEaseOutBack, tLinear};
private:

    /// Número de atributos a animar
    int numAttr;

    /// Duración de la animación
    int duracion;

    /// Espera inicial antes de iniciar la animación
    int esperaInicial;

    /// Contador del tiempo pasado
    int time;

    /// Vector de posiciones iniciales
    int * inicial;

    /// Vector de posiciones finales
    int * final;

    /// Vector de recorridos (diferencia entre final e inicial)
    int * change;

    /// Vector de posiciones actuales
    float * actual;

    /// Tipo de animación a realizar
    tipoAnim anim;

    /// Puntero a la función de animación
    float (*puntFun) (float, float, float, float);
    
public:
    /**
     * @brief Crea una nueva animación
     * 
     * Se inicializan los vectores para cada uno de los atributos a animar.
     *
     * @param n Número de atributos en los que se hará la animación.
     * @param d Duración de la animación.
     * @param anim Tipo de animación.
     * @param e Espera inicial antes de empezar la animación.
     *
     */

    Animacion(int n, int d, tipoAnim anim = tEaseInQuad, int e = 0);

    /**
     * @brief Reinicia la animación al estado inicial
     */
    inline void init();

    /**
     * @brief Coloca la animación en su estado final
     */
    void end();

    /**
     * @brief Comprueba si la animación ha terminado.
     * @return Verdadero si la animación ha terminado.
     */
    bool finished();

    /**
     * @brief Devuelve el valor actual del atributo indicado.
     *
     * @param i El índice del atributo cuyo valor hay que consultar.
     * @return El valor del atributo.
     *
     */
    float get(int i);


    void setInicial(int i, int v);

    void setFinal(int i, int v);

    void set(int i, int v1, int v2);

    /**
     * @brief Selecciona la ecuación de la animación.
     *
     * @param a Ecuación a asignar.
     */
    void setTipoAnimacion(tipoAnim a);

    /**
     * @brief Asigna la duración de la animación.
     * @param d Duración de la animación.
     */
    void setDuracion(int d) { duracion = d; }

    /**
     * @brief Asigna el tiempo de espera de la animación.
     * @param Tiempo de espera.
     */

    void setEspera(int e) { esperaInicial = e; }

    /**
     * @brief Actualiza la animación un paso.
     */

    void update(bool a = true);


    /**
     * @name Ecuaciones de tweening
     * Todas las ecuaciones de tweening reciben cuatro argumentos:
     * - Tiempo pasado.
     * - Valor inicial.
     * - Diferencia entre el valor final y el inicial.
     * - Duración de la animación.
     */

    //@{


    static float easeLinear(float t, float b, float c, float d);

    static float easeInQuad (float t, float b, float c, float d);
    static float easeOutQuad(float t, float b, float c, float d);
    static float easeInOutQuad(float t, float b, float c, float d);
    
    static float easeInCubic(float t, float b, float c, float d) ;
    static float easeOutCubic(float t, float b, float c, float d) ;
    static float easeInOutCubic(float t, float b, float c, float d);


    static float easeInQuart(float t, float b, float c, float d) ;
    static float easeOutQuart(float t, float b, float c, float d) ;
    static float easeInOutQuart(float t, float b, float c, float d);

    static float easeOutBack(float t, float b, float c, float d);
    //@}

    /// Libera la memoria de los diferentes vectores.
    ~Animacion();
};

#endif /* _ANIMACION_H_ */
