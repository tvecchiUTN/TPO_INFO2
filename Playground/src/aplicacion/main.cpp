/*
 * main.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 */

#include <cr_section_macros.h>
#include "main.h"
//#include "inicializacion.h"

int main( void )
{
    // ── Inicialización — NO modificar ────────────────────────────────────
    inicializacion();
    // ── Loop principal ───────────────────────────────────────────────────
    uint8_t goToFlour = 0;

    while( 1 ) 
    {
        if(pulsador_0.GetPin())
        {
            goToFlour = 0;
        }
        else if(pulsador_1.GetPin())
        {
            goToFlour = 1;
        }
        else if(pulsador_2.GetPin())
        {
            goToFlour = 2;
        }
        else if(pulsador_3.GetPin())
        {
            goToFlour = 3;
        }

        if(goToFlour == 3)
        {

        }
    }   

    return 0;
}
