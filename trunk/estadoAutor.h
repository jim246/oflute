#ifndef _ESTADOAUTOR_H_
#define _ESTADOAUTOR_H_

#include "estadoImagenFija.h"
#include "boost/scoped_ptr.hpp"

class EstadoAutor : public EstadoImagenFija{

public:
    EstadoAutor(Juego * p);
    void accionPosterior();
    ~EstadoAutor();
};

#endif /* _ESTADOAUTOR_H_ */
