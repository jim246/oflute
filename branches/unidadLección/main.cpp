#include "Gosu/Gosu.hpp"
#include <iostream>
#include <string>


#include "texto.h"

#include "leccion.h"


using namespace std;

class pruebaFuentes : public Gosu::Window{
    
public:
//    boost::scoped_ptr<Texto> myFont, f2, f3;

    boost::scoped_ptr<Leccion> L;
    pruebaFuentes() : Gosu::Window(640, 480, false)
		      /*,
		      myFont(new Texto(graphics(), "El perro de san roque\nno tiene rabo", 
				       40, Gosu::Color::WHITE, 
				       1, true, 80, 20, 50)),
		      f2(new Texto(graphics(), "El perro de san roque\nno tiene rabo", 
				   40, Gosu::Color::WHITE, 
				   2, true,80, 320, 200)),
		      f3(new Texto(graphics(), "El perro de san roque\nno tiene rabo", 
				   40, Gosu::Color::WHITE, 
				   3, true,80,620,350))
		      */
	{

	cout << ">>> pruebaFuentes::CONSTRUCTOR" << endl;
	L.reset(new Leccion(graphics(), "lec1.xml"));
    }

    void update(){

    }
    
    void draw(){

	Gosu::Color c (128,128,128);
	graphics() . drawQuad(0,0,c,
			      640, 0, c,
			      640, 480, c,
			      0, 480, c, 
			      1); //*/

	L -> draw();
	/*
	myFont -> draw(1);
	f2 -> draw(1);
	f3 -> draw(1); //*/
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

