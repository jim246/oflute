#include "estadoIntro.h"
#include "juego.h"

estadoIntro::estadoIntro (Juego * p) : 
    estadoImagenFija(p,
		     Gosu::resourcePrefix() + L"media/estadoIntro.png"){
    cout << "** estadoIntro::CONSTRUCTOR" << endl;
}

void estadoIntro::accionPosterior(){
    padre -> cambiarEstado ("estadoMenu");
}

estadoIntro::~estadoIntro(){
    cout << "** estadoIntro::DESTRUCTOR" << endl;
}
