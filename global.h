// global.h --- Cosas globales

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

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

enum t_altura { Do5, Re5, Mi5, Fa5, Sol5, La5, Si5, Do6, Re6, Silencio };
enum t_figura { Redonda, Blanca, Negra, Corchea };

float durfig(t_figura t){
    if(t == Redonda){
	return 4;
    }else if(t == Blanca){
	return 2;
    }else if(t == Negra){
	return 1;
    }else if(t == Corchea){
	return 0.5;
    }else{
	return 0;
    }
}

#endif /* _GLOBAL_H_ */
