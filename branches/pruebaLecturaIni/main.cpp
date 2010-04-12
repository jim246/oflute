#include <iostream>

using std::cout;
using std::endl;

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

int main(int argc, char *argv[])
{
    boost::property_tree::ptree arbol;
    read_ini("config.ini", arbol);
    float lim = arbol.get<float>("sonido.limite");

    cout << "Límite: " << lim << endl;
    return 0;
}

