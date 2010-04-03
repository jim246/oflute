#include "Gosu/Gosu.hpp"
#include <iostream>

#include "botonMenu.h"


using namespace std;

class pruebaFuentes : public Gosu::Window{

    boost::scoped_ptr<BotonMenu> btn1, btn2, btn3;
public:

    pruebaFuentes() : Gosu::Window(800, 600, false){
	btn1.reset(new BotonMenu(graphics(), "Lecciones de flauta", Gosu::Color(3, 69, 90)));
	btn2.reset(new BotonMenu(graphics(), "Canciones", Gosu::Color(34, 139, 114)));
	btn3.reset(new BotonMenu(graphics(), "Isa peorra", Gosu::Color(34, 255, 114)));

	cout << ">>> pruebaFuentes::CONSTRUCTOR" << endl;

    }

    void update(){

    }
    
    void draw(){
	Gosu::Color c (255,255,255);

	// Pinta el fondo del color c
	graphics() . drawQuad(0,0,c,
			      800, 0, c,
			      800, 600, c,
			      0, 600, c, 
			      1);

	Gosu::Color d (255, 3, 69, 90);

	btn1 -> draw(0, 400, 2);
	btn2 -> draw(0, 451, 2);
	btn3 -> draw(0, 502, 2);

	/* Colores del menú
	   3, 69, 90
	   34, 139, 114
	   188, 216, 56,
	   245, 215, 19
	   241, 106, 0
	 */

    }

    void buttonDown(Gosu::Button boton){
	if(boton == Gosu::kbEscape){
	    close();
	}
    }

    ~pruebaFuentes(){
	cout << "<<< pruebaFuentes::DESTRUCTOR" << endl;
    }
};


int main(int argc, char *argv[])
{
    
    pruebaFuentes P;
    P.show();
    return 0;
}

