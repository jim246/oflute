#ifndef _CANCION_H_
#define _CANCION_H_

#include <vector>
#include <queue>

#include "global.h"

#include "nota.h"

#include <Gosu/Gosu.hpp>

class Cancion{

public:
    queue<Nota*> pilaNotas;
    vector<Nota*> vectorNotasInstanciadas;

    // Momento en el que se inicia la canción
    double momentoInicial;

    // Momento actual
    double momentoTranscurrido;

    /// Duración de una negra en milisegundos según el bpm de la canción
    double duracionNegra;

    // Tiempo después del cual las notas deben ser instanciadas y aparecer en pantalla
    double tiempoSeguridad;

    double diferencialHorizontal;

    Cancion(Gosu::Graphics * g);

    void comenzarCancion();

    void update();
    void draw();

    ~Cancion();
};

#endif /* _CANCION_H_ */
