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
}

t_altura Analizador::notaActual(){
    return proxy . notaActual();
}

float Analizador::volumenActual(){
    return proxy . miBuffer -> lastVolume;
}
