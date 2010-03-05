#include "estadoAnalizador.h"
#include "juego.h"

//int posFinalesY[] = {281, 333, 386, 441, 494 };
estadoAnalizador::estadoAnalizador (Juego * p) : estado(p){
    cout << "* Se crea estadoAnalizador" << endl;
    lanzado = false;
}

void estadoAnalizador::lanzar(){
    cout << "* estadoAnalizador lanzado" << endl;
    lanzado = true;

    // Poblamos el puntero de las imágenes
    imgFondo.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/analizadorAssets/baseAnalizador.png"));
}

void estadoAnalizador::update(){
    if(!lanzado) 
	return;
}

void estadoAnalizador::draw(){
    if(!lanzado) 
	return;

    imgFondo -> draw(0,0,1,
		     1,1,
		     Gosu::Color(255,255,255,255));      
}

void estadoAnalizador::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    if (boton == Gosu::kbEscape){
//	padre -> cambiarEstado("estadoIntro");
	padre -> close();
//	accionPosterior();
    }
}
