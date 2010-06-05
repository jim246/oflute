#include "elementosInterfaz.h"

ElementoImagen::ElementoImagen (Gosu::Graphics & g, string ruta, 
				int fX, int fY, int fA, double z, 
				Animacion::atribAnim animar, int wait, int duracion, 
				int iX, int iY, int iA)
    : Elemento (animar, fX, fY, fA, z, wait, duracion, iX, iY, iA), 
      ruta (ruta)
{
    imagen.reset(new Gosu::Image(g, Gosu::widen(ruta)));	
}

ElementoImagen::ElementoImagen (Gosu::Graphics & g, string ruta, tConfAnim t)
    : Elemento (t.animar, t.finalX, t.finalY, t.finalA, t.z, 
		t.wait, t.duracion, 
		t.inicialX, t.inicialY, t.inicialA), 
      ruta (ruta)
{
    lDEBUG << "New ElementoImagen" << ruta;
    imagen.reset(new Gosu::Image(g, Gosu::widen(ruta)));
}

ElementoImagen::ElementoImagen (Gosu::Graphics & g, string ruta, double z, Animacion::atribAnim animar)
    : Elemento (animar, z)
{
    imagen.reset(new Gosu::Image(g, Gosu::widen(ruta)));
}

void ElementoImagen::drawEnd (int x, int y, double z, int a)
{
//    lDEBUG << "img @ " << x << "," << y << "," << z << "(" << a;
    imagen -> draw(x,y,z,1,1, Gosu::Color(a, 255, 255, 255));
}

int ElementoImagen::getWidth ()
{
    return imagen -> width();
}

int ElementoImagen::getHeight ()
{
    return imagen -> height();
}

