#include <iostream>

using namespace std;

#include "analizador.h"


int main(int argc, char *argv[])
{    
    Analizador * A = new Analizador();
    A -> configurarFlujo();
    A -> iniciarAnalisis();

    double a = 0;
    while(a++ < 1.e8){}

    A -> detenerAnalisis();

    delete A;
    A = NULL;
    return 0;
}
