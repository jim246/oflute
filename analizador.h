#ifndef _ANALIZADOR_H_
#define _ANALIZADOR_H_

#include <portaudiocpp/PortAudioCpp.hxx>
#include <map>

#include "global.h"

class tipoBuffer{
public:
    tipoBuffer():pos(0), silencio(false){}
    int pos;
    float in[4096];
    float out[2048];

    float mayores[5];
    bool silencio;
};


class Analizador{

    t_altura asociarNota (double frecuencia);
    std::map<double, t_altura> notas;

public:

    tipoBuffer * miBuffer;

    Analizador();

    t_altura notaActual();

    int funcionCallback(const void * inB, 
			void * outB, 
			unsigned long nFrames, 
			const PaStreamCallbackTimeInfo * timeInfo,
			PaStreamCallbackFlags statusFlags);

    ~Analizador();

};

#endif /* _ANALIZADOR_H_ */
