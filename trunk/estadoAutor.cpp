#include "estadoAutor.h"
#include "juego.h"
#include "colores.h"

estadoAutor::estadoAutor (Juego * p) : 
    estadoImagenFija(p,
		     Gosu::resourcePrefix() + L"media/estadoAutor.png"){
    cout << Colores::Verde + "** estadoAutor::CONSTRUCTOR" + Colores::Reset << endl;
}

void estadoAutor::accionPosterior(){
    padre -> cambiarEstado("estadoIntro");
}

estadoAutor::~estadoAutor(){
    cout << Colores::Rojo  + "** estadoAutor::DESTRUCTOR" + Colores::Reset << endl;
}
