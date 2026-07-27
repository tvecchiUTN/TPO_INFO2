/*
 * inicializacion.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 *
 * Instanciar aquí los objetos globales y completar inicializacion()
 * si fuera necesario.
 */

#include "main.h"

// ── Instanciación de objetos globales ─────────────────────────────────────
// (completar con los objetos del enunciado)
Gpio SENSOR_HALL(0, 17, Gpio::PULLUP, Gpio::INPUT, Gpio::LOW);

void inicializacion( void )
{
    inicOScilador();
    SysTick_InstalarCallback( MiFuncionSysTickCallback );
    Inicializar_SysTick( FREQ_SYSTICK );

    // (completar con inicializaciones adicionales si fuera necesario)
}
