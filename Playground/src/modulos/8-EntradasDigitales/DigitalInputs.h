/*
 * DigitalInputs.h  —  Informatica II  UTN-FRBA  2026
 */

#ifndef DIGITALINPUTS_H_
#define DIGITALINPUTS_H_

#include "main.h"

#define MAX_BOUNCE  10

class DigitalInputs : protected Gpio, public PerifericoTemporizado {
private:
    uint8_t m_BufferEntrada;
    uint8_t m_MaxBounce;
    uint8_t m_CountBounce;
public:
    DigitalInputs( uint8_t puerto, uint8_t bit, uint8_t modo,
                   uint8_t actividad, uint8_t MaxBounce = MAX_BOUNCE );
    uint8_t get( void );
    void HandlerDelPeriferico( void );
    virtual ~DigitalInputs();
};

#endif /* DIGITALINPUTS_H_ */
