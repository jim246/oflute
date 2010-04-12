#ifndef _ANALIZADOR_H_
#define _ANALIZADOR_H_

#include <portaudiocpp/PortAudioCpp.hxx>
#include <map>

#include "global.h"
#include "configuracion.h"


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
    bool iniciado;

    float int_to_hz, hz_to_int;

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
