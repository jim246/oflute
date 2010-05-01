PROJECT( oFlute )
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(SDL)
#FIND_PACKAGE(SDL_ttf)
FIND_PACKAGE(Boost)

FIND_PATH(rutaPortAudio "portaudiocpp/PortAudioCpp.hxx")

IF(NOT rutaPortAudio)
  MESSAGE(FATAL_ERROR "** Falta la cabecera de PortAudio")
ENDIF()

INCLUDE_DIRECTORIES(rutaPortAudio)

FIND_LIBRARY(rutaLibPortAudio portaudiocpp)

IF(NOT rutaLibPortAudio)
  MESSAGE(FATAL_ERROR "** Falta la librería PortAudioCpp")
ENDIF()

LINK_LIBRARIES(SDL_ttf)

INCLUDE_DIRECTORIES(gosu)
INCLUDE_DIRECTORIES(.)

#set ( CMAKE_CXX_FLAGS "")

# Ejecutamos gosu-config para sacar las flags de la compilación
EXECUTE_PROCESS(COMMAND ./gosu/bin/gosu-config --cxxflags 
  OUTPUT_VARIABLE salidaGosuConfigCXX 
  OUTPUT_STRIP_TRAILING_WHITESPACE)
  
SET(CMAKE_CXX_FLAGS "${salidaGosuConfigCXX}")

ADD_LIBRARY (libGosu STATIC IMPORTED)

SET_PROPERTY (TARGET libGosu PROPERTY IMPORTED_LOCATION ./gosu/lib/libgosu.a)

# Ejecutamos gosu-config para sacar las flags de enlazado
EXECUTE_PROCESS(COMMAND ./gosu/bin/gosu-config --libs 
  OUTPUT_VARIABLE salidaGosuConfig
  OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} ${salidaGosuConfig}")


ADD_EXECUTABLE(programa main.cpp juego.cpp estadoImagenFija.cpp estadoMenu.cpp FFT.cpp analizador.cpp controlSonido.cpp estadoAnalizador.cpp colores.cpp animacion.cpp)

TARGET_LINK_LIBRARIES(programa ${rutaLibPortAudio} libGosu)