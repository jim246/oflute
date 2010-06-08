#include "analizador.h"
#include "controlSonido.h"

#include "FFT.h"
#include "log.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;

ControlSonido::ControlSonido(){
    lDEBUG << Log::CON("ControlSonido");
}


bool ControlSonido::configurarFlujo(Analizador& analizador){

    portaudio::System &sys = portaudio::System::instance();

    lDEBUG << Log::cAzul << "PortAudio version number = " << sys.version();
    lDEBUG << Log::cAzul << "PortAudio version text = '" << sys.versionText() << "'";

    portaudio::DirectionSpecificStreamParameters paramEntrada(
	sys.defaultInputDevice(),  // dispositivo
	2, // número de canales
	portaudio::INT32, // formato
	false, // entrelazado
	sys.defaultInputDevice().defaultLowInputLatency(), // latencia sugerida
	NULL);

    portaudio::DirectionSpecificStreamParameters paramSalida(
	sys.defaultOutputDevice(),  // dispositivo
	2, // número de canales
	portaudio::INT32, // formato
	false, // entrelazado
	sys.defaultOutputDevice().defaultLowOutputLatency(), // latencia sugerida
	NULL);

    //cout << "*** [Analizador] Nombre del dispositivo: " << sys.defaultInputDevice().name() << endl;

    portaudio::StreamParameters parametros(
	paramEntrada,
	paramSalida,
	44100.0,
	256,
	paClipOff);

    //cout << "*** [Analizador] isSupported(): " << (int)parametros.isSupported() << endl;

    flujo.open(parametros, analizador, &Analizador::funcionCallback);

    return true;
} 


bool ControlSonido::iniciarFlujo(){
    flujo.start();

    lDEBUG << Log::cAmar << "ControlSonido: Flujo iniciado" << Log::cDef;

    return true;
} // Fin de iniciarAnalisis

bool ControlSonido::detenerFlujo(){
    try{
	// Paramos el flujo
	flujo.stop();
	flujo.close();
	lDEBUG << Log::cAmar << "ControlSonido: Flujo detenido" << Log::cDef;

 	return true;
    }
    catch (const portaudio::PaException &e)
    {
	std::cout << "A PortAudio error occured: " << e.paErrorText() << std::endl;
    }
    catch (const portaudio::PaCppException &e)
    {
	std::cout << "A PortAudioCpp error occured: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
	std::cout << "A generic exception occured: " << e.what() << std::endl;
    }
    catch (...)
    {
	std::cout << "An unknown exception occured." << std::endl;
    }
    
    return true;
}

ControlSonido::~ControlSonido(){
    lDEBUG << Log::DES("ControlSonido");
    portaudio::System::instance().terminate();
}
