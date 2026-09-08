/*
 * main.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 */

#include <cr_section_macros.h>
#include "main.h"

int main( void )
{
    // ── Inicialización — NO modificar ────────────────────────────────────
    inicializacion();

    LED_ROJO.SetPin();
    // ── Loop principal ───────────────────────────────────────────────────
    while( 1 )
    {

        if(Rx_OPTICO.get())
        {
            LED_ROJO.ClrPin();
        }
        else
        {
        	LED_ROJO.SetPin();
        }

    }

    return 0;
}
