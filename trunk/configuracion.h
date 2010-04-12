#ifndef _CONFIGURACION_H_
#define _CONFIGURACION_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


#include <iostream>
using namespace std;

class lectorConfiguracion{
public:
    lectorConfiguracion(){
	boost::property_tree::ptree arbol;

	read_ini("config.ini", arbol);
	float lim = arbol.get<float>("sonido.limite");

	cout << "Límite: " << lim << endl;
    }

};

#endif /* _CONFIGURACION_H_ */
