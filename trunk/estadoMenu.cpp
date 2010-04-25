#include "estadoMenu.h"
#include "juego.h"

#include <cmath>

int posFinalesY[] = {281, 332, 383, 434, 485 };

EstadoMenu::EstadoMenu (Juego * p) : Estado(p){
    cout << "+++ [Constructor] EstadoMenu" << endl;
    p -> setCaption(L"oFlute .:. Menú principal");
    
}

void EstadoMenu::lanzar(){
    cout << "* EstadoMenu lanzado" << endl;
    lanzado = true;
    estadoAnim = 0;
 
    // Poblamos el puntero de las imágenes
    imgFondo.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/menuAssets/menuBase.png"));

    logoCusl.reset(new Gosu::Image(padre -> graphics(),
				   Gosu::resourcePrefix() + L"media/logo-cusl4.png"));

    int pInit = 290;
    for (int i = 0; i < 5; ++i)
    {
	posFinalesY[i] = pInit + i*51;
    }

    btnUca.reset(new Gosu::Image(padre -> graphics(), 
				 Gosu::resourcePrefix() + L"media/menuAssets/btnUca.png"));//*/

    btn1.reset(new BotonMenu(padre -> graphics(), "Analizador de notas", Gosu::Color(255,3,69,90)));
    btn2.reset(new BotonMenu(padre -> graphics(), "Canciones(Inactivo)", Gosu::Color(255,34,139,114)));
    btn3.reset(new BotonMenu(padre -> graphics(), "Opciones (Inactivo)", Gosu::Color(255,188,216,56)));
    btn4.reset(new BotonMenu(padre -> graphics(), "Salir", Gosu::Color(255,245,215,19)));




    animOpacidadFondo.reset(new Animacion(0,0,255,0, 30, Animacion::tEaseOutQuad));

    animaciones[0].reset(new Animacion(0, 600, 0, posFinalesY[0], 30, Animacion::tEaseOutQuart, 0));
    animaciones[1].reset(new Animacion(0, 600, 0, posFinalesY[1], 30, Animacion::tEaseOutQuart, 10)); 
    animaciones[2].reset(new Animacion(0, 600, 0, posFinalesY[2], 30, Animacion::tEaseOutQuart, 20)); 
    animaciones[3].reset(new Animacion(0, 600, 0, posFinalesY[3], 30, Animacion::tEaseOutQuart, 30)); 
    animaciones[4].reset(new Animacion(0, 600, 0, posFinalesY[4], 30, Animacion::tEaseOutQuart, 40)); 


    animLogoCusl.reset(new Animacion(820, 10, 590, 10, 30, Animacion::tEaseOutBack, 40));

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
    if(estadoAnim == 0){
	animOpacidadFondo -> update();

	if(animOpacidadFondo -> getX() == 255){
	    estadoAnim = 1;
	}
    }

    // 1: Sacando botones
    else if(estadoAnim == 1){
	int j = 0;
	for (int i = 0; i < 5; ++i)
	{
	    animaciones[i] -> update();
	    if(animaciones[i] -> getY() == posFinalesY[i]) ++j;
	}

	if(j == 5){
	    cout << "** Los botones llegaron a su lugar" << endl;
	    estadoAnim = 2;
	}
    }
    
    else if(estadoAnim == 2){
	// Los botones están en su sitio, parados
	
    }

    // 2: Guardamos los botones
    
    else if(estadoAnim == 3){
	for (int i = 4; i > -1; --i)
	{
	    animaciones[i] -> setInicialY( animaciones[i] -> getY() );
	    animaciones[i] -> setFinalY(600);
	    animaciones[i] -> setTipoAnimacion(Animacion::tEaseInQuart);
	    animaciones[i] -> setDuracion(20);
	    
	    animaciones[i] -> setEspera ((4-i) * 10);
	    animaciones[i] -> init();
	}

	estadoAnim = 4;
    }

    else if(estadoAnim == 4){
	
	int j = 0;
	for (int i = 0; i < 5; ++i)
	{
	    animaciones[i] -> update();
	    if(animaciones[i] -> getY() == 600){
		++j;
	    }
	}

	if(j == 5){
	    estadoAnim = 5;
	    cout << "** Los botones se escondieron." << endl;
	}
	
	
    }

    else if(estadoAnim == 5){
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
    btnUca -> draw(0, animaciones[4] -> getY(), 6); //*/

    animLogoCusl -> update();

    logoCusl -> draw(animLogoCusl -> getX(), animLogoCusl -> getY(), 4);

}

void EstadoMenu::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;


    if(boton == Gosu::kbEscape){
	estadoDestino = "salir";
	estadoAnim = 3;
    } //*/
    
    if(boton == Gosu::msLeft){
	int x = padre -> input().mouseX();
	int y = padre -> input().mouseY();
	
	if(btn1 -> clicked(x,y)){
	    estadoDestino = "estadoAnalizador";
	    estadoAnim = 3;
	}

	else if(btn2 -> clicked(x,y)){

	}

	else if(btn3 -> clicked(x,y)){

	}

	else if(btn4 -> clicked(x,y)){
	    estadoDestino = "salir";
	    estadoAnim = 3;
	}

	
	cout << "*** LMB @ (" << x << "," << y << ")" << endl;
    }
    else{
	cout << "KABOOM" << endl;
    }
}

EstadoMenu::~EstadoMenu(){
    cout << "--- [DESTRUCTOR] EstadoMenu" << endl << endl;
}//*/
