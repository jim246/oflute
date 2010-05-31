#include "elementosInterfaz.h"

ElementoTexto::ElementoTexto (Gosu::Graphics & g, string str, 
			      string rutaFuente, unsigned int tam, Gosu::Color color, 
			      unsigned int alineacion, bool sombra, int opacidadSombra, 
			      int fX, int fY, int fA, double z, 
			      Animacion::atribAnim animar, int wait, int duracion, 
			      int iX, int iY, int iA)
    : Elemento (animar, fX, fY, fA, z, wait, duracion, iX, iY, iA)
{
	
    texto.reset(new Texto(g, str, rutaFuente, 
			  tam, color, alineacion, 
			  sombra, opacidadSombra));
}
ElementoTexto::ElementoTexto (Gosu::Graphics & g,
		   tConfTexto t,
		   tConfAnim a)
    : Elemento(a)
{
    texto.reset(new Texto(g, t.cadena, t.rutaFuente, 
			  t.tam, t.color, t.alineacion, 
			  t.sombra, t.opacidadSombra));
}

void ElementoTexto::drawEnd (int x, int y, double z, int a)
{
    texto -> draw(x, y, z, a);
}

void ElementoTexto::setText (string s)
{
    texto -> setText(s);
}

int ElementoTexto::getWidth ()
{
    return 0;
}

int ElementoTexto::getHeight ()
{
    return 0;
}
