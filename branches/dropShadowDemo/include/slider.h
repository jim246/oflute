/**
 * @file slider.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef _SLIDER_H_
#define _SLIDER_H_

#include <Gosu/Gosu.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

class Slider{
public:
    Slider(Gosu::Graphics & g, Gosu::Input & input, 
	   float minValue, float maxValue, int x, int y, int z);

    void update();
    void buttonDown(Gosu::Button B);
    void buttonUp(Gosu::Button B);

    void draw();
    boost::function<void ()> onChange;

    float get();
    void set(float p);
private:
    static boost::shared_ptr<Gosu::Image> sliderBar;
    static boost::shared_ptr<Gosu::Image> sliderHandle;
    static bool imagesLoaded;

    Gosu::Graphics & g;
    Gosu::Input & input;

    float minValue;
    float currentValue;
    float maxValue;

    int x;
    int y;
    int z;

    int handleX;  

    int offsetFromX;
    int trackWidth;
    int handleWidth, handleHeight;
    int handleMargin;

    bool clicking;

    void linX(int x1, int color = 0xffff0000);
    void linY(int y1, int color = 0xffff0000);
};

#endif /* _SLIDER_H_ */
