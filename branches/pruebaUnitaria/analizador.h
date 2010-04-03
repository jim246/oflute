#ifndef _ANALIZADOR_H_
#define _ANALIZADOR_H_

#include "global.h"
#include <portaudiocpp/PortAudioCpp.hxx>

#include <map>

typedef int MY_TYPE;
#define TIPO paInt16;


class tipoBuffer{
public:
    tipoBuffer():pos(0), silencio(false){}
    int pos;
    float in[4096];
    float out[2048];

    float mayores[5];
    bool silencio;
};


class Analizador : public portaudio::CallbackInterface{
public:
    Analizador();
    bool configurarFlujo();
    bool iniciarAnalisis();
    t_altura notaActual();
    bool detenerAnalisis();
    ~Analizador();

    static tipoBuffer miBuffer;

private:
    bool iniciado, silencio;

    PaError err;

    // Vector de harmónicos más importantes en la nota
    float mayores[5];

    // Flujo principal
    PaStream * stream;

    // Mapa de frecuencias y notas
    std::map<double, t_altura> notas;

    // Devuelve la nota asociada a una frecuencia
    t_altura asociarNota(double frecuencia);

    // Función callback    
    int paCallbackFun(const void * inB, 
			     void * outB, 
			     unsigned long nFrames, 
			     const PaStreamCallbackTimeInfo * timeInfo,
			     PaStreamCallbackFlags statusFlags);

    portaudio::AutoSystem autoSys;


    portaudio::InterfaceCallbackStream flujo;

};


#endif /* _ANALIZADOR_H_ */
