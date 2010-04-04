#include <iostream>

using namespace std;

#include "controlSonido.h"

#include "analizador.h"


int main(int argc, char *argv[])
{    

    ControlSonido C;
    Analizador A;
    C . configurarFlujo(A);
    C . iniciarFlujo();
    
    double a = 0;
    while(a++ < 1.e9){}

    C . detenerFlujo();

    return 0;
}
