// customFont.h --- Class to use custom fonts in Gosu

// Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>

// Autor: José Tomás Tocino García

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.

#ifndef _CUSTOMFONT_H_
#define _CUSTOMFONT_H_

#include "Gosu/Gosu.hpp"

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <SDL.h>
#include <SDL/SDL_ttf.h>

#include <iostream>

using std::cerr;
using std::endl;

class customFont {
    Gosu::Graphics& graphics;
    std::wstring fontName;
    unsigned fontHeight;

    boost::scoped_ptr<Gosu::Bitmap> mapaBMP;
    boost::scoped_ptr<Gosu::Image> imagen;
    TTF_Font * font;

    std::string lastText;

    SDL_Surface * createSurface(const std::string& text, Gosu::Color c){
	SDL_Surface * textSurface;
	SDL_Color fontColor = {c.red(), c.green(), c.blue()};
	
	textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), fontColor);
	
	if(textSurface == NULL){
	    cerr << "ERROR when trying to draw the text." << endl;
	    return NULL;
	}
	
	return textSurface;
    }

public:
    customFont (Gosu::Graphics &graphics, 
		const std::wstring &fontName, 
		unsigned fontHeight,
		unsigned fontFlags = 0) :
	graphics(graphics), fontName(fontName), fontHeight(fontHeight){
	
	if( TTF_Init() < 0){
	    cerr << "ERROR when initialising TTF engine." << endl;
	    exit(-1);
	}

	font = TTF_OpenFont(Gosu::wstringToUTF8(fontName).c_str(), fontHeight);

	if(fontFlags != 0){
	    TTF_SetFontStyle(font, fontFlags);
	}
	 


	if(font == NULL){
	    cerr << "ERROR when trying to open font." << endl;
	    exit(-1);
	}
    }

    inline std::wstring name() const{
	return fontName;
    }

    inline unsigned height() const{
	return fontHeight;
    }
    void setHinting(unsigned i){
	if(i > 3) return;
//	TTF_SetFontHinting(font, i);
    }
    double textWidth(const std::string& text){
	double retorno;
	SDL_Surface * textSurface = createSurface(text, Gosu::Color::WHITE);
	if(textSurface == NULL){
	    retorno = -1;
	}else{
	    retorno = textSurface -> w;
	}
	
	SDL_FreeSurface (textSurface);

	return retorno;
    }

    void draw(const std::string& text, double x, double y, Gosu::ZPos z, Gosu::Color c = Gosu::Color::WHITE){

	// Avoid redrawing the text if it hasn't changed
	if(text != lastText){
	    SDL_Surface * textSurface = createSurface(text, c);
	    
	    if(textSurface == NULL){
		return;
	    }

	    int w = textSurface -> w,
		h = textSurface -> h;

	    mapaBMP.reset(new Gosu::Bitmap());
	    mapaBMP -> resize(w, h);

	    unsigned * source = (unsigned *) textSurface -> pixels;
	    unsigned * dest = mapaBMP -> data();

	    for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
		    *dest++ = *source++;
		}
	    }

	    SDL_FreeSurface (textSurface);
	    imagen.reset(new Gosu::Image(graphics, *mapaBMP));
	}

	imagen -> draw(x,y,z);

	lastText = text;	
    }

    ~customFont(){
	TTF_CloseFont(font);
    }
};

#endif /* _CUSTOMFONT_H_ */
