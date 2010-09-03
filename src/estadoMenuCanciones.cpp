/**
 * @file estadoMenuCanciones.cpp
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


#include "juego.h"
#include "estadoCancion.h"

#include "estadoMenuCanciones.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <pugixml.hpp>

#include <string>



EstadoMenuCanciones::EstadoMenuCanciones(Juego * p)
    : Estado(p), cancionCargada(false){

    lDEBUG << Log::CON("EstadoMenuCanciones");

    estadoTransicion = transIn;

    // CONFIGURACIÓN DE LA IMAGEN DEL LOGOTIPO
    imgLogotipo.reset(new ElementoImagen(padre -> graphics(),
					 "media/ofluteLogoGrande.png",
					 3, Animacion::tAlpha));

    imgLogotipo -> setXY(75, 100);
    imgLogotipo -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic);
    imgLogotipo -> animacion -> set(0, 0, 255);


    imgSeleccion.reset(new ElementoImagen(padre -> graphics(),
					  "media/selCanMark.png",
					  3, Animacion::tPos));

    imgSeleccion -> animacion = new Animacion(2, 30, Animacion::tEaseOutCubic, 10);
    imgSeleccion -> animacion -> set(0, 800, 397);
    imgSeleccion -> animacion -> set(1, 100, 100);

	

    imgBtnUp.reset(new ElementoImagen(padre -> graphics(),
				      "media/selCanUp.png",
				      3, Animacion::tPos));
    imgBtnUp -> animacion = new Animacion(2, 30, Animacion::tEaseOutCubic, 30);
    imgBtnUp -> animacion -> set(0, 360, 360);
    imgBtnUp -> animacion -> set(1, -40, 101);

    imgBtnDown.reset(new ElementoImagen(padre -> graphics(),
					"media/selCanDown.png",
					3, Animacion::tPos));
    imgBtnDown -> animacion = new Animacion(2, 30, Animacion::tEaseOutCubic, 20);
    imgBtnDown -> animacion -> set(0, 360, 360);
    imgBtnDown -> animacion -> set(1, -40, 139);


    imgBtnOk.reset(new ElementoImagen(padre -> graphics(),
				      "media/selCanOk.png",
				      3, Animacion::tPos));
    imgBtnOk -> animacion = new Animacion(2, 30, Animacion::tEaseOutCubic, 10);
    imgBtnOk -> animacion -> set(0, 360, 360);
    imgBtnOk -> animacion -> set(1, -40, 176);


    // CONFIGURACIÓN DEL SUBTÍTULO
    txtSubtitulo.reset(new ElementoTexto(padre -> graphics(),
					 _("Seleccione una canción"),
					 "media/fNormal.ttf",
					 34, Gosu::Color(0xffa4a4a4),
					 Texto::alignCentro,
					 true, 10, 3, 
					 Animacion::tAlpha));

    txtSubtitulo -> setXY(180, 425);
    txtSubtitulo -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 10);
    txtSubtitulo -> animacion -> set(0, 0, 255);

}

void EstadoMenuCanciones::update(){
    if(cancionCargada == true) {
	lDEBUG << LOC() << " WATTTTTTTTTTTTTTTTTTTTT????????????????????????????????????????????";
    }


    if(estadoTransicion == transIn){
	if(imgLogotipo -> animacion -> finished() &&
	   txtSubtitulo -> animacion -> finished()){

	    lDEBUG << "Botones en su sitio";
	    estadoTransicion = transHold;
	    listarCanciones();
	}
    }
	
    else if(estadoTransicion == transOut && imgBtnOk -> animacion -> finished()){
	lDEBUG << "Animaciones de ocultación terminadas";
	padre -> cambiarEstado("estadoMenuSinFondo");
    }

}

void EstadoMenuCanciones::draw(){
    if(estadoTransicion == mostrandoCancion){
//		cancion -> draw();
    }else{
	imgLogotipo -> draw();
	txtSubtitulo -> draw();
	imgSeleccion -> draw();
	imgBtnUp -> draw();
	imgBtnDown -> draw();
	imgBtnOk -> draw();

	if(estadoTransicion == transHold && !conjuntoCanciones.empty()){
	    boost::shared_ptr<EntradaMenuCanciones> E;
	    foreach(E, conjuntoCanciones){
		E -> draw();
	    }
	}
    }
}

void EstadoMenuCanciones::buttonDown(Gosu::Button boton){
    if(cancionCargada == true){
//		cancion -> buttonDown(boton);
    }

    if(boton == Gosu::kbEscape){
	if(estadoTransicion == transHold){
	    estadoTransicion = transOut;

	    imgLogotipo -> animacion -> reverse();
	    imgLogotipo -> animacion -> init();

	    imgSeleccion -> animacion -> reverse();
	    imgSeleccion -> animacion -> init();

	    imgBtnUp -> animacion -> reverse();
	    imgBtnUp -> animacion -> init();
	    imgBtnUp -> animacion -> setEspera(10);

	    imgBtnDown -> animacion -> reverse();
	    imgBtnDown -> animacion -> init();
	    imgBtnDown -> animacion -> setEspera(20);

	    imgBtnOk -> animacion -> reverse();
	    imgBtnOk -> animacion -> init();
	    imgBtnOk -> animacion -> setEspera(30);

	    txtSubtitulo -> animacion -> reverse();
	    txtSubtitulo -> animacion -> init();

	    estadoTransicion = transOut;

	}
    }

    else if(boton == Gosu::kbReturn){

	lDEBUG << "Se pulsó enter";

	/*
	cancionCargada = true;

	//	cancion.reset(new Cancion(padre -> graphics(), "song1.xml"));
	//  cancion -> lanzar();

	estadoTransicion = mostrandoCancion;

	//*/
    }

    else if(boton == Gosu::msLeft){
	int x = padre -> input().mouseX();
	int y = padre -> input().mouseY();

	if(estadoTransicion == transHold){
	    if(imgBtnUp -> clicked(x,y)){
		lDEBUG << "UP";
	    }else if(imgBtnDown -> clicked(x,y)){
		lDEBUG << "Down";
	    }else if(imgBtnOk -> clicked(x,y)){
		lDEBUG << "Ok";
	    }
	}
    }
}

EstadoMenuCanciones::~EstadoMenuCanciones(){
    lDEBUG << Log::DES("EstadoMenuCanciones");
}

void EstadoMenuCanciones::listarCanciones(){

    boost::filesystem::path rutaDirectorio("./canciones");
    boost::filesystem::directory_iterator inicial(rutaDirectorio), final;

    pugi::xml_document documento;
    pugi::xml_parse_result resultado;
    pugi::xml_node nodoActual, nodoVacio;
    pugi::xml_attribute atributo;

    unsigned contadorCanciones = 0;

    for(; inicial != final ; ++ inicial){
	if(boost::to_lower_copy(inicial -> path() . extension()) == ".xml"){


	    string atrRuta, atrTitulo, atrDescripcion, atrPos;


	    atrRuta = boost::lexical_cast<string>(inicial -> path());

	    lDEBUG << "Intentando cargar archivo " << atrRuta;

	    resultado = documento . load_file(atrRuta.c_str());

	    if(!resultado){
		lERROR << LOC() << " Error al leer el documento: " << atrRuta;
		lERROR << resultado.description(); 
		continue;
	    }

	    //lecActual.atrRuta = atrRuta;

	    /////////////////
	    // Leemos el título de la canción

	    nodoActual = documento.child("Song").child("Title");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << atrRuta << " no está bien formado. "
		       << "(Falta nombre)";
		continue;
	    }

	    atrTitulo = nodoActual.first_child().value();

	    /////////////////////
	    // Leemos la descripción
	    nodoActual = documento.child("Song").child("Desc");

	    if(nodoActual == nodoVacio){
		lERROR << "El fichero " << atrRuta << " no está bien formado. "
		       << "(Falta descripción)";
		continue;
	    }

	    atrDescripcion = nodoActual.first_child().value();

	    boost::shared_ptr<EntradaMenuCanciones> cancionActual;
	    
	    cancionActual.reset(new EntradaMenuCanciones(padre -> graphics(),
							 atrTitulo, atrDescripcion, atrRuta, 
							 contadorCanciones++));

	    conjuntoCanciones.push_back(cancionActual);

	}
    }

    //sort(leccionesCargadas.begin(), leccionesCargadas.end(), ordenarLecciones());
    //leccionActual = 0;
    //cambiarLeccion(leccionActual);

}
