/*
 * PerifericoTemporizado.cpp  —  Informatica II  UTN-FRBA  2026
 */

#include "main.h"

// Definición e inicialización de miembros estáticos
PerifericoTemporizado* PerifericoTemporizado::m_perifericosTemporizados[N_PERIF_TEMPORIZADOS];
uint8_t                PerifericoTemporizado::m_countPerifericosTemporizados = 0;

PerifericoTemporizado::PerifericoTemporizado()
{
}

void PerifericoTemporizado::AddPerifericoTemporizado( PerifericoTemporizado* periferico )
{
    m_perifericosTemporizados[ m_countPerifericosTemporizados ] = periferico;
    m_countPerifericosTemporizados++;
}

PerifericoTemporizado::~PerifericoTemporizado()
{
}
