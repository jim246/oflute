#ifndef _ESTADOCANCION_H_
#define _ESTADOCANCION_H_

#include "estado.h"

#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include "foreach.h"


#include <vector>

using namespace std;

#include "nota.h"

class Juego;

class myTimer{
    unsigned long inicial;
public:
    myTimer(){
	restart();
    }

    void restart(){
	inicial = Gosu::milliseconds();
    }

    unsigned long elapsed(){
	return Gosu::milliseconds() - inicial;
    }
    
};


class EstadoCancion : public Estado{
    int bpm;

    float milisegundosPorPulso;

    float frecuencia;

    /// Número de píxeles que en pantalla ocupa una negra
    int distanciaPulso;

    int margenIzquierdo;

    /// Espera inicial antes de la primera nota
    float esperaInicial;

    myTimer temporizador;

    bool lanzado;

    vector<boost::shared_ptr<Nota> > conjNotas;

public:
    EstadoCancion(Juego * p);

    void lanzar();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    
    ~EstadoCancion();
};

#endif /* _ESTADOCANCION_H_ */
