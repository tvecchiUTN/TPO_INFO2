/*
 * main.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 */

#include <cr_section_macros.h>
#include "main.h"

int main( void )
{
    // ── Inicialización — NO modificar ────────────────────────────────────
    inicializacion();
    // ── Loop principal ───────────────────────────────────────────────────
    tmr_led.TimerStart(1);

    volatile bool test = false;
    while( 1 ) 
    {
        
        if(rx.GetPin())
        {
            test = true;
        }

        if(test)
        {
        	test = false;    
        }
        
        tmr_led.TmrEvent();

    }   

    return 0;
}
