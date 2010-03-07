#include "Gosu/Gosu.hpp"
#include <iostream>

#include "customFont.h"

using namespace std;

class pruebaFuentes : public Gosu::Window{
    
public:
    boost::scoped_ptr<customFont> myFont;

    pruebaFuentes() : Gosu::Window(640, 480, false),
		      myFont(new customFont(graphics(), "consola.ttf", 30)){
	cout << "* pruebaFuentes::CONSTRUCTOR" << endl;

    }

    void update(){

    }
    
    void draw(){
	Gosu::Color c (128,128,128);
	graphics() . drawQuad(0,0,c,
			      640, 0, c,
			      640, 480, c,
			      0, 480, c, 
			      1);

	myFont -> draw("I'm the beññst", 30, 30, 2);
    }

    void buttonDown(Gosu::Button boton){
	if(boton == Gosu::kbEscape){
	    close();
	}
    }
};


int main(int argc, char *argv[])
{
    
    pruebaFuentes P;
    P.show();
    return 0;
}

