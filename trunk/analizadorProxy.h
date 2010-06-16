#ifndef _ANALIZADORPROXY_H_
#define _ANALIZADORPROXY_H_

#include <map>
#include <cmath>

#include "configuracion.h"
#include "log.h"
#include "global.h"

#include <pulse/simple.h>
/**
 * @class tipoBuffer
 *
 * @brief Búffer en el que se guardan los datos de la captura.
 *
 * El sistema de audio va capturando audio y volcando los datos en este búffer, que luego se pasa a la función de Fourier
 * para calcular la frecuencia. 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class tipoBuffer{
public:
    tipoBuffer():pos(0), silencio(false){}
    int pos;
    int in[4096];
    float out[2048];
    float lastVolume;
    float mayores[5];
    bool silencio;
};


class AnalizadorProxy{
    float int_to_hz;
    float hz_to_int;

    t_altura asociarNota (double frecuencia);
    std::map<double, t_altura> notas;
    bool iniciado;
    bool salir;

//    lectorConfiguracion L;
public:
    AnalizadorProxy();
    AnalizadorProxy(const AnalizadorProxy& copia);

    tipoBuffer * miBuffer;
    t_altura notaActual();
    
    void operator()();
    void lanzar();
    void detener();

    ~AnalizadorProxy(); //*/
};

#endif /* _ANALIZADORPROXY_H_ */
