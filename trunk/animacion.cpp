#include "animacion.h"

Animacion::Animacion(int iX, int iY, int fX, int fY, int d, tipoAnim anim, int e):
    inicialX(iX), inicialY(iY), finalX(fX), finalY(fY), 
    time(0), duration(d),  esperaInicial(e),
    currX(inicialX), currY(inicialY),
    changeX(finalX - inicialX), changeY(finalY - inicialY),
    anim(anim){
    cout << "+++ Animación::Constructor" << endl;
}

//void Animacion::init(){ time = 0; }

// ######################################################
// Ecuaciones de tweening

float Animacion::easeLinear(float t, float b, float c, float d){
    return c * t / d + b;
}

float Animacion::easeInQuad (float t, float b, float c, float d) {
    t/=d;
    return c*t*t + b;
};

float Animacion::easeOutQuad(float t, float b, float c, float d) {
    t/=d;
    return -c *(t)*(t-2) + b;
};
    
float Animacion::easeInOutQuad(float t, float b, float c, float d) {
    t /= d/2;
    if (t < 1){
	return c/2*t*t + b;
    }else{
	--t;
	return -c/2 * ((t)*(t-2) - 1) + b;
    }
};
    
float Animacion::easeInCubic(float t, float b, float c, float d) {
    t/=d;
    return c*(t)*t*t + b;
};

float Animacion::easeOutCubic(float t, float b, float c, float d) {
    t=t/d-1;
    return c*(t*t*t + 1) + b;
};

float Animacion::easeInOutCubic(float t, float b, float c, float d) {
    t/=d/2;
    if ((t) < 1){
	return c/2*t*t*t + b;
    }else{
	t-=2;
	return c/2*((t)*t*t + 2) + b;
    }
};


float Animacion::easeInQuart(float t, float b, float c, float d) {
    t/=d;
    return c*(t)*t*t*t + b;
};

float Animacion::easeOutQuart(float t, float b, float c, float d) {
    t=t/d-1;
    return -c * ((t)*t*t*t - 1) + b;
};

float Animacion::easeInOutQuart(float t, float b, float c, float d) {
    t/=d/2;
    if ((t) < 1){
	return c/2*t*t*t*t + b;
    }else{
	t-=2;
	return -c/2 * ((t)*t*t*t - 2) + b;
    }
};

float Animacion::easeOutBack(float t, float b, float c, float d){
//    float s = 1.70158;
    float s = 1.3;
    t = t/d - 1;
    return c*(t*t*((s+1)*t + s) + 1) + b;
};

/*
float Animacion::getX() { return currX; }
float Animacion::getY() { return currY; } //*/

void Animacion::update(){
    if(time - esperaInicial > duration){
	currX = finalX;
	currY = finalY;
	return;
    }else if(time >= esperaInicial){
	switch(anim){
	case tLinear:
	    currX = easeLinear(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeLinear(time - esperaInicial, inicialY, changeY, duration);
	    break;
	    
	case tEaseInQuad:
	    currX = easeInQuad(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeInQuad(time - esperaInicial, inicialY, changeY, duration);
	    break;
	case tEaseOutQuad:
	    currX = easeOutQuad(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeOutQuad(time - esperaInicial, inicialY, changeY, duration);
	    break;
	case tEaseInOutQuad:
	    currX = easeInOutQuad(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeInOutQuad(time - esperaInicial, inicialY, changeY, duration);
	    break;
	    
	case tEaseInCubic:
	    currX = easeInCubic(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeInCubic(time - esperaInicial, inicialY, changeY, duration);
	    break;
	case tEaseOutCubic:
	    currX = easeOutCubic(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeOutCubic(time - esperaInicial, inicialY, changeY, duration);
	    break;
	case tEaseInOutCubic:
	    currX = easeInOutCubic(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeInOutCubic(time - esperaInicial, inicialY, changeY, duration);
	    break;
	    
	    
	case tEaseInQuart:
	    currX = easeInQuart(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeInQuart(time - esperaInicial, inicialY, changeY, duration);
	    break;
	case tEaseOutQuart:
	    currX = easeOutQuart(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeOutQuart(time - esperaInicial, inicialY, changeY, duration);
	    break;
	case tEaseInOutQuart:
	    currX = easeInOutQuart(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeInOutQuart(time - esperaInicial, inicialY, changeY, duration);
	    break;

	case tEaseOutBack:
	    currX = easeOutBack(time - esperaInicial, inicialX, changeX, duration);
	    currY = easeOutBack(time - esperaInicial, inicialY, changeY, duration);
	}
    }
    
    ++time;
}



Animacion::~Animacion(){
    cout << "--- Animación::DESTRUCTOR" << endl;
}

