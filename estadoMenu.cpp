#include "estadoMenu.h"
#include "juego.h"

#include <cmath>

int posFinalesY[] = {281, 333, 386, 441, 494 };
EstadoMenu::EstadoMenu (Juego * p) : Estado(p){
    cout << "** EstadoMenu::CONSTRUCTOR" << endl;
}

void EstadoMenu::lanzar(){
    cout << "* EstadoMenu lanzado" << endl;
    lanzado = true;
    estadoAnim = 0;
    alphaActual = 0;

    // Poblamos el puntero de las imágenes
    imgFondo.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/menuAssets/menuBase.png"));
    btn1.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/menuAssets/btn1.png"));
    btn2.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/menuAssets/btn2.png"));
    btn3.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/menuAssets/btn3.png"));
    btn4.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/menuAssets/btn4.png"));
    btnUca.reset(new Gosu::Image(padre -> graphics(), 
				   Gosu::resourcePrefix() + L"media/menuAssets/btnUca.png"));


    std::wstring resPref = Gosu::resourcePrefix();
    
    miFuente.reset(new customFont(padre -> graphics(),
				  Gosu::resourcePrefix() + L"media/fuente1.ttf",
				  27));

    anim.reset(new Animacion(0, 600, 0, 281, 20, Animacion::tEaseOutQuart));
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


    short step = 10;

    // 0: Haciendo el fade in
    if(estadoAnim == 0){
	alphaActual += step;

	if(alphaActual > 255){
	    alphaActual = 255;
	    estadoAnim = 1;
	}
    }

    // 1: Sacando btn1
    else if(estadoAnim > 0 && estadoAnim < 6){
	anim -> update();
	posY[0] = anim -> getY();
/*	for (int i = 0; i < 5; ++i)
	{
	    posY[i] += (posFinalesY[i] - posY[i]) / 10;
//	    cout << posY[i] << endl;
	    
	    if(abs(posFinalesY[i] - (posY[i])) < 0.01){
		posY[i] = posFinalesY[i];
		estadoAnim++;
		cout << "Cambiando a estado: " << estadoAnim << endl;
	    }
	}//*/
    }
}

void EstadoMenu::draw(){
    if(!lanzado) 
	return;

    imgFondo -> draw(0,0,1,1,1,Gosu::Color(alphaActual,255,255,255));
    
    btn1 -> draw(0, posY[0], 2); 
    btn2 -> draw(0, posY[1], 3);
    btn3 -> draw(0, posY[2], 4);
    btn4 -> draw(0, posY[3], 5);
    btnUca -> draw(0, posY[4], 6); //*/

    //  miFuente -> setHinting(0);
    miFuente -> draw("Pulse escape para continuar hacia el analizador", 10, 10, 7,
		     Gosu::Color(255,0,0,0));
/*
    miFuente -> setHinting(1);
    miFuente -> draw("Pulse escape para continuar hacia el analizador", 10, 330, 7,
		     Gosu::Color(255,255,255,255));

    miFuente -> setHinting(2);
    miFuente -> draw("Pulse escape para continuar hacia el analizador", 10, 360, 7,
		     Gosu::Color(255,255,255,255));

    miFuente -> setHinting(3);
    miFuente -> draw("Pulse escape para continuar hacia el analizador", 10, 390, 7,
		     Gosu::Color(255,255,255,255));
//*/    
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
    else{
	cout << "KABOOM" << endl;
    }
}

EstadoMenu::~EstadoMenu(){
    cout << "EstadoMenu::DESTRUCTOR" << endl << endl;
}
