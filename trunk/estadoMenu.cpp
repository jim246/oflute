#include "estadoMenu.h"
#include "juego.h"

#include <cmath>

int posFinalesY[] = {281, 332, 383, 434, 485 };
EstadoMenu::EstadoMenu (Juego * p) : Estado(p){
    cout << "+++ [CONSTRUCTOR] EstadoMenu" << endl;
    p -> setCaption(L"oFlute .:. Menú principal");
}

void EstadoMenu::lanzar(){
    cout << "* EstadoMenu lanzado" << endl;
    lanzado = true;
    estadoAnim = 0;
    alphaActual = 0;

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

    btn1.reset(new BotonMenu(padre -> graphics(), "Analizador de notas (pulse Escape para acceder)", Gosu::Color(255,3,69,90)));
    btn2.reset(new BotonMenu(padre -> graphics(), "Canciones (Inactivo)", Gosu::Color(255,34,139,114)));
    btn3.reset(new BotonMenu(padre -> graphics(), "Opciones (Inactivo)", Gosu::Color(255,188,216,56)));
    btn4.reset(new BotonMenu(padre -> graphics(), "Salir", Gosu::Color(255,245,215,19)));



    anim1.reset(new Animacion(0, 600, // X inicial, Y inicial
			     0, posFinalesY[0], // X final, Y final
			     30, Animacion::tEaseOutQuart)); // duración, tipo


    anim2.reset(new Animacion(0, 600, 0, posFinalesY[1], 30, Animacion::tEaseOutQuart, 10)); 
    anim3.reset(new Animacion(0, 600, 0, posFinalesY[2], 30, Animacion::tEaseOutQuart, 20)); 
    anim4.reset(new Animacion(0, 600, 0, posFinalesY[3], 30, Animacion::tEaseOutQuart, 30)); 
    anim5.reset(new Animacion(0, 600, 0, posFinalesY[4], 30, Animacion::tEaseOutQuart, 40)); 


    animLogoCusl.reset(new Animacion(820, 10, 590, 10, 30, Animacion::tEaseOutBack, 40));

    // Inicialmente todos los botones se encuentran bajo el borde inferior de la pantalla
    for (int i = 0; i < 5; ++i)
    {
	posY [i] = 600;
    }
    
}

void EstadoMenu::update(){
    if(!lanzado) 
	return;

/*
  Estados de la animación:
  0: Haciendo fade in del fondo
  1: Subiendo btn1
  2: Subiendo btn2
  3: Subiendo btn3
  4: Subiendo btn4
  5: Subiendo btnUca
  6: A la espera del usuario
*/


    short step = 5;

    // 0: Haciendo el fade in
    if(estadoAnim == 0){
	alphaActual += step;

	if(alphaActual > 255){
	    alphaActual = 255;
	    estadoAnim = 1;
	}

//	cout << alphaActual << endl;
    }

    // 1: Sacando btn1
    else if(estadoAnim > 0 && estadoAnim < 6){
	anim1 -> update();
	anim2 -> update();
	anim3 -> update();
	anim4 -> update();
	anim5 -> update();

	posY[0] = anim1 -> getY();
	posY[1] = anim2 -> getY();
	posY[2] = anim3 -> getY();
	posY[3] = anim4 -> getY();
	posY[4] = anim5 -> getY();

    }
}

void EstadoMenu::draw(){
    if(!lanzado) 
	return;

    imgFondo -> draw(0,0,1, 1,1, Gosu::Color(alphaActual, 255, 255, 255));

    btn1 -> draw(0, posY[0], 2); 
    btn2 -> draw(0, posY[1], 3);
    btn3 -> draw(0, posY[2], 4);
    btn4 -> draw(0, posY[3], 5);
    btnUca -> draw(0, posY[4], 6); //*/

    animLogoCusl -> update();

    logoCusl -> draw(animLogoCusl -> getX(), animLogoCusl -> getY(), 4);

}

void EstadoMenu::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    if (boton == Gosu::kbReturn){
	padre -> close();
    }
    else if(boton == Gosu::kbEscape){
	padre -> cambiarEstado("estadoAnalizador");
    }
    else if(boton == Gosu::msLeft){
	int x = padre -> input().mouseX();
	int y = padre -> input().mouseY();
	cout << "*** LMB @ (" << x << "," << y << ")" << endl;
    }
    else{
	cout << "KABOOM" << endl;
    }
}

EstadoMenu::~EstadoMenu(){
    cout << "--- [DESTRUCTOR] EstadoMenu" << endl << endl;
}//*/
