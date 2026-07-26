/*
 * DigitalOutputs.cpp  —  Informatica II  UTN-FRBA  2026
 */

#include "main.h"

DigitalOutputs::DigitalOutputs( uint8_t puerto, uint8_t bit, uint8_t modo,
                                  uint8_t actividad, uint8_t estado )
    : Gpio( puerto, bit, modo, Gpio::OUTPUT, actividad )
{
    m_buffer = estado;
    AddPerifericoTemporizado( this );
}

int8_t DigitalOutputs::set( void )
{
    m_buffer = Gpio::ON;
    return m_error;
}

int8_t DigitalOutputs::clr( void )
{
    m_buffer = Gpio::OFF;
    return m_error;
}

int8_t DigitalOutputs::toggle( void )
{
    m_buffer = ( m_buffer == Gpio::ON ) ? Gpio::OFF : Gpio::ON;
    return m_error;
}

DigitalOutputs& DigitalOutputs::operator=( uint8_t estado )
{
    m_buffer = estado;
    return *this;
}

void DigitalOutputs::HandlerDelPeriferico( void )
{
    if ( m_buffer )
        SetPin();
    else
        ClrPin();
}

DigitalOutputs::~DigitalOutputs()
{
}
