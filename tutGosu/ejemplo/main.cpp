#include <iostream>
#include "Gosu/Gosu.hpp"

using namespace std;

class Juego : public Gosu::Window{

public:

    Juego() : Gosu::Window(640, 480, false){
	cout << "Constructor" << endl;
    }

    void update(){
	// Aquí va la lógica del juego
    }

    void draw(){
	// Dibujado
    }

    void buttonDown(Gosu::Button boton){
	if(boton == Gosu::kbEscape){
	    close();
	}
    }
};

int main(int argc, char *argv[])
{
    Juego J;
    J.show();

    return 0;
}
