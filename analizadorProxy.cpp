#include "analizadorProxy.h"
#include "FFT.h"

#include <iomanip>
#include <fstream>

#define BUFSIZE 4096


AnalizadorProxy::AnalizadorProxy() : iniciado(false), salir(false){
    lDEBUG << Log::CON("AnalizadorProxy");

    miBuffer = new tipoBuffer;

    notas[523.25] = Do5;
    notas[592.163] = Re5;
    notas[656.763] = Mi5;
    notas[699.829] = Fa5;
    notas[785.692] = Sol5;
    notas[893.628] = La5;
    notas[1001.29] = Si5;
    notas[1076.66] = Do6;
    notas[1195.09] = Re6;

    // Definimos dos constantes para hacer las conversiones desde 
    // posición del vector a frecuencia y viceversa
    
    //Para pasar de pos de vector a frecuencia, multiplicamos por 22050/2048
    int_to_hz = 22050./(BUFSIZE / 2.); // ~ 10.76660156250000000000000

    // PAra pasar de frecuencia a posición de vector, multiplicamos por 2048/22050
    hz_to_int = (BUFSIZE / 2.)/22050.; // ~ 0.928798185941043083900226

    lDEBUG << VARV(int_to_hz) << "  " << VARV(hz_to_int);
};

AnalizadorProxy::AnalizadorProxy(const AnalizadorProxy& copia){
    lDEBUG << Log::CON("AnalizadorProxy Constructor de copia");
    notas = copia.notas;
    int_to_hz = copia.int_to_hz;
    hz_to_int = copia.hz_to_int;
    iniciado = copia.iniciado;
    salir = copia.salir;
    miBuffer = new tipoBuffer;    
}

t_altura AnalizadorProxy::asociarNota(double frecuencia){
    std::map<double, t_altura> diferencias;
    std::map<double, t_altura>::iterator iter;

    for(iter = notas.begin();
	iter != notas.end();
	++iter)
    {
	diferencias[abs(frecuencia - iter -> first)] = iter -> second;
    }
    
    iter = min_element(diferencias.begin(), diferencias.end());
    return iter -> second;
    
}

t_altura AnalizadorProxy::notaActual(){
    if(miBuffer -> silencio)
	return Silencio;

    return asociarNota(miBuffer -> mayores[0]);
}


void AnalizadorProxy::lanzar(){
    iniciado = true;
}

void AnalizadorProxy::detener(){
    lDEBUG << "AnalizadorProxy::detener...";
    iniciado = false;
    salir = true;
    lDEBUG << VARV(iniciado);
    lDEBUG << VARV(salir);
}

AnalizadorProxy::~AnalizadorProxy(){
    lDEBUG << Log::DES("AnalizadorProxy");
    if(miBuffer != 0){
	delete miBuffer;
	miBuffer = NULL;
    }
}



void AnalizadorProxy::operator()(){

    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 44100;
    ss.channels = 1;


    lDEBUG << "Tamaño del formato: " << pa_sample_size(&ss);

    pa_simple * sIn = NULL;
    pa_simple * sOut = NULL;

    int error;

    pa_buffer_attr atr;
    atr.maxlength = (uint32_t) -1;
    atr.prebuf =  (uint32_t) -1;
    atr.minreq =  (uint32_t) -1;
    atr.fragsize = 1;
    atr.tlength = 1;

    if (!(sIn = pa_simple_new(NULL, "nozin", PA_STREAM_RECORD, NULL, 
			      "record", &ss, NULL, &atr, &error))) {
	cerr << "ERROR" << endl;
    }

    if (!(sOut = pa_simple_new(NULL, "nozin", PA_STREAM_PLAYBACK, NULL, 
			       "playback", &ss, NULL, &atr, &error))) {
	cout << "ERROR" << endl;
    }

    cout << "Frame size: " << pa_frame_size(&ss) << endl
	 << "Sample size: " << pa_sample_size(&ss) << endl
	 << "Formato intermedio: " << sizeof(int16_t) << endl
	 << "Convers: " << sizeof(int) << endl;

    fstream F;
    F.open("test", fstream::in | fstream::out);
    cout << "Failed? " << F.fail() << endl;

    for(;;){
	if(iniciado){
	    int16_t buf[BUFSIZE];
	    float in[BUFSIZE];
	    float out[BUFSIZE / 2];

	    float maxValue[] = {0,0,0};
	    float maxPos[] = {0,0,0};
                
	    if (pa_simple_read(sIn, buf, sizeof(buf), &error) < 0) {
		cerr << "ERROR al grabar" << endl;
	    }

	    // Dump al fichero y al vector de flotantes
	    for (int i = 0; i < BUFSIZE; ++i)
	    {
		in[i] = (int)buf[i];
		//F << (int)buf[i] << endl;
		//F << in[i] << endl;
	    }

#if 1
	    WindowFunc(3, BUFSIZE,  in);
	    PowerSpectrum(BUFSIZE,  in,  out);
	    
	    for(int i = 450 * hz_to_int; i < BUFSIZE / 2; ++i){
		for (int j = 0; j < 3; j++)
		{
		    if( out[i] > maxValue[j]){
			maxValue[j] =  out[i];
			maxPos[j] = i;
			break;
		    }
		}                   
		
		// Hemos seleccionado como límite superior 1500Hz
		// 22050 => 2048
		// x     => i
		// x = i * 22050 / 2048 = i * 10.766

		if(i * int_to_hz > 1500) break;
	    } //*/
	    

	    miBuffer -> lastVolume = maxValue[0];
	    
	    miBuffer -> mayores[0] = maxPos[0]  * int_to_hz;
	    miBuffer -> mayores[1] = maxPos[1]  * int_to_hz;
	    miBuffer -> mayores[2] = maxPos[2]  * int_to_hz;

	    int ancho = 18;
	    std::cout << '\xd' << "Datos:" 
		      << std::setw(ancho) << miBuffer -> mayores[0] << " (" << maxPos[0] << ") "
		      << std::setw(ancho) << miBuffer -> mayores[1]  
		      << std::setw(ancho) << miBuffer -> mayores[2]  
		      << std::setw(ancho) << maxValue[0]
		      << std::flush;        

	    
#endif
	    /*

	    // Dump al altavoz
	    if (pa_simple_write(sOut, buf, sizeof(buf), &error) < 0) {
	      cerr << "ERROR al reproducir" << endl;
	    }

	    //*/
	    

	}


	if(!iniciado && salir){
	    return;
	    cout << "Cerrando archivo..." << endl;
	    F.close();
	}
    }

    
//*/
}
#if 0
#endif
