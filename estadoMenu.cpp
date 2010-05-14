#include "estadoMenu.h"
#include "juego.h"
#include "log.h"

#include <cmath>

int posFinalesY[] = {281, 332, 383, 434, 485, 589 };

EstadoMenu::EstadoMenu (Juego * p) : Estado(p){
    lDEBUG << Log::CON("EstadoMenu");
    p -> setCaption(L"oFlute .:. Menú principal");

}

void EstadoMenu::lanzar(){
    lDEBUG << "* EstadoMenu lanzado" ;
    lanzado = true;
    estadoAnim = eFADEIN;
 
    // Poblamos el puntero de las imágenes
    imgFondo.reset(new Gosu::Image(padre -> graphics(), L"media/fondoGenerico.png"));

    logoCusl.reset(new Gosu::Image(padre -> graphics(), L"media/logo-cusl4.png"));

    logotipo.reset(new Gosu::Image(padre -> graphics(), L"media/menuAssets/logoMenu.png"));

    barraRoja.reset(new Gosu::Image(padre -> graphics(), L"media/menuAssets/barraInferior.png"));

    
    // Inicializamos las animaciones
    int pInit = 290;
    for (int i = 0; i < 6; ++i)
    {
	posFinalesY[i] = pInit + i*51;
	if(i == 5) posFinalesY[i] = 589;
	animaciones[i].reset(new Animacion(0, 600, 0, posFinalesY[i], 30,
					   Animacion::tEaseOutQuart,
					   i * 10));
    }

    animOpacidadFondo.reset(new Animacion(0,0,255,0, 30, Animacion::tEaseOutQuad));
    animLogoCusl.reset(new Animacion(820, 10, 590, 10, 30, Animacion::tEaseOutBack, 40));
    animLogotipo.reset(new Animacion(0, 0, 255, 0, 30, Animacion::tEaseOutQuart,10));

    // Inicializamos los botones del menú
    btnUca.reset(new Gosu::Image(padre -> graphics(), L"media/menuAssets/btnUca.png"));//*/
    btn1.reset(new BotonMenu(padre -> graphics(), "Analizador de notas", Gosu::Color(255,3,69,90)));
    btn2.reset(new BotonMenu(padre -> graphics(), "Canciones(Inactivo)", Gosu::Color(255,34,139,114)));
    btn3.reset(new BotonMenu(padre -> graphics(), "Lecciones", Gosu::Color(255,188,216,56)));
    btn4.reset(new BotonMenu(padre -> graphics(), "Salir", Gosu::Color(255,245,215,19)));
}

void EstadoMenu::update(){
    if(!lanzado) 
	return;

/*
  Estados de la animación:
  0: Haciendo fade in del fondo
  1: Salen los botones
*/


    // 0: Haciendo el fade in
    if(estadoAnim == eFADEIN){
	animOpacidadFondo -> update();

	if(animOpacidadFondo -> getX() == 255){
	    estadoAnim = eBOTONESIN;
	}
    }

    // 1: Sacando botones
    else if(estadoAnim == eBOTONESIN){
	int j = 0;
	for (int i = 0; i < 6; ++i)
	{
	    animaciones[i] -> update();
	    if(animaciones[i] -> getY() == posFinalesY[i]) ++j;
	}

	if(j == 5){
	    lDEBUG << "** Los botones llegaron a su lugar" ;
	    estadoAnim = eESTATICO;
	}
    }
    
    else if(estadoAnim == eESTATICO){
	// Los botones están en su sitio, parados
	
    }

    // 3: Inicialización del guardado de los botones, se reinician las animaciones
    
    else if(estadoAnim == eBOTONESOUT){
	for (int i = 5; i > -1; --i)
	{
	    animaciones[i] -> setInicialY( animaciones[i] -> getY() );
	    animaciones[i] -> setFinalY(600);
	    animaciones[i] -> setTipoAnimacion(Animacion::tEaseInQuart);
	    animaciones[i] -> setDuracion(20);
	    
	    animaciones[i] -> setEspera ((5-i) * 10);
	    animaciones[i] -> init();
	}

	animLogoCusl -> setInicialX( animLogoCusl -> getX() );
	animLogoCusl -> setFinalX(820);
	animLogoCusl -> setTipoAnimacion(Animacion::tEaseInQuart);
	animLogoCusl -> setDuracion(15);
	animLogoCusl -> setEspera(0);
	animLogoCusl -> init();

	animLogotipo.reset(new Animacion(255,0,0,0, 30, Animacion::tLinear, 10) );

	estadoAnim = eANIMOUT;
    }

    else if(estadoAnim == eANIMOUT){
	
	int j = 0;
	for (int i = 0; i < 6; ++i)
	{
	    animaciones[i] -> update();
	}

	if(animaciones[0] -> finished() &&
	   animaciones[1] -> finished() &&
	   animaciones[2] -> finished() &&
	   animaciones[3] -> finished() &&
	   animaciones[4] -> finished() &&
	   animaciones[5] -> finished() &&
	   animLogoCusl -> finished() &&
	   animLogotipo -> finished() ){
	    estadoAnim = eANIMEND;
	    lDEBUG << "** Los botones se escondieron." ;
	}
	
	
    }

    else if(estadoAnim == eANIMEND){
	padre -> cambiarEstado(estadoDestino);
    }
}

void EstadoMenu::draw(){
    if(!lanzado) 
	return;

    imgFondo -> draw(0,0,1, 1,1, Gosu::Color(animOpacidadFondo -> getX(), 255, 255, 255));

    btn1 -> draw(0, animaciones[0] -> getY(), 2); 
    btn2 -> draw(0, animaciones[1] -> getY(), 3);
    btn3 -> draw(0, animaciones[2] -> getY(), 4);
    btn4 -> draw(0, animaciones[3] -> getY(), 5);
    btnUca -> draw(0, animaciones[4] -> getY(), 6);
    barraRoja -> draw(0, animaciones[5] -> getY(), 7);

    animLogoCusl -> update();
    animLogotipo -> update();

    logoCusl -> draw(animLogoCusl -> getX(), animLogoCusl -> getY(), 4);
    logotipo -> draw(330, 35, 30, 1,1, Gosu::Color(animLogotipo -> getX(), 255, 255, 255));

}

void EstadoMenu::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;


    if(boton == Gosu::kbEscape){
	lDEBUG << "Escape pulsado " << VARV(estadoAnim);
	if(estadoAnim < eESTATICO){
	    for (int i = 0; i < 6; ++i)
	    {
		animaciones[i] -> end();
	    }
	    animLogoCusl -> end();
	    animLogotipo -> end();
	    estadoAnim = eESTATICO;
	}

	else if(estadoAnim < eBOTONESOUT){
	    estadoDestino = "salir";
	    estadoAnim = eBOTONESOUT;
	} //*/

	else if(estadoAnim < eANIMEND){
	    estadoAnim = eANIMEND;
	    for (int i = 0; i < 6; ++i)
	    {
		animaciones[i] -> end();
	    }
	    animLogoCusl -> end();
	    animLogotipo -> end();
	}
    }

    if(boton == Gosu::msLeft){
	int x = padre -> input().mouseX();
	int y = padre -> input().mouseY();
	
	if(btn1 -> clicked(x,y)){
	    estadoDestino = "estadoAnalizador";
	    estadoAnim = eBOTONESOUT;
	}

	else if(btn2 -> clicked(x,y)){

	}

	else if(btn3 -> clicked(x,y)){
	    estadoDestino = "estadoLecciones";
	    estadoAnim = eBOTONESOUT;
	}

	else if(btn4 -> clicked(x,y)){
	    estadoDestino = "salir";
	    estadoAnim = eBOTONESOUT;
	}

	
	lDEBUG << "*** LMB @ (" << x << "," << y << ")" ;
    }
}

EstadoMenu::~EstadoMenu(){
    lDEBUG << Log::DES("EstadoMenu");
}//*/
