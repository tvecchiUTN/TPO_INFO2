/*
 * MultiplesTimers.cpp  —  Informatica II  UTN-FRBA  2026
 */

#include "main.h"

MultiplesTimers::MultiplesTimers()
{
    m_count = 0;
}

MultiplesTimers& MultiplesTimers::operator<<( Timer* t )
{
    if ( m_count < MAX_TIMERS ) {
        m_timers[ m_count ] = t;
        m_count++;
    }
    return *this;
}

MultiplesTimers& MultiplesTimers::operator<<( Timer& t )
{
    if ( m_count < MAX_TIMERS ) {
        m_timers[ m_count ] = &t;
        m_count++;
    }
    return *this;
}

void MultiplesTimers::TmrEventosVencidos( void )
{
    uint8_t i;
    for ( i = 0; i < m_count; i++ )
        m_timers[i]->TmrEvent();
}

MultiplesTimers::~MultiplesTimers()
{
}
