/*
 * inicializacion.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 *
 * Instanciar aquí los objetos globales y completar inicializacion()
 * si fuera necesario.
 */

#include "main.h"

// ── Instanciación de objetos globales ─────────────────────────────────────
// (completar con los objetos del enunciado)

DriverStepper motorPAP(0, 16, 0, 17, 0, 18);

Gpio LED_ROJO(1, 0, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);

Gpio LED_AZUL(1, 1, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);

void inicializacion( void )
{
    inicOScilador();
    SysTick_InstalarCallback( MiFuncionSysTickCallback );
    Inicializar_SysTick( FREQ_SYSTICK );

    // (completar con inicializaciones adicionales si fuera necesario)
}
