#include "estadoIntro.h"
#include "juego.h"

EstadoIntro::EstadoIntro (Juego * p) : 
    EstadoImagenFija(p,
		     Gosu::resourcePrefix() + L"media/estadoIntro.png"){
    cout << "** EstadoIntro::CONSTRUCTOR" << endl;
}

void EstadoIntro::accionPosterior(){
    padre -> cambiarEstado ("estadoMenu");
}

EstadoIntro::~EstadoIntro(){
    cout << "** EstadoIntro::DESTRUCTOR" << endl;
}
