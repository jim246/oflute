#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

#define TIXML_USE_STL
#include "tinyxml.h"
#include "tinystr.h"


#include "boost/regex.hpp"


int main(int argc, char *argv[])
{
    TiXmlDocument doc;
    doc.LoadFile( "song1.xml");

    TiXmlHandle manejador( &doc );
    TiXmlElement * elemento = manejador
	.FirstChild("Song")
	.FirstChild("Notes")
	.ToElement();

    if(!elemento) throw ("ERROR"); 
    string notas = elemento -> GetText();

    map<string, string> nombresFiguras;
    nombresFiguras["r"] = "redonda"; 
    nombresFiguras["b"] = "blanca"; 
    nombresFiguras["n"] = "negra"; 
    nombresFiguras["c"] = "corchea"; 

    boost::regex myRegExp("(do|re|mi|fa)(5|6)(r|b|n|c)");

    boost::sregex_iterator myIt(notas.begin(), notas.end(), myRegExp), itEnd;

    for(;myIt != itEnd; myIt++){
	cout << "Nota: " << (*myIt)[1]
	     << ", octava: " << (*myIt)[2] 
	     << ", figura: " << nombresFiguras[(*myIt)[3]] << endl;
    } //*/

    return 0;
}
