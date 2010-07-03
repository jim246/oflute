#include "analizador.h"
#include "FFT.h"

#include <iostream>
#include <iomanip>

// Para usar abs
#include <cmath>

// Para usar min_element
#include <algorithm>
 
#include "configuracion.h"
#include "log.h"
#include "analizadorProxy.h"

#include <boost/ref.hpp>


using namespace std;

Analizador::Analizador(){
    lDEBUG << Log::CON("Analizador");

    notas[523.25] = Do5;
    notas[592.163] = Re5;
    notas[656.763] = Mi5;
    notas[699.829] = Fa5;
    notas[785.692] = Sol5;
    notas[893.628] = La5;
    notas[1001.29] = Si5;
    notas[1076.66] = Do6;
    notas[1195.09] = Re6;
}

t_altura Analizador::asociarNota(double frecuencia){
    std::map<double, t_altura> diferencias;
    std::map<double, t_altura>::iterator iter;

    for(iter = notas.begin();
	iter != notas.end();
	++iter)
    {
	diferencias[abs(frecuencia - iter -> first)] = iter -> second;
    }
    
    iter = min_element(diferencias.begin(), diferencias.end());
    return iter -> second;
    
}


void Analizador::iniciar(){
    lDEBUG << "Analizador::iniciar...";
    proxy . lanzar();
    hilo.reset(new boost::thread(boost::ref(proxy)));
    lDEBUG << "Hilo lanzado!";
}

void Analizador::detener(){
    lDEBUG << "Analizador::detener...";
    proxy . detener();
    hilo -> join();
    proxy . cerrarFlujo();
}

t_altura Analizador::notaActual(){
    if(lectorConfig.sonidoLimite() <= volumenActual()){
	float f = proxy . notaActual();
	if(f == 0){
	    return Silencio;
	}else{
	    return asociarNota(f);
	}
    }else{
	return Silencio;
    }
}

float Analizador::volumenActual(){
    return proxy . miBuffer -> lastVolume;
}
