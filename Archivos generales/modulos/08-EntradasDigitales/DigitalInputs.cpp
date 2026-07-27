/*
 * DigitalInputs.cpp  —  Informatica II  UTN-FRBA  2026
 */

#include "main.h"

DigitalInputs::DigitalInputs( uint8_t puerto, uint8_t bit, uint8_t modo,
                                uint8_t actividad, uint8_t MaxBounce )
    : Gpio( puerto, bit, modo, Gpio::INPUT, actividad ),
      m_MaxBounce( MaxBounce )
{
    m_CountBounce   = 0;
    m_BufferEntrada = GetPin();
    AddPerifericoTemporizado( this );
}

uint8_t DigitalInputs::get( void )
{
    return m_BufferEntrada;
}

void DigitalInputs::HandlerDelPeriferico( void )
{
    uint8_t lectura = GetPin();
    if ( lectura != m_BufferEntrada ) {
        m_CountBounce++;
        if ( m_CountBounce >= m_MaxBounce )
            m_BufferEntrada = !m_BufferEntrada;
    } else {
        m_CountBounce = 0;
    }
}

DigitalInputs::~DigitalInputs()
{
}
