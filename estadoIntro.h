#ifndef _ESTADOINTRO_H_
#define _ESTADOINTRO_H_

#include "estadoImagenFija.h"
#include "boost/scoped_ptr.hpp"

class EstadoIntro : public EstadoImagenFija{

public:
    EstadoIntro(Juego * p);
    void accionPosterior();
    ~EstadoIntro();
};

#endif /* _ESTADOINTRO_H_ */
