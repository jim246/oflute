#ifndef _ANALIZADOR_H_
#define _ANALIZADOR_H_

#include "global.h"
#include <portaudio.h>

#include <map>

class tipoBuffer{
public:
    tipoBuffer():pos(0){}
    int pos;
    float in[4096];
    float out[2048];
};


class Analizador{
public:
    Analizador();
    bool configurarFlujo();
    bool iniciarAnalisis();
    t_altura notaActual();
    bool detenerAnalisis();
    ~Analizador();

    tipoBuffer miBuffer;

private:
    bool iniciado;

    // Vector de harmónicos más importantes en la nota
    float mayores[5];

    // Flujo principal
    PaStream * stream;

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
};


#endif /* _ANALIZADOR_H_ */
