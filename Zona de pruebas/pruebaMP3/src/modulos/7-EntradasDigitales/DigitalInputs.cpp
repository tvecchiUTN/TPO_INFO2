/*
 * DigitalInputs.cpp
 *
 *  Created on: 29 jun. 2025
 *      Author: Gabriel
 */

#include "main.h"

DigitalInputs::DigitalInputs(uint8_t puerto, uint8_t bit, uint8_t modo, uint8_t actividad, uint8_t MaxBounce)
:Gpio(puerto, bit, modo, actividad, Gpio::INPUT), m_MaxBounce(MaxBounce){
	// TODO Auto-generated constructor stub
	m_CountBounce = 0;
	m_BufferEntrada = GetPin();
	pushCallback();
}

uint8_t DigitalInputs::get(void){
	return m_BufferEntrada;
}

void DigitalInputs::handlerDelPeriferico(void){
	uint8_t BufferEntradasInstantaneo = 0;
	BufferEntradasInstantaneo = GetPin();
	if(BufferEntradasInstantaneo != m_BufferEntrada){
		m_CountBounce++;
		if(m_CountBounce>= m_MaxBounce)
			m_BufferEntrada =  !m_BufferEntrada;
	}else
		m_CountBounce = 0;
}

DigitalInputs::~DigitalInputs() {
	// TODO Auto-generated destructor stub
}

