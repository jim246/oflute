#include "estadoAutor.h"
#include "juego.h"
#include "colores.h"

EstadoAutor::EstadoAutor (Juego * p) : 
    EstadoImagenFija(p,
		     Gosu::resourcePrefix() + L"media/estadoAutor.png"){
    cout << Colores::Verde + "** EstadoAutor::CONSTRUCTOR" + Colores::Reset << endl;
}

void EstadoAutor::accionPosterior(){
    padre -> cambiarEstado("estadoIntro");
}

EstadoAutor::~EstadoAutor(){
    cout << Colores::Rojo  + "** EstadoAutor::DESTRUCTOR" + Colores::Reset << endl;
}
