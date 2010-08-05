/**
 * @file customFont.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Class to use custom fonts in Gosu & Linux
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


#ifndef _CUSTOMFONT_H_
#define _CUSTOMFONT_H_

#include "Gosu/Gosu.hpp"

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <SDL/SDL_ttf.h>


#include <iostream>

#include <cstdio>

using std::cout;
using std::cerr;
using std::endl;
/**
 * @class customFont
 *
 * @brief Draws text using ttf fontfaces
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class customFont {

    boost::scoped_ptr<Gosu::Image> imagen;

    /// Reference to graphics object
    Gosu::Graphics& graphics;

    /// Last color used
    Gosu::Color lastColor;

    /// Font name
    std::wstring fontName;

    /// Font size
    unsigned fontHeight;

    /// Actual SDL_TTF font object
    TTF_Font * font;

    /// Last text written
    std::string lastText;

    /**
     * @brief Creates a SDL Surface with the text written on it
     *
     * @param text the text to write
     * @param c color of the text
     *
     */

    SDL_Surface * createSurface(const std::string& text, Gosu::Color& c){
	// Convert the color to SDL datatype
	SDL_Color fontColor = {(int)c.red(), (int)c.green(), (int)c.blue()};

	// Render the surface
	SDL_Surface * textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), fontColor);
	
	if(textSurface == NULL){
	    cerr << "ERROR when trying to draw the text." << endl;
	    return NULL;
	}
	
	// Return the created surface
	return textSurface;
    }

public:
    /**
     * @brief Creates a new customFont, loading the font at the given path that can be rendered onto graphics.
     *
     * @param graphics The graphics object onto which the font will be rendered
     * @param fontName The filename for the typeface
     * @param fontHeight The size of the text
     *
     */

    customFont (Gosu::Graphics& graphics, 
		const std::wstring &fontName, 
		unsigned fontHeight) :
	graphics(graphics), lastColor(Gosu::Color::WHITE), fontName(fontName), 
	fontHeight(fontHeight), lastText(""){

	// Try to initialise SDL_TTF engine
	if( TTF_Init() < 0){
	    cerr << "ERROR when initialising TTF engine." << endl;
	    exit(-1);
	}

	// Try to open the font at the given path
	font = TTF_OpenFont(Gosu::wstringToUTF8(fontName).c_str(), fontHeight);

	if(font == NULL){
	    cout << "ERROR when trying to open font: " << TTF_GetError() << endl;
	    exit(-1);
	}

    }

    /**
     * @brief Returns the name (path) of the font
     *
     * @return The name of the font
     *
     */

    inline std::wstring name() const{
	return fontName;
    }

    /**
     * @brief Returns the size (points) of the font.
     *
     * @return The size of the font.
     *
     */

    inline unsigned height() const{
	return fontHeight;
    }

    /**
     * @brief Returns how tall a line of text is. Useful when rendering multiline text, paragraphs and such.
     *
     */

    int saltoLinea(){
	return TTF_FontLineSkip(font);
    }

    /**
     * @brief Returns the width of the string written with the loaded font
     *
     * @param text The text to be measured
     * @return Width in pixels.
     *
     */

    double textWidth(const std::string& text){
	double retorno;
	SDL_Surface * textSurface = createSurface(text, lastColor);

	if(textSurface == NULL){
	    retorno = -1;
	}else{
	    retorno = textSurface -> w;
	}
	    
	return retorno;
    }

    /**
     * @brief Writes the given text in the given position and using the given color.
     *
     * @param text Text to be written
     * @param x Horizontal position
     * @param y Vertical position
     * @param z Z position
     * @param c Color.
     *
     */

    void draw(std::string& text, int x, int y, 
	      Gosu::ZPos z, Gosu::Color c){

	// Create the surface
	SDL_Surface * textSurface = createSurface(text, c);
	
	if(textSurface == NULL){
	    cerr << "ERROR: The surface could not be created" << endl;
	    return;
	}

	// Get the width and height
	int w = textSurface -> w,
	    h = textSurface -> h;

	// Temporary bitmap object
	Gosu::Bitmap mapaBMP;

	// Resize the bitmap to the surface's size
	mapaBMP . resize(w, h);

	// Casting the input and output sources
	unsigned * source = (unsigned *) textSurface -> pixels;
	unsigned * dest = mapaBMP . data();
	
	// Copy every pixel in the original surface onto the new bitmap
	for(int i = 0; i < w; i++){
	    for(int j = 0; j < h; j++){
		*dest++ = *source++;
	    }
	}

	// Create the new image
	imagen . reset(new Gosu::Image(graphics, mapaBMP));

	// Draw the image at the given position
	imagen -> draw(x,y,z,1,1,Gosu::Color(c.alpha(), 255, 255, 255));

	// Delete the original surface
	SDL_FreeSurface (textSurface);
    }

    ~customFont(){
	TTF_CloseFont(font);
    }
};

#endif /* _CUSTOMFONT_H_ */
