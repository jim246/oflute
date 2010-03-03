#ifndef _ESTADOINTRO_H_
#define _ESTADOINTRO_H_

#include "estadoImagenFija.h"
#include "boost/scoped_ptr.hpp"

class estadoIntro : public estadoImagenFija{

public:
    estadoIntro(Juego * p, Gosu::Graphics * graphics);
    void accionPosterior();
};

#endif /* _ESTADOINTRO_H_ */
