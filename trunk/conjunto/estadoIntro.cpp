#include "estadoIntro.h"
#include "juego.h"

estadoIntro::estadoIntro (Juego * p, Gosu::Graphics * graphics) : 
    estadoImagenFija(p, graphics, 
		     Gosu::resourcePrefix() + L"media/estadoIntro.png"){
    cout << "* Se crea estado intro" << endl;
}

void estadoIntro::accionPosterior(){
    padre -> close();
}
