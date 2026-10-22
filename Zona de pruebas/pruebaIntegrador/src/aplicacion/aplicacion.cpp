#include "main.h"

// ── Callback del SysTick — NO modificar ──────────────────────────────────
void MiFuncionSysTickCallback( void )
{
    uint8_t i;
    for ( i = 0; i < PerifericoTemporizado::m_countPerifericosTemporizados; i++ )
        PerifericoTemporizado::m_perifericosTemporizados[i]->HandlerDelPeriferico();
}