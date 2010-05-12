#include "log.h"

string Log::ToString(TLogLevel T){
    switch(T){
    case logERROR:
	return "ERROR";
	break;
    case logWARNING:
	return "WARNING";
	break;
    case logINFO:
	return "INFO";
	break;
    case logDEBUG:
	return "DEBUG";
	break;
    }
}
string Log::cRojo = "\033[01;31m";
string Log::cVerde =  "\033[01;32m";
string Log::cAzul = "\033[01;34m";
string Log::cAmar = "\033[01;33m";
string Log::cDef = "\033[00m";
/*
    ROJO='\[\033[01;31m\]'
    VERDE='\[\033[01;32m\]'
    AZUL='\[\033[01;34m\]'
    AMAR='\[\033[01;33m\]'
    DEF='\[\033[00m\]'
*/

string Log::CON(string s){
    return cVerde + "[++ Constructor] " + s + cDef;
}

string Log::DES(string s){
    return cRojo + "[-- Destructor] " + s + cDef;
}

std::ostringstream& Log::Get(TLogLevel level)
{

    os << "[" << ToString(level) << "] ";
    return os;
}

Log::~Log(){
    os << std::endl;
    fprintf(stderr, "%s", os.str().c_str());
    fflush(stderr);
}

