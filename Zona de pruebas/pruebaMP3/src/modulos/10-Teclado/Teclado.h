/*
 * Teclado.h
 *
 *  Created on: 21 sep. 2025
 *      Author: Gabriel
 */

#ifndef TECLADO_H_
#define TECLADO_H_

#include "main.h"

#define NO_KEY 0xFF
#define MAX_BOUNCES 4
#define DIVISOR_BARRIDO_TECLADO	30

class Teclado : public PerifericoTemporizado {
private:
	Gpio **m_ret;
	Gpio **m_scn;

	uint8_t m_TeclaAnterior ;
	uint8_t m_CantRebotes ;
	uint8_t m_BufferTeclado ;
	uint8_t m_MaxRebotes;
	int8_t m_MaxReturns;
	int8_t m_MaxScans;
	uint8_t m_ticks;

public:
	Teclado ( Gpio ** , Gpio **);
	void handlerDelPeriferico ( void );
	uint8_t GetKey( void );
	virtual ~Teclado();

private:
	uint8_t TecladoHW ( void );
	void TecladoSW ( uint8_t );

};

#endif /* TECLADO_H_ */
