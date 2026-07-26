/*
 * Timer.cpp  —  Informatica II  UTN-FRBA  2026
 */

#include "main.h"

Timer::Timer()
{
    m_TmrRun     = 0;
    m_TmrEvent   = false;
    m_TmrHandler = nullptr;
    m_TmrStandBy = RUN;
    m_TmrBase    = DEC;
    AddPerifericoTemporizado( this );
}

Timer::Timer( const bases_t base )
{
    m_TmrRun     = 0;
    m_TmrEvent   = false;
    m_TmrHandler = nullptr;
    m_TmrStandBy = RUN;
    m_TmrBase    = base;
    AddPerifericoTemporizado( this );
}

Timer::Timer( const Timer_Handler_t handler, const bases_t base )
{
    m_TmrRun     = 0;
    m_TmrEvent   = false;
    m_TmrHandler = handler;
    m_TmrStandBy = RUN;
    m_TmrBase    = base;
    AddPerifericoTemporizado( this );
}

void Timer::TimerStart( uint32_t time, const Timer_Handler_t handler, const bases_t base )
{
    m_TmrBase    = base;
    m_TmrHandler = handler;
    switch ( base ) {
        case DEC: time *= DECIMAS;                        break;
        case SEG: time *= ( SEGUNDOS * DECIMAS );         break;
        case MIN: time *= ( MINUTOS * SEGUNDOS * DECIMAS ); break;
    }
    if ( time != 0 ) {
        m_TmrRun   = time;
        m_TmrEvent = false;
    } else {
        m_TmrRun   = 0;
        m_TmrEvent = true;
    }
}

void Timer::TimerStart( uint32_t time )
{
    switch ( m_TmrBase ) {
        case DEC: time *= DECIMAS;                        break;
        case SEG: time *= ( SEGUNDOS * DECIMAS );         break;
        case MIN: time *= ( MINUTOS * SEGUNDOS * DECIMAS ); break;
    }
    if ( time != 0 ) {
        m_TmrRun   = time;
        m_TmrEvent = false;
    } else {
        m_TmrRun   = 0;
        m_TmrEvent = true;
    }
}

void Timer::TimerStop( void )
{
    m_TmrRun     = 0;
    m_TmrEvent   = false;
    m_TmrHandler = nullptr;
    m_TmrStandBy = RUN;
}

void Timer::TimerPause( standby_t accion )
{
    m_TmrStandBy = accion;
}

void Timer::GetTimer( uint32_t &time ) const
{
    time = m_TmrRun;
    switch ( m_TmrBase ) {
        case DEC: time /= DECIMAS;                        break;
        case SEG: time /= ( SEGUNDOS * DECIMAS );         break;
        case MIN: time /= ( MINUTOS * SEGUNDOS * DECIMAS ); break;
    }
}

void Timer::SetTimer( uint32_t time )
{
    switch ( m_TmrBase ) {
        case DEC: time *= DECIMAS;                        break;
        case SEG: time *= ( SEGUNDOS * DECIMAS );         break;
        case MIN: time *= ( MINUTOS * SEGUNDOS * DECIMAS ); break;
    }
    m_TmrRun = time;
}

Timer& Timer::operator=( uint32_t time )
{
    switch ( m_TmrBase ) {
        case DEC: time *= DECIMAS;                        break;
        case SEG: time *= ( SEGUNDOS * DECIMAS );         break;
        case MIN: time *= ( MINUTOS * SEGUNDOS * DECIMAS ); break;
    }
    m_TmrRun   = time;
    m_TmrEvent = false;
    return *this;
}

bool Timer::operator==( uint32_t t )
{
    return ( (uint32_t)m_TmrRun == t );
}

bool operator==( uint32_t t, Timer &T )
{
    return ( (uint32_t)T.m_TmrEvent == t );
}

Timer::operator bool()
{
    return !m_TmrEvent;
}

void Timer::TmrEvent( void )
{
    if ( m_TmrEvent ) {
        m_TmrEvent = false;
        if ( m_TmrHandler != nullptr )
            m_TmrHandler();
    }
}

void Timer::HandlerDelPeriferico( void )
{
    if ( m_TmrRun ) {
        if ( !m_TmrStandBy ) {
            m_TmrRun--;
            if ( !m_TmrRun )
                m_TmrEvent = true;
        }
    }
}

Timer::~Timer()
{
}
