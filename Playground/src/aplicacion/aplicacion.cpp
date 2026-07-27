/*
 * aplicacion.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 *
 * Implementar aquí la lógica de la aplicación:
 * callbacks de timers, eventos de botones, etc.
 */

#include "main.h"

// ── Callback del SysTick — NO modificar ──────────────────────────────────
void MiFuncionSysTickCallback( void )
{
    uint8_t i;
    for ( i = 0; i < PerifericoTemporizado::m_countPerifericosTemporizados; i++ )
        PerifericoTemporizado::m_perifericosTemporizados[i]->HandlerDelPeriferico();
}

// ── Funciones de la aplicación ────────────────────────────────────────────
// (implementar aquí los callbacks y la lógica pedida por el enunciado)

void funcTimer()
{
    static bool isHorario = true;

    if(isHorario)
    {
        pasoPaso.setStepperDirection(DriverStepper::HORARIO);
        isHorario = false;
        timePaso.SetTimer(5);
        return;
    }

    pasoPaso.setStepperDirection(DriverStepper::ANTIHORARIO);
    isHorario = true;
    timePaso.SetTimer(5);
}
