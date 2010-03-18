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

class Animacion{
public:
    enum tipoAnim {tEaseInQuad, tEaseOutQuad, tEaseInOutQuad,
		   tEaseInCubic, tEaseOutCubic, tEaseInOutCubic,
		   tEaseInQuart, tEaseOutQuart, tEaseInOutQuart};

    Animacion(unsigned iX, unsigned iY, unsigned fX, unsigned fY, int d, tipoAnim anim = tEaseInQuad):
	inicialX(iX), inicialY(iY), finalX(fX), finalY(fY), time(0), duration(d),  
	changeX(finalX - inicialX), changeY(finalY - inicialY),
	currX(inicialX), currY(inicialY), anim(anim){
	cout << ">>> Animación::CONSTRUCTOR" << endl;
    }

    void init(){ time = 0; }

// ######################################################
// Ecuaciones de tweening

    float easeInQuad (float t, float b, float c, float d) {
	t/=d;
	return c*t*t + b;
    };

    float easeOutQuad(float t, float b, float c, float d) {
	t/=d;
	return -c *(t)*(t-2) + b;
    };
    
    float easeInOutQuad(float t, float b, float c, float d) {
	t /= d/2;
	if (t < 1){
	    return c/2*t*t + b;
	}else{
	    --t;
	    return -c/2 * ((t)*(t-2) - 1) + b;
	}
    };
    
    float easeInCubic(float t, float b, float c, float d) {
	t/=d;
	return c*(t)*t*t + b;
    };

    float easeOutCubic(float t, float b, float c, float d) {
	t=t/d-1;
	return c*(t*t*t + 1) + b;
    };

    float easeInOutCubic(float t, float b, float c, float d) {
	t/=d/2;
	if ((t) < 1){
	    return c/2*t*t*t + b;
	}else{
	    t-=2;
	    return c/2*((t)*t*t + 2) + b;
	}
    };


    float easeInQuart(float t, float b, float c, float d) {
	t/=d;
	return c*(t)*t*t*t + b;
    };

    float easeOutQuart(float t, float b, float c, float d) {
	t=t/d-1;
	return -c * ((t)*t*t*t - 1) + b;
    };

    float easeInOutQuart(float t, float b, float c, float d) {
	t/=d/2;
	if ((t) < 1){
	    return c/2*t*t*t*t + b;
	}else{
	    t-=2;
	    return -c/2 * ((t)*t*t*t - 2) + b;
	}
    };

    float getX() { return currX; }
    float getY() { return currY; }

    void update(){
	if(time > duration){
	    currX = finalX;
	    currY = finalY;
	}else{
	    switch(anim){
	    case tEaseInQuad:
		currX = easeInQuad(time, inicialX, changeX, duration);
		currY = easeInQuad(time++, inicialY, changeY, duration);
		break;
	    case tEaseOutQuad:
		currX = easeOutQuad(time, inicialX, changeX, duration);
		currY = easeOutQuad(time++, inicialY, changeY, duration);
		break;
	    case tEaseInOutQuad:
		currX = easeInOutQuad(time, inicialX, changeX, duration);
		currY = easeInOutQuad(time++, inicialY, changeY, duration);
		break;

	    case tEaseInCubic:
		currX = easeInCubic(time, inicialX, changeX, duration);
		currY = easeInCubic(time++, inicialY, changeY, duration);
		break;
	    case tEaseOutCubic:
		currX = easeOutCubic(time, inicialX, changeX, duration);
		currY = easeOutCubic(time++, inicialY, changeY, duration);
		break;
	    case tEaseInOutCubic:
		currX = easeInOutCubic(time, inicialX, changeX, duration);
		currY = easeInOutCubic(time++, inicialY, changeY, duration);
		break;


	    case tEaseInQuart:
		currX = easeInQuart(time, inicialX, changeX, duration);
		currY = easeInQuart(time++, inicialY, changeY, duration);
		break;
	    case tEaseOutQuart:
		currX = easeOutQuart(time, inicialX, changeX, duration);
		currY = easeOutQuart(time++, inicialY, changeY, duration);
		break;
	    case tEaseInOutQuart:
		currX = easeInOutQuart(time, inicialX, changeX, duration);
		currY = easeInOutQuart(time++, inicialY, changeY, duration);
		break;
	    }
	}
    }

    

    ~Animacion(){
	cout << "<<< Animación::DESTRUCTOR" << endl;
    }

private:
    unsigned inicialX, inicialY, finalX, finalY;
    unsigned time, duration;
    int changeX, changeY;
    
    float currX, currY;
    float (*puntero) (float, float, float, float);

    tipoAnim anim;

};

#endif /* _ANIMACION_H_ */
