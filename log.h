/**
 * @file log.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Clase para el log
 * 
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>

using namespace std;

// Añade Función:(Archivo: linea) desde donde fué llamada.
// Literales de cadena no indexados se concatenan.
#define LOC()  std::endl <<						\
			    __FUNCTION__ << " :(" << __FILE__ << ":" <<  __LINE__ << ")  " 
    
// Añade variable == valor.
// (x) debe tener definido el operador << obviamente.
#define VARV(x) #x << " = " << (x)

// Log, version 0.1: a simple logging class
enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG};

class Log{
public:
    ~Log();
    std::ostringstream& Get(TLogLevel level = logINFO);

    static string ToString(TLogLevel T);

    static string CON(string s);

    static string DES(string s);
    static string cRojo, cVerde, cAzul, cAmar, cDef;
protected:
    std::ostringstream os;

};


#define lDEBUG Log().Get(logDEBUG)


/*
  class Log{
  public:    
  stringstream S;
  int level;
  Log(int l = LINFO) : level(l){ }
    
  ~Log(){
  switch(level){
  case LWARN:
  cout << "[WARN] " << S.str() << flush;
  break;
	
  case LINFO:
  cout << "[INFO] " << S.str() << flush;
  break;

  case LDEBUG:
  cout << "[DEBUG] " << S.str() << flush;
  break;
  }
  }
    
  static stringstream& info(){
  return Log(LINFO);
  }

  template <typename T>
  friend Log& operator<<(Log& log, const T& value);
  friend Log& operator<<(Log& log, ostream& (*pf) (ostream&));
  };

  template <typename T>
  Log& operator <<(Log& log, T const & value) {
  log.S << value;
  return log;
  }


  Log& operator<< (Log& log, ostream& (*pf) (ostream&))
  {
  log.S << pf;
  return log;
  }//*/



#endif /* _LOG_H_ */
