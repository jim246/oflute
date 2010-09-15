/**
 * @file ventanaDropShadow.h
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
#ifndef _VENTANADROPSHADOW_H_
#define _VENTANADROPSHADOW_H_

#include <Gosu/Gosu.hpp>
#include <boost/scoped_ptr.hpp>
#include "slider.h"



class VentanaDropShadow : public Gosu::Window{
public:
    VentanaDropShadow();
    void update();
    void draw();
    void buttonDown(Gosu::Button B);
    void buttonUp(Gosu::Button B);

    bool needsCursor() const;
    void redrawShadow();
private:
    boost::scoped_ptr<Slider> slider1, slider2, slider3, slider4;

    boost::scoped_ptr<Gosu::Image> imgOriginal, imgShadow;
    boost::scoped_ptr<Gosu::Font> fontBold, fontNormal;

    float currentSize, currentOpacity, currentDistance, currentAngle;
};

#endif /* _VENTANA_H_ */
