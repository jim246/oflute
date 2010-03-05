#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "Gosu/Gosu.hpp"
#include <boost/scoped_ptr.hpp>

#define ANCHO 800
#define ALTO 600
#define FULLSCREEN false
#define FPS 30

class estado;

class Juego : public Gosu::Window{
    boost::scoped_ptr <estado> estadoActual;
public:
    Juego();
    void update();
    void draw();
    void cambiarEstado(std::string destino);
    void buttonDown(Gosu::Button boton);
    ~Juego();
};

#endif /* _JUEGO_H_ */
