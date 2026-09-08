/*
 * DigitalOutputs.cpp
 *
 *  Created on: 29 jun. 2025
 *      Author: Gabriel
 */

#include "main.h"

DigitalOutputs::DigitalOutputs(uint8_t puerto, uint8_t bit, uint8_t modo, uint8_t actividad, uint8_t estado)
:Gpio(puerto,bit,modo,Gpio::OUTPUT,actividad){
	// TODO Auto-generated constructor stub
	m_buffer = estado;
	pushCallback();

}

int8_t DigitalOutputs::set(void){
	m_buffer = ON;
	return m_error;
}

int8_t DigitalOutputs::clr(void){
	m_buffer = OFF;
	return m_error;
}

int8_t DigitalOutputs::toggle(void){
	if(m_buffer == ON)
		m_buffer = OFF;
	else
		m_buffer = ON;

	return m_error;
}

DigitalOutputs& DigitalOutputs::operator= (uint8_t estado){
	m_buffer = estado;
	return *this;
}

void DigitalOutputs::handlerDelPeriferico ( void )
{
	if ( m_buffer )
		SetPin( );
	else
		ClrPin( );
}


DigitalOutputs::~DigitalOutputs() {
	// TODO Auto-generated destructor stub
}

