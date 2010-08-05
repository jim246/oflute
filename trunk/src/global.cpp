#include "global.h"
#include "log.h"

float durfig(t_figura t){
    if(t == Redonda){
	return 4;
    }else if(t == Blanca){
	return 2;
    }else if(t == Negra){
	return 1;
    }else if(t == Corchea){
	return 0.5;
    }else{
	return 0;
    }
}

map<string,string> cadenasTraducciones;

void inicializarTrad(string lang){
    boost::property_tree::ptree arbol;
    boost::property_tree::ptree::iterator iter1, iter2;
    try{
	read_json("trans." + lang, arbol);
    }catch(...){
	lERROR << "ERROR al leer el fichero de cadenas";
    }
    for(iter1 = arbol.begin(); iter1 != arbol.end(); iter1++){
	cadenasTraducciones[iter1 -> first] = iter1 -> second.data();
    }
}

string _(const char * S){
    if(cadenasTraducciones.find(string(S)) != cadenasTraducciones.end()){
	return cadenasTraducciones[string(S)];
    }else{
	lERROR << "Cadena sin traducir: " << S;
	return string(S);
    }
}
