/*
 * main.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 */

#include <cr_section_macros.h>
#include "main.h"

int main( void )
{
    // ── Inicialización — NO modificar ────────────────────────────────────
    inicializacion();

    pasoPaso.moveTicks(10);
    timePaso.TimerStart(5, funcTimer, Timer::SEG);

    // ── Loop principal ───────────────────────────────────────────────────
    while( 1 ) {

        // (implementar la lógica del enunciado)
    	timePaso.TmrEvent();

    }

    return 0;
}
