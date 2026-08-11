/*
 * inicializacion.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 *
 * Instanciar aquí los objetos globales y completar inicializacion()
 * si fuera necesario.
 */

#include "main.h"

// ── Instanciación de objetos globales ─────────────────────────────────────
// (completar con los objetos del enunciado)
DriverStepper pap(0, 0, 0, 17, 0, 18);

Gpio rx(0, 17, Gpio::PULLUP, Gpio::INPUT, Gpio::LOW);
Gpio tx(0, 18, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH);

Timer tmr_led(func_tmr_led, Timer::DEC);

void inicializacion( void )
{
    inicOScilador();
    SysTick_InstalarCallback( MiFuncionSysTickCallback );
    Inicializar_SysTick( FREQ_SYSTICK );

    // (completar con inicializaciones adicionales si fuera necesario)
}
