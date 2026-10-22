#ifndef __MDE_ASCESENSOR_H
#define __MDE_ASCESENSOR_H

enum ESTADOS_ASCENSOR
{
    QUIETO,
    BAJAR,
    SUBIR
};

extern uint8_t DESTINO;
extern uint8_t PISO;

void MdE_Ascensor();

#endif
