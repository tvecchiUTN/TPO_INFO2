/*
 * IntExt.h
 *
 *  Created on: 7 sep. 2025
 *      Author: Gabriel
 */

#ifndef INTEXT_H_
#define INTEXT_H_

#include "main.h"

#if defined (__cplusplus)
extern "C"{
	void PININT0_IRQHandler();
	void PININT1_IRQHandler();
	void PININT2_IRQHandler();
	void PININT3_IRQHandler();
	void PININT4_IRQHandler();
	void PININT5_IRQHandler();
	void PININT6_IRQHandler();
	void PININT7_IRQHandler();
}
#endif


class IntExt {
public:
	enum tipoIE_t {FLANCO = 0, NIVEL};
	enum polaridad_t{ASCENDENTE_ALTO = 0, DESCENDENTE_BAJO, AMBOS_FLANCOS};
	enum error_t	{ ERROR = 2 , OK };
	IntExt(uint8_t, uint8_t, uint8_t, bool, polaridad_t, void (*)(void));
	void PINT_IRQHandler(void);
	virtual ~IntExt();
private:
	uint8_t m_pint;
	uint8_t m_port;
	uint8_t m_pin;
	uint8_t m_error;
	void (*m_callback) (void);
	bool m_tipo;
	void set_flanco(polaridad_t);
	void set_nivel(polaridad_t);
};

#endif /* INTEXT_H_ */
