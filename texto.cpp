#include "texto.h"

int Texto::dividirTexto(){
	
    string::size_type lastPos = texto.find_first_not_of('\n', 0);
    // Find first "non-delimiter".
    string::size_type pos     = texto.find_first_of('\n', lastPos);
	
    while (string::npos != pos || string::npos != lastPos)
    {
	// Found a token, add it to the vector.
	lineas.push_back(texto.substr(lastPos, pos - lastPos));
	// Skip '\n'.  Note the "not_of"
	lastPos = texto.find_first_not_of('\n', pos);
	// Find next "non-delimiter"
	pos = texto.find_first_of('\n', lastPos);
    }	
    return lineas.size();
}

Texto::Texto(Gosu::Graphics& graphics, 
      string texto, string rutaFuente, unsigned tam, Gosu::Color color,
      unsigned alineacion, 
      bool sombra, unsigned opSombra, int x, int y, int z) 
    : 
    graphics(graphics), texto(texto), tam(tam), color(color), 
    alineacion(alineacion), sombra(sombra), opacidadSombra(opSombra), x(x), y(y), z(z){
	

    int n = dividirTexto();
    for (int i = 0; i < n; ++i)
    {
	boost::shared_ptr<customFont> f (new customFont(graphics, Gosu::widen(rutaFuente), tam));
	fuentes.push_back(f);
	if(sombra){
	    f.reset(new customFont(graphics, Gosu::widen(rutaFuente), tam));
	    fuentesSombra.push_back(f);
	}
    }

    offsetShadow[0] = 1;
    offsetShadow[1] = 2;
}

void Texto::update(){ }

void Texto::draw(){
    drawAlpha(255);
}


void Texto::drawAlpha(int a){
	
    int salto = fuentes[0] -> saltoLinea();
    short i = 0;


    BOOST_FOREACH(string& s, lineas)
    {
	int destX = 0;

	// Alineación a la izquierda
	if(alineacion == 1){
	    destX = x;
	}
	// Alineación a la derecha
	else if(alineacion == 3){
	    destX = x - fuentes[i] -> textWidth(s);
	}

	// Centrado
	else{
	    destX = x - fuentes[i] -> textWidth(s) / 2;
	}

	color.setAlpha(a);
	fuentes[i] -> draw(s, destX, y + salto * i, z + 0.1, color);
	    
	if(sombra){
	    fuentesSombra[i] -> draw(s, destX + offsetShadow[0], y + salto * i + offsetShadow[1],
				     z, Gosu::Color(opacidadSombra * a / 255, 0, 0, 0));
	}

	i++;
    } 

    //*/
	
}

void Texto::draw(int z_){
    z = z_;
    draw();
}

void Texto::draw(int x_, int y_, int z_, int a_){
    x = x_;
    y = y_;
    z = z_;
    drawAlpha(a_);
}
