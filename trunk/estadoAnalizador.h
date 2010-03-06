#ifndef _ESTADOANALIZADOR_H_
#define _ESTADOANALIZADOR_H_

#include "estado.h"
#include "juego.h"

#include <Gosu/Gosu.hpp>
#include "boost/scoped_ptr.hpp"

#include "portaudio.h"


#include "global.h"

#include <string>
#include <map>

class Juego;

class tipoBuffer{
public:
    tipoBuffer():pos(0){}
    int pos;
    float in[4200]; // 4096
    float out[2048];

    // Vector de harmónicos más importantes en la nota
    float mayores[5];
};

class estadoAnalizador : public estado{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo;
    boost::shared_ptr<Gosu::Image> imgDo5, imgRe5, imgMi5, imgFa5, imgSol5, imgLa5, imgSi5, imgDo6, imgRe6;

    bool iniciado, silencio;

    // Flujo principal
    PaStream * stream;

    PaError err;

    // Mapa de frecuencias y notas
    std::map<double, t_altura> notas;

    // Devuelve la nota asociada a una frecuencia
    t_altura asociarNota(double frecuencia);

    // Función callback    
    static int updateBuffer(const void * inB, 
			    void * outB, 
			    unsigned long nFrames, 
			    const PaStreamCallbackTimeInfo * timeInfo,
			    PaStreamCallbackFlags statusFlags,
			    void * data);
    int updateBuffer2(const void * inB, 
			    void * outB, 
			    unsigned long nFrames, 
			    const PaStreamCallbackTimeInfo * timeInfo,
		      PaStreamCallbackFlags statusFlags);
    
public:
    int numSamples;

    static tipoBuffer miBuffer;
    estadoAnalizador(Juego * p);
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    bool configurarFlujo();
    bool iniciarAnalisis();
    t_altura notaActual();
    bool detenerAnalisis();
    ~estadoAnalizador();
};

#endif
