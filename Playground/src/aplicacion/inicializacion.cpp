/*
 * inicializacion.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 *
 * Instanciar aquí los objetos globales y completar inicializacion()
 * si fuera necesario.
 */

#include "main.h"

// ── Instanciación de objetos globales ─────────────────────────────────────
// (completar con los objetos del enunciado)
Gpio pulsador_0(0, 8, Gpio::PULLUP, Gpio::INPUT, Gpio::LOW);
Gpio pulsador_1(0, 9, Gpio::PULLUP, Gpio::INPUT, Gpio::LOW);
Gpio pulsador_2(0, 31, Gpio::PULLUP, Gpio::INPUT, Gpio::LOW);
Gpio pulsador_3(0, 30, Gpio::PULLUP, Gpio::INPUT, Gpio::LOW);

void inicializacion( void )
{
    inicOScilador();
    SysTick_InstalarCallback( MiFuncionSysTickCallback );
    Inicializar_SysTick( FREQ_SYSTICK );

    // (completar con inicializaciones adicionales si fuera necesario)
}
