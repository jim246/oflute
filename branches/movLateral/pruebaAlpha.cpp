#include <Gosu/Gosu.hpp>

#include <iostream>
#include <ctime>
#include <vector>
#include <cassert>
#include <queue>

#include <boost/scoped_ptr.hpp>

#include "cancion.h"



using namespace std;

class MiVentana : public Gosu::Window
{
    Gosu::Image fondo;
    int alphaDir, alphaVal, alphaStep, stepHor, stepVer;
    unsigned int imX, imY;

    unsigned long tiempo_inicial, tiempo_transcurrido, tiempo_prep, tiempo_acumulado;
    vector<Nota*> Notas;
    boost::scoped_ptr<Cancion> nuevaCancion;

public:

    MiVentana()
	: Window(800, 600, false, FPS),
	  fondo(graphics(), L"fondo1.png"),
	  alphaDir(0), alphaVal(0), alphaStep(5), stepHor(10), stepVer(10),
	  imX(0),imY(0)
	{
	    cout << "* Constructor" << endl;
	    nuevaCancion.reset(new Cancion(&graphics()));

		
	}
	
    ~MiVentana(){
	std::cout << "* Destructor" << std::endl;
    }
	
    void update(){
	tiempo_transcurrido = Gosu::milliseconds();
	nuevaCancion -> update();
    }

    void draw(){
	fondo.draw(0,0,0);
	nuevaCancion -> draw();
    }

    void buttonDown(Gosu::Button btn)
	{
	    if (btn == Gosu::kbEscape)
		close();
	}
};

int main(int argc, char* argv[])
{
    MiVentana ventana;
    ventana.show();

}
