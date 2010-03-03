#include "estadoIntro.h"
#include "juego.h"

estadoIntro::estadoIntro (Juego * p) : 
    estadoImagenFija(p,
		     Gosu::resourcePrefix() + L"media/estadoIntro.png"){
    cout << "* Se crea estado intro" << endl;
}

void estadoIntro::accionPosterior(){
    padre -> cambiarEstado ("estadoMenu");
}
