/*
 * oscilador.cpp
 *
 *  Created on: 26 mar. 2024
 *      Author: Gabriel
 */

#include <main.h>



/**
	\fn 		void inicOScilador(void)
	\brief 		Inicializa el oscilador del MCU
	\details 	Inicializa el oscilador del MCU para usar FRO a 30MHz
 	\param 		void
	\return 	void
*/
void inicOScilador(void){
	// 1-Asegura que FRO está encendido
	SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_FROOUT_PD_MASK;
	SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_FRO_PD_MASK;
	// 2-Se de frecuencia de FRO
	(*((void (*)(uint32_t freq))(CLOCK_FRO_SETTING_API_ROM_ADDRESS)))(30000);
	// 3-Elige FRO directo como salida de FRO la segunda y tercera instrucciones son necesarias para que el update del FRO tnega efecto
	SYSCON->FROOSCCTRL |= (1<<17);
	SYSCON->FRODIRECTCLKUEN &= ~(uint32_t)SYSCON_FRODIRECTCLKUEN_ENA_MASK;
	SYSCON->FRODIRECTCLKUEN |= (uint32_t)SYSCON_FRODIRECTCLKUEN_ENA_MASK;
	// 4-Se asegura que Main clk está encendido
	SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_SYSOSC_PD_MASK;
	// Elige System oscilator como clk externo
	SYSCON->EXTCLKSEL &= ~(uint32_t)SYSCON_EXTCLKSEL_SEL_MASK;
	// 5-Elige FRO como main clk
	SYSCON->MAINCLKSEL &= ~(uint32_t)SYSCON_MAINCLKPLLSEL_SEL_MASK;
	SYSCON->MAINCLKUEN &= ~(uint32_t)SYSCON_MAINCLKUEN_ENA_MASK;
	SYSCON->MAINCLKUEN |= (uint32_t)SYSCON_MAINCLKUEN_ENA_MASK;
	SYSCON->MAINCLKPLLSEL &= ~(uint32_t)SYSCON_MAINCLKPLLSEL_SEL_MASK;
	SYSCON->MAINCLKPLLUEN &= ~(uint32_t)SYSCON_MAINCLKPLLUEN_ENA_MASK;
	SYSCON->MAINCLKPLLUEN |= ~(uint32_t)SYSCON_MAINCLKPLLUEN_ENA_MASK;
	// 6-Setea el divisor de clock en 1
	SYSCON->SYSAHBCLKDIV = (uint32_t) 0x01;
}

