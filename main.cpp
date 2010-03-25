#include "Gosu/Gosu.hpp"
#include <iostream>

#include <boost/scoped_ptr.hpp>


#include "particulas.h"


class pruebaParticle : public Gosu::Window{
    boost::scoped_ptr<SistemaParticulas> SP;
public:
    pruebaParticle() : Gosu::Window(640, 480, false){
	cout << "+++ pruebaParticle::CONSTRUCTOR" << endl;
	SP . reset(new SistemaParticulas(graphics(), 150, 120, 300, Gosu::Color(255,125,125)));
    }

    void update(){

    }
    
    void draw(){
	Gosu::Color c (255,255,255);

/*
	graphics() . drawQuad(0,0,c,
			      640, 0, c,
			      640, 480, c,
			      0, 480, c, 
			      1); //*/

	SP -> draw(320, 240);
    }

    void buttonDown(Gosu::Button boton){
	if(boton == Gosu::kbEscape){
	    close();
	}else{
	    SP -> inicializar();
	}
    }

    ~pruebaParticle(){
	cout << "--- pruebaParticle::DESTRUCTOR" << endl;
    }
};


int main(int argc, char *argv[])
{
    
    pruebaParticle P;
    P.show();
    return 0;
}

