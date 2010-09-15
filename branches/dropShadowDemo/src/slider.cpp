#include "slider.h"
#include "log.h"

boost::shared_ptr<Gosu::Image> Slider::sliderBar;
boost::shared_ptr<Gosu::Image> Slider::sliderHandle;
bool Slider::imagesLoaded;

Slider::Slider(Gosu::Graphics & g, Gosu::Input & input, 
	       float minValue, float maxValue, int x, int y, int z) 
    : g(g), input(input), minValue(minValue), maxValue(maxValue), x(x), y(y), z(z){

    if(!imagesLoaded){
	imagesLoaded = true;
	sliderBar.reset(new Gosu::Image(g, L"media/sliderBar.png"));
	sliderHandle.reset(new Gosu::Image(g, L"media/sliderHandle.png"));
    }

    clicking = false;
    currentValue = minValue;

    trackWidth = sliderBar -> width() - sliderHandle -> width();    
    handleWidth = sliderHandle -> width();
    handleHeight = sliderHandle -> height();
    handleMargin = 0;
}

void Slider::update(){
    if(clicking){
	double mX = input.mouseX() - offsetFromX;
	float p;

	if(mX < x){
	    p = 0;
	}
	
	else if(mX > x + trackWidth){
	    p = 1;
	}

	else{
	    mX -= x;
//	    mX -= offsetFromX;
	    p = (float)mX / trackWidth;
	}
	float computedValue = minValue + (maxValue - minValue) * p;
	if(currentValue != computedValue){
	    if(onChange)
		onChange();
	    currentValue = computedValue;
	}
    }

    handleX = x + trackWidth * ((currentValue - minValue) / ( maxValue - minValue));

}

void Slider::buttonDown(Gosu::Button B){
    if(B == Gosu::msLeft){
	double mX = input.mouseX();
	double mY = input.mouseY();

	if((mX >= handleX ) && 
	   (mX <= handleX + handleWidth) &&
	   (mY >= y) &&
	   (mY <= y + handleHeight)){
	    clicking = true;
	    offsetFromX = mX - handleX;
	}
    }
}

void Slider::buttonUp(Gosu::Button B){
    if(B == Gosu::msLeft){
	clicking = false;
    }
}

void Slider::linX(int x1, int color){
    g.drawLine(x1, 0, color, 
	       x1, 600, color,
	       100);
}

void Slider::linY(int y1, int color){
    g.drawLine(0, y1, color,
	       800, y1, color,
	       100);
}

void Slider::draw(){
    sliderBar -> draw(x, y + handleHeight / 2 - 3, z);
    sliderHandle -> draw(handleX, y, z + 0.1);

    /*
    linX(handleX);
    linX(handleX + 26);

    linY(y + 7);
    linY(y + 33);

    linX(x, 0xff00ff00);
    linX(x + sliderBar->width(), 0xff00ff00);
    //*/
}

float Slider::get(){
    return currentValue;
}

void Slider::set(float p){
    if(p >= minValue && p <= maxValue)
	currentValue = p;
}
