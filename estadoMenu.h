#ifndef _ESTADOMENU_H_
#define _ESTADOMENU_H_

#include "estado.h"
#include "customFont.h"

#include "boost/scoped_ptr.hpp"
#include <string>

class Juego;

/**
 * @class EstadoMenu
 * 
 * @brief Menú principal del juego.
 *
 * Controla la aparición de los botones, su pulsación y demás.
 */
class EstadoMenu : public Estado{
    bool lanzado;
    boost::scoped_ptr<Gosu::Image> imgFondo, btn1, btn2, btn3, btn4, btnUca;
    boost::scoped_ptr<customFont> miFuente;
    int estadoAnim;
    short alphaActual;
    unsigned long tiempoEsperaInicial;
    float posY[5]; //, posFinalesX[5];
public:
    /// Constructor. Crea un nuevo menú para el juego p.
    EstadoMenu(Juego * p);

    /// 
    void lanzar ();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    ~EstadoMenu();
};

#endif
