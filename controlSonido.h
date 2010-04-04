#ifndef _CONTROLSONIDO_H_
#define _CONTROLSONIDO_H_

#include <portaudiocpp/PortAudioCpp.hxx>

#include "analizador.h"


class ControlSonido{

    portaudio::AutoSystem autoSys;

    portaudio::MemFunCallbackStream<Analizador> flujo;

public:
    ControlSonido();
    bool configurarFlujo(Analizador& analizador);
    bool iniciarFlujo();
    bool detenerFlujo();
};

#endif /* _CONTROLSONIDO_H_ */
