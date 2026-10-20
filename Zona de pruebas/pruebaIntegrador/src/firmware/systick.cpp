/*
 * systick.cpp
 *
 *  Created on: 16 abr. 2024
 *      Author: Gabriel
 */


#include <main.h>



/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define MAX_TICKS 	0xffffff

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** OBJETOS GLOBALES PUBLICOS
 *********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
volatile void (* pf_sysTickCallback)(void) = nullptr;


void SysTick_InstalarCallback (void (*MiFuncionCallback)(void)) {
	pf_sysTickCallback = (volatile void (*)(void)) MiFuncionCallback;
}


/**
	\fn 		void SysTick_Handler(void)
	\brief 		Handler de interrupcion del sytick
	\details 	Handler de interrupcion del sytick, llama al callback del systick si este esta instalado
 	\param 		void
	\return 	void
*/
void SysTick_Handler(void)
{
	if(pf_sysTickCallback)
			pf_sysTickCallback();

}


/**
	\fn 		uint32_t Inicializar_SysTick( uint32_t ms )
	\brief 		Funcion que inicializa el systick
	\details 	Funcion que inicializa el systick, recibe el tiempo de tick en ms
 	\param 		uint32_t ms: tiempo de interrupcion de systick en ms
	\return 	uint32_t: 0 si todo ok / 1 si la configuracion excede el tiempo maximo
*/
uint32_t Inicializar_SysTick( uint32_t ms )
{
	uint32_t clock_ticks;

	clock_ticks = (FREQ_CLOCK/1000);  		// ticks = Tsystic / Tclock ;

	if (clock_ticks > MAX_TICKS)
		return 1UL ;          		//* Reload value fuera de rango

	SysTick->RELOAD = (uint32_t)(clock_ticks - 1);  	//* Cargamos la Cuenta

	SysTick->CURR = 0;   			//* SysTick Counter en 0 para que se recargue

	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;	// ENABLE = 1, TICKINT = 1, CLKSOURCE = 1;

	return 0UL;
}


