#include "Gosu/Gosu.hpp"

#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <string>

using namespace std;

class MyClass{
    Gosu::Graphics & g;

public:
    MyClass(Gosu::Graphics & g) : g(g){ }

    void draw(){
	Gosu::Image * myImage = new Gosu::Image(g, L"media/estadoAutor.png");
	myImage -> draw(0,0,1);
    }

};

class MyWindow : public Gosu::Window{
    boost::scoped_ptr<MyClass> M;
public:

    MyWindow() : Gosu::Window(640, 480, false){
	M . reset(new MyClass(graphics()));
    }

    void update(){

    }
    
    void draw(){
	M -> draw();
	M -> draw();
    }

    void buttonDown(Gosu::Button boton){
	if(boton == Gosu::kbEscape){
	    close();
	}
    }

    ~MyWindow(){
	cout << "<<< MyWindow::DESTRUCTOR" << endl;
    }
};


int main(int argc, char *argv[])
{
    
    MyWindow P;
    P.show();
    return 0;
}

