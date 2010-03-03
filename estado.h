#ifndef _ESTADO_H_
#define _ESTADO_H_

#include <Gosu/Gosu.hpp>
#include <iostream>

using namespace std;


class Juego;

class estado{
protected:
    Juego * padre;
//    Gosu::Graphics * graph;
public:
    estado(Juego * p):padre(p){};
    virtual void lanzar(){};
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void buttonDown(Gosu::Button){};
};

#endif /* _ESTADO_H_ */
