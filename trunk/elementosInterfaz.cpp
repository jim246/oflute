#include "elementosInterfaz.h"

tConfTexto::tConfTexto ()
    : color (Gosu::Color(255,255,255,255)), 
      alineacion (Texto::alignIzq), 
      sombra (true), 
      opacidadSombra (80)
{}


tConfAnim::tConfAnim ()
    : inicialX (0), inicialY (0), inicialA (0), 
      finalX (0), finalY (0), finalA (255), 
      z (0), animar (Animacion::tNada), 
      wait (0), duracion (30)
{}

void Elemento::setupAnimacion (int wait, int duracion)
{
    if(animar != Animacion::tNada){
	lDEBUG << "** Se animará. Attrib: " << animar << endl;
	    
	if(animar == Animacion::tAlpha){
	    animacion = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
	    animacion -> set (0, inicialAlpha, finalAlpha);
	}
	    
	else if(animar == Animacion::tPos){
	    animacion = new Animacion(2, duracion, Animacion::tEaseOutQuad, wait);
	    animacion -> set(0, inicialX, finalX);
	    animacion -> set(1, inicialY, finalY);
	}
	    
	else if(animar == Animacion::tAlphaPos){
	    animacion = new Animacion(3, duracion, Animacion::tEaseOutQuad, wait);
	    animacion -> set(0, inicialAlpha, finalAlpha);
	    animacion -> set(1, inicialX, finalX);
	    animacion -> set(2, inicialY, finalY);
	}
    }else{
	animacion = 0;
    }
}
void Elemento::actualizarPosicion ()
{

    if(animar != Animacion::tNada){

	if(animar == Animacion::tAlpha){
	    currentAlpha = animacion -> get(0);
	    currentX = finalX;
	    currentY = finalX;
	}

	else if(animar == Animacion::tPos){
	    currentAlpha = finalAlpha;
	    currentX = animacion -> get(0);
	    currentY = animacion -> get(1);
	}

	else{
	    currentAlpha = animacion -> get(0);
	    currentX = animacion -> get(1);
	    currentY = animacion -> get(2);
	}
    }else{
	currentX = finalX;
	currentY = finalY;
	currentAlpha = finalAlpha;
    }
}

Elemento::Elemento (Animacion::atribAnim animar, 
		    int fX, int fY, int fA, double z, 
		    int wait, int duracion, 
		    int iX, int iY, int iA)
    : animar (animar), finalX (fX), finalY (fY), finalAlpha (fA), z (z), inicialX (iX), inicialY (iY), inicialAlpha (iA)
{
    setupAnimacion(wait, duracion);
}

Elemento::Elemento (tConfAnim t)
    : animar (t.animar), 
      finalX (t.finalX), finalY (t.finalY), finalAlpha (t.finalA), z (t.z), 
      inicialX (t.inicialX), inicialY (t.inicialY), inicialAlpha (t.inicialA)
{
    setupAnimacion(t.wait, t.duracion);
}

int Elemento::currX (){ 
    return currentX; 
}

int Elemento::currY (){ 
    return currentY; 
}

bool Elemento::clicked (int x, int y)
{
    return (x >= currentX && x <= currentX + getWidth() &&
	    y >= currentY && y <= currentY + getHeight());
}

void Elemento::draw ()
{
    if(animar != Animacion::tNada){
	animacion -> update();
    }
    actualizarPosicion();
    drawEnd(currentX, currentY, z, currentAlpha);
}

Elemento::~ Elemento ()
{
    if(animar != Animacion::tNada){
	delete animacion;
    }
}


