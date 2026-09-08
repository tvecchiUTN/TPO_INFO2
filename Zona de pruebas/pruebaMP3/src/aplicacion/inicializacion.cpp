/*
 * inicializacion.cpp
 *
 *  Created on: 7 ago. 2025
 *      Author: Gabriel
 */

#include "main.h"


void inicializacion(void){
	inicOScilador();
	SysTick_InstalarCallback(MiFuncionSysTickCallback);
	Inicializar_SysTick(FREQ_SYSTICK);
}
