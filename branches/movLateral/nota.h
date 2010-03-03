#ifndef _NOTA_H_
#define _NOTA_H_

// Includes de Gosu
#include <Gosu/Gosu.hpp>

// Includes de Boost
#include <boost/scoped_ptr.hpp>

// Includes STL
#include <iostream>

using namespace std;


class Cancion;

class Nota{
public:
    
    enum t_altura { Do5, Re5, Mi5, Fa5, Sol5, La5, Si5, Do6, Re6 };
    static double longitudNegra;
//    static double duracionNegra;

    static double corchea;
    static double negra;
    static double blanca;
    static double unidad;

    t_altura altura;
    double duracion;

    bool aparece;

    /// Posición en el tiempo respecto del instante inicial
    double posicionInicial;
    double avanceMs;

    double tiemposAcumulados; // ¿Cuántos tiempos hay antes que ella (medido en negras)?

    
    int posX, posY;
    unsigned long acumulado;
    boost::scoped_ptr<Gosu::Image> figura;
    Cancion * cancionPadre;

    Nota(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c);

    void update();
    void draw();
    void instanciar(){
	cout << "* Instanciada" << endl;
	aparece = true;
    }
};


class Blanca : public Nota{
public:
    Blanca(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c);
};

class Negra : public Nota{
public:
    Negra(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c);
};

class Corchea : public Nota{
public:
    Corchea(Nota::t_altura alt, Gosu::Graphics * g, double acum, Cancion * c);
};

#endif /* _NOTA_H_ */
