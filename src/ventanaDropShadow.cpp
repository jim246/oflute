#include "ventanaDropShadow.h"
#include "log.h"
#include "dropShadow.h"

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
using std::string;

VentanaDropShadow::VentanaDropShadow() : Gosu::Window(800, 400, false){
    setCaption(L"Drop Shadow Test");
    slider1.reset(new Slider(graphics(), input(), 1, 50, 450, 110, 1));
    slider2.reset(new Slider(graphics(), input(), 0.01, 1, 450, 180, 1));
    slider3.reset(new Slider(graphics(), input(), 1, 100, 450, 250, 1));
    slider4.reset(new Slider(graphics(), input(), 0, 360, 450, 320, 1));

    slider1 -> onChange = boost::bind(&VentanaDropShadow::redrawShadow, this);
    slider2 -> onChange = boost::bind(&VentanaDropShadow::redrawShadow, this);
    slider3 -> onChange = boost::bind(&VentanaDropShadow::redrawShadow, this);
    slider4 -> onChange = boost::bind(&VentanaDropShadow::redrawShadow, this);

    imgOriginal.reset(new Gosu::Image(graphics(), L"media/image1.png"));
    fontBold.reset (new Gosu::Font(graphics(), Gosu::defaultFontName(), 40, 1));
    fontNormal.reset (new Gosu::Font(graphics(), Gosu::defaultFontName(), 30, 0));

    currentSize = 5;
    currentOpacity = 0.5;
    currentDistance = 5;
    currentAngle = 138;

    slider1 -> set(currentSize);
    slider2 -> set(currentOpacity);
    slider3 -> set(currentDistance);
    slider4 -> set(currentAngle);

    redrawShadow();
}

void VentanaDropShadow::update(){
    slider1 -> update();
    slider2 -> update();
    slider3 -> update();
    slider4 -> update();
}

void VentanaDropShadow::draw(){
    graphics().drawQuad(0, 0, 0xffffffff,
			800, 0, 0xffffffff,
			800, 400, 0xffffffff,
			0, 400, 0xffffffff,
			0);

    slider1 -> draw();
    slider2 -> draw();
    slider3 -> draw();
    slider4 -> draw();

    imgOriginal -> draw(50, 45, 2);
    imgShadow -> draw(50 - currentSize + Gosu::offsetX(currentAngle, currentDistance), 
		      45 - currentSize + Gosu::offsetY(currentAngle, currentDistance), 1);

    fontBold -> draw(L"Drop Shadow Test", 400, 30, 1, 1, 1, 0xff000000);
    fontNormal -> draw(L"Size: ", 420, 80, 1, 1, 1, 0xff000000);
    fontNormal -> draw(L"Opacity: ", 420, 150, 1, 1, 1, 0xff000000);
    fontNormal -> draw(L"Distance: ", 420, 220, 1, 1, 1, 0xff000000);
    fontNormal -> draw(L"Angle: ", 420, 290, 1, 1, 1, 0xff000000);

    fontNormal -> draw(Gosu::utf8ToWstring(boost::lexical_cast<string>(currentSize)),
		       720, 110, 1, 1, 1, 0xff000000);

    fontNormal -> draw(Gosu::utf8ToWstring(boost::lexical_cast<string>(currentOpacity)),
		       720, 180, 1, 1, 1, 0xff000000);

    fontNormal -> draw(Gosu::utf8ToWstring(boost::lexical_cast<string>(currentDistance)),
		       720, 250, 1, 1, 1, 0xff000000);

    fontNormal -> draw(Gosu::utf8ToWstring(boost::lexical_cast<string>(currentAngle)),
		       720, 320, 1, 1, 1, 0xff000000);
}

void VentanaDropShadow::buttonDown(Gosu::Button B){
    slider1 -> buttonDown(B);
    slider2 -> buttonDown(B);
    slider3 -> buttonDown(B);
    slider4 -> buttonDown(B);

    if(B == Gosu::kbEscape){
	close();
    }
}

void VentanaDropShadow::buttonUp(Gosu::Button B){
    slider1 -> buttonUp(B);
    slider2 -> buttonUp(B);
    slider3 -> buttonUp(B);
    slider4 -> buttonUp(B);

}

bool VentanaDropShadow::needsCursor() const{
    return true;
}

void VentanaDropShadow::redrawShadow(){
    currentSize = slider1 -> get();
    currentOpacity = slider2 -> get();
    currentDistance = slider3 -> get();
    currentAngle = slider4 -> get();
    imgShadow.reset(new Gosu::Image(graphics(), 
				    applyShadow(*imgOriginal, currentSize, currentOpacity)));
}
