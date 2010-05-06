// animacion.h --- 

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


#ifndef _ANIMACION_H_
#define _ANIMACION_H_

#include <cmath>
#include <iostream>
using namespace std;


class Animacion{
    int inicialX, inicialY, finalX, finalY;
    int time, duration, esperaInicial;
    float currX, currY;
    int changeX, changeY;

public:
    enum tipoAnim {tEaseInQuad, tEaseOutQuad, tEaseInOutQuad,
		   tEaseInCubic, tEaseOutCubic, tEaseInOutCubic,
		   tEaseInQuart, tEaseOutQuart, tEaseInOutQuart,
		   tEaseOutBack, tLinear};

    Animacion(int iX, int iY, 
	      int fX, int fY, int d, 
	      tipoAnim anim = tEaseInQuad, int e=0);

    inline void init() { time = 0; };
    inline void end() { time = duration + esperaInicial; };

    inline bool finished(){ return time >= duration + esperaInicial;  }

    inline float getX() { return currX; };
    inline float getY() { return currY; };
    
    inline void setInicialX(int x) { inicialX = x; changeX = finalX - inicialX; }
    inline void setInicialY(int y) { inicialY = y; changeY = finalY - inicialY; }

    inline void setFinalX(int x) { finalX = x; changeX = finalX - inicialX; }
    inline void setFinalY(int y) { finalY = y; changeY = finalY - inicialY; }

    inline void setTipoAnimacion(tipoAnim a){ anim = a; }

    inline void setDuracion(int d) { duration = d; }
    inline void setEspera(int e) { esperaInicial = e; }



// ######################################################
// Ecuaciones de tweening

    float easeLinear(float t, float b, float c, float d);

    float easeInQuad (float t, float b, float c, float d);
    float easeOutQuad(float t, float b, float c, float d);
    float easeInOutQuad(float t, float b, float c, float d);
    
    float easeInCubic(float t, float b, float c, float d) ;
    float easeOutCubic(float t, float b, float c, float d) ;
    float easeInOutCubic(float t, float b, float c, float d);


    float easeInQuart(float t, float b, float c, float d) ;
    float easeOutQuart(float t, float b, float c, float d) ;
    float easeInOutQuart(float t, float b, float c, float d);

    float easeOutBack(float t, float b, float c, float d);

    void update();
    

    ~Animacion();

private:
    tipoAnim anim;

};

#endif /* _ANIMACION_H_ */
