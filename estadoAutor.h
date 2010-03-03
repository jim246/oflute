#ifndef _ESTADOAUTOR_H_
#define _ESTADOAUTOR_H_

#include "estadoImagenFija.h"
#include "boost/scoped_ptr.hpp"

class estadoAutor : public estadoImagenFija{

public:
    estadoAutor(Juego * p);
    void accionPosterior();
};

#endif /* _ESTADOAUTOR_H_ */
