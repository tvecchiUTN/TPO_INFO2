/*
 * DigitalInputs.h
 *
 *  Created on: 29 jun. 2025
 *      Author: Gabriel
 */

#ifndef DIGITALINPUTS_H_
#define DIGITALINPUTS_H_

#define MAX_BOUNCE 30

#include "main.h"



class DigitalInputs:protected Gpio, public PerifericoTemporizado {
private:
	uint8_t m_BufferEntrada;
	uint8_t m_MaxBounce;
	uint8_t m_CountBounce;
public:
	DigitalInputs(uint8_t puerto, uint8_t bit, uint8_t modo, uint8_t actividad, uint8_t MaxBounce = MAX_BOUNCE);
	uint8_t get(void);
	void handlerDelPeriferico(void);
	virtual ~DigitalInputs();
};

#endif /* DIGITALINPUTS_H_ */
