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

Gpio::error_t checkError(uint8_t port, uint8_t bit)
{
    if((port > 1) || (bit > 31) || ((port == 1) && (bit > 9)))
    {
        return Gpio::ERROR;
    }
}

// ── Funciones de la aplicación ────────────────────────────────────────────
// (implementar aquí los callbacks y la lógica pedida por el enunciado)

