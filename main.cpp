#include "Gosu/Gosu.hpp"
#include <iostream>

using namespace std;

#include <boost/scoped_ptr.hpp>


class pruebaParticle : public Gosu::Window{
    boost::scoped_ptr<Gosu::Image> imagen;
public:
    pruebaParticle() : Gosu::Window(800, 600, false){
	cout << "+++ pruebaParticle::CONSTRUCTOR" << endl;
//	imagen.reset(new Gosu::Image(graphics(), L"do5.png"));
	Gosu::Bitmap B = Gosu::quickLoadBitmap(L"do5.png");

	unsigned w_ = B.width();
	unsigned h_ = B.height();
	for (int i = 0; i < w_; ++i)
	{
	    for (int j = 0; j < h_; ++j)
	    {
		Gosu::Color c = B.getPixel(i,j);
		c.setSaturation(0);
		B.setPixel(i,j,c);
	    }
	}
	imagen.reset(new Gosu::Image(graphics(), B);)
    }

    void update(){

    }
    
    void draw(){
	Gosu::Color c (255,255,255);

	imagen -> draw(0,0,1);
    }

    void buttonDown(Gosu::Button boton){
	if(boton == Gosu::kbEscape){
	    close();
	}
    }

    ~pruebaParticle(){
	cout << "--- pruebaParticle::DESTRUCTOR" << endl;
    }
};


int main(int argc, char *argv[])
{
    std::cout << "\n########### PULSE CUALQUIER TECLA PARA QUE APAREZCAN LOS FUEGOS ARTIFICIALES ######\n" << std::endl;	    
    pruebaParticle P;
    P.show();
    return 0;
}

