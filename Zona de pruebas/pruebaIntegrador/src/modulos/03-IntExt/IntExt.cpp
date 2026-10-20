/*
 * IntExt.cpp
 *
 *  Created on: 7 sep. 2025
 *      Author: Gabriel
 */

#include "main.h"



static IntExt* g_intexts[8];

IntExt::IntExt(uint8_t pint, uint8_t port, uint8_t pin, bool tipoIE, polaridad_t polaridad, void (*callback)(void)){

	m_pint = pint;
	m_port = port;
	m_pin = pin;
	m_tipo = tipoIE;
	m_callback = callback;
	m_error = OK;

	if((m_pint > 7 ) || ( (m_port == 1) && (m_pin > 9)) || (m_port > 2) )
			m_error = ERROR;

	if(m_error == OK){
		SYSCON->PINTSEL[m_pint] = m_port*32 + m_pin;
		SYSCON->SYSAHBCLKCTRL0 |= (1 << SYSCON_SYSAHBCLKCTRL0_GPIOINT_SHIFT);

		if(m_tipo)
			set_nivel(polaridad);
		else
			set_flanco(polaridad);

		g_intexts[m_pint] = this;

		PINT->IST |= (1<<m_pint);
		NVIC->ISER[0] |= (1 << (NVIC_PININT0_BIT + m_pint));
	}
}



void IntExt::set_flanco(polaridad_t flanco){

	PINT->ISEL &= ~(1 << m_pint);//Selecciono FLANCO
	PINT->IENR &= ~(1 << m_pint);//Selecciono FLANCO
	PINT->IENF &= ~(1 << m_pint);//Selecciono FLANCO

	if((flanco == IntExt::ASCENDENTE_ALTO)||(flanco == IntExt::AMBOS_FLANCOS)){
		PINT->IENR |= (1 << m_pint);//FLANCO ascendente
	}
	else{
		PINT->IENF |= (1 << m_pint);//FLANCO descendente
		uint8_t Indice_PortPin ;
		if(m_port)
			Indice_PortPin = IOCON_INDEX_PIO1[m_pin];
		else
			Indice_PortPin = IOCON_INDEX_PIO0[m_pin];

		IOCON->PIO[ Indice_PortPin ] = ~0x18;
		IOCON->PIO[ Indice_PortPin ] = Gpio::PULLUP << 3;
	}

}

void IntExt::set_nivel(polaridad_t nivel){

	PINT->ISEL |= (1 << m_pint);
	PINT->IENR |= (1 << m_pint);
	PINT->IENF &= ~(1 << m_pint);
	PINT->IENF |= (nivel << m_pint);

}

void IntExt::PINT_IRQHandler(void){
	PINT->IST |= (1<<m_pint);
	if(m_callback)
		m_callback();
}

void PININT0_IRQHandler(void){
	g_intexts[0]->PINT_IRQHandler();
}



void PININT1_IRQHandler(void){
	g_intexts[1]->PINT_IRQHandler();
}

void PININT2_IRQHandler(void){
	g_intexts[2]->PINT_IRQHandler();
}

void PININT3_IRQHandler(void){
	g_intexts[3]->PINT_IRQHandler();
}

void PININT4_IRQHandler(void){
	g_intexts[4]->PINT_IRQHandler();
}

void PININT5_IRQHandler(void){
	g_intexts[5]->PINT_IRQHandler();
}



void PININT6_IRQHandler(void){
	g_intexts[6]->PINT_IRQHandler();
}

void PININT7_IRQHandler(void){
	g_intexts[7]->PINT_IRQHandler();
}

IntExt::~IntExt() {
	// TODO Auto-generated destructor stub
}

