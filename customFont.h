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

#include <cstdio>

using std::cout;
using std::cerr;
using std::endl;

class customFont {
    Gosu::Graphics& graphics;
    Gosu::Color lastColor;

    std::wstring fontName;
    unsigned fontHeight;

    
  
    TTF_Font * font;

    std::string lastText;

    SDL_Surface * createSurface(const std::string& text, Gosu::Color& c){

//	cout << (int)c.red() << " " << (int) c.green() << " " << (int)c.blue() << endl;
	SDL_Color fontColor = {(int)c.red(), (int)c.green(), (int)c.blue()};

	SDL_Surface * textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), fontColor);
	
	if(textSurface == NULL){
	    cerr << "ERROR when trying to draw the text." << endl;
	    return NULL;
	}
	


	return textSurface;

	/*
	SDL_Surface * alphaedSurface = SDL_DisplayFormat(textSurface);

	if(alphaedSurface == NULL){
	    cerr << "ERROR" << endl;
	    return NULL;
	}

	SDL_FreeSurface(textSurface);
	return alphaedSurface; //*/
    }

public:
    customFont (Gosu::Graphics& graphics, 
		const std::wstring &fontName, 
		unsigned fontHeight) :
	graphics(graphics), lastColor(Gosu::Color::WHITE), fontName(fontName), 
	fontHeight(fontHeight), lastText(""){
	
	if( TTF_Init() < 0){
	    cerr << "ERROR when initialising TTF engine." << endl;
	    exit(-1);
	}

	font = TTF_OpenFont(Gosu::wstringToUTF8(fontName).c_str(), fontHeight);

	if(font == NULL){
	    cout << "ERROR on TTF_OpenFont: " << TTF_GetError() << endl;
	    exit(-1);
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
    }

    int saltoLinea(){
	return TTF_FontLineSkip(font);
    }

    double textWidth(const std::string& text){
	double retorno;
//	if(text != lastText){
	    SDL_Surface * textSurface = createSurface(text, lastColor);
	    if(textSurface == NULL){
		retorno = -1;
	    }else{
		retorno = textSurface -> w;
	    }
	    
//	    SDL_FreeSurface (textSurface);
//	    textSurface = NULL;
	    /*}else{
	    retorno = imagen -> width();
	} //*/
	    
	return retorno;
    }

    void draw(std::string& text, int x, int y, 
	      Gosu::ZPos z, Gosu::Color c){

	/*
	cout << "SURMANOOOOOOOO" << endl;
	Gosu::Image * imagen = new Gosu::Image(graphics, L"media/estadoAutor.png");
	cout << "CHARMANDERRRR" << endl;
	imagen -> draw(x,y,z, 1,1); //Gosu::Color(c.alpha(), 255, 255, 255));
	cout << "MUERONCAI" << endl; 
	//*/

	
	
	    SDL_Surface * textSurface = createSurface(text, c);
	
	    if(textSurface == NULL){
		cout << "WAT?" << endl;
		return;
	    }

	    int w = textSurface -> w,
		h = textSurface -> h;

	    Gosu::Bitmap mapaBMP;

//	    boost::scoped_ptr<Gosu::Bitmap> mapaBMP (new Gosu::Bitmap());
	    mapaBMP . resize(w, h);
	
	    unsigned * source = (unsigned *) textSurface -> pixels;
	    unsigned * dest = mapaBMP . data();
	
	    for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
		    *dest++ = *source++;
		}
	    }
	     

	Gosu::Image * imagen = new Gosu::Image(graphics, mapaBMP);

	imagen -> draw(x,y,z);


	SDL_FreeSurface (textSurface);
//	delete textSurface;

	

/*	lastText = text;	
	lastColor = c; //*/
    }

    ~customFont(){
	TTF_CloseFont(font);
    }
};

#endif /* _CUSTOMFONT_H_ */
