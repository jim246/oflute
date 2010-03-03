#include "estadoAutor.h"
#include "juego.h"

estadoAutor::estadoAutor (Juego * p, Gosu::Graphics * graphics) : 
    estadoImagenFija(p, graphics, 
		     Gosu::resourcePrefix() + L"media/estadoAutor.png"){
    cout << "* Se crea estado autor" << endl;
}

void estadoAutor::accionPosterior(){
    padre -> cambiarEstado("estadoIntro");
}
