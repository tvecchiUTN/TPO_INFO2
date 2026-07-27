/*
 * DigitalOutputs.h  —  Informatica II  UTN-FRBA  2026
 */

#ifndef DIGITALOUTPUTS_H_
#define DIGITALOUTPUTS_H_

#include "main.h"

class DigitalOutputs : protected Gpio, public PerifericoTemporizado {
private:
    uint8_t m_buffer;
public:
    DigitalOutputs( uint8_t puerto, uint8_t bit, uint8_t modo,
                    uint8_t actividad, uint8_t estado );
    int8_t  set( void );
    int8_t  clr( void );
    int8_t  toggle( void );
    DigitalOutputs& operator=( uint8_t estado );
    void HandlerDelPeriferico( void );
    virtual ~DigitalOutputs();
};

#endif /* DIGITALOUTPUTS_H_ */
