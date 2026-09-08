/*
 * Timer.cpp
 *
 *  Created on: 16 jun. 2025
 *      Author: Gabriel
 */

#include "main.h"




Timer::Timer() {
	// TODO Auto-generated constructor stub
	m_TmrRun = 0; m_TmrEvent = 0 ;
	m_TmrHandler = nullptr ;
	m_TmrStandBy = RUN; //0
	m_TmrBase = DEC; //0;
// Lo engancho en la lista
	pushCallback();
}

Timer::Timer(const bases_t base ){
	m_TmrRun = 0; m_TmrEvent = 0 ;
	m_TmrHandler = nullptr ;
	m_TmrStandBy = RUN; //0
	m_TmrBase = base;
// Lo engancho en la lista
	pushCallback();
}


Timer::Timer(const Timer_Handler_t handler, const bases_t base ) {
	m_TmrRun = 0; m_TmrEvent = 0 ;
	m_TmrHandler = handler ;
	m_TmrStandBy = RUN; //0
	m_TmrBase = base;
// Lo engancho en la lista
	pushCallback();
}

void Timer::TimerStart( uint32_t time, const Timer_Handler_t handler
													, const bases_t base ) {
    m_TmrBase = base;
	m_TmrHandler = handler;
	switch ( base ) {
	case DEC: time *= DECIMAS;  break;
	case SEG: time *= ( SEGUNDOS * DECIMAS );  break;
	case MIN: time *= ( MINUTOS * SEGUNDOS * DECIMAS );   break;
	}
	if( time != 0 )	 {  //el tiempo no es 0, lo cargo
		m_TmrRun = time;
		m_TmrEvent = false ;	 //programación “defensiva”. (me aseguro que sea cero)
     }
     else  {	//el tiempo es cero, el timer vence automáticamente
		m_TmrRun = 0;
		m_TmrEvent = true;
     }
	return ;
}

void Timer::TimerStart( uint32_t time )
{
    switch ( m_TmrBase ) {
		case DEC: time *= DECIMAS; break;
		case SEG: time *= ( SEGUNDOS * DECIMAS ); break;
		case MIN: time *= ( MINUTOS * SEGUNDOS * DECIMAS ); break;
    }
    if( time != 0 ) {	//el tiempo no es 0, lo cargo
		m_TmrRun = time;
		m_TmrEvent = false ;
    }
    else {	//el tiempo es cero, el timer vence automáticamente
		m_TmrRun = 0;
		m_TmrEvent = true;
    }
    return ;
}

void Timer::TimerStop( void ) {
	m_TmrRun = 0;
	m_TmrEvent = false ;
	m_TmrHandler = nullptr ;
	m_TmrStandBy = 0 ;
	m_TmrBase = 0;
	return ;
}

void Timer::TimerPause( standby_t accion ) {
	m_TmrStandBy = accion;
	return ;
}

void Timer::GetTimer( uint32_t &time ) const {
   time = m_TmrRun;
   switch ( m_TmrBase ) 	{
	case DEC:
	   time /= DECIMAS;
	   break;
	case SEG:
	   time /= ( SEGUNDOS * DECIMAS );
	   break;
	case MIN:
	   time /= ( MINUTOS * SEGUNDOS * DECIMAS );
	   break;
   }
   return ;
}

void Timer::SetTimer( uint32_t time ) {
   switch ( m_TmrBase ) 	{
	case DEC:
	   time *= DECIMAS; 	break;
	case SEG:
	   time *= ( SEGUNDOS * DECIMAS );
	   break;
	case MIN:
	   time *= ( MINUTOS * SEGUNDOS * DECIMAS );
	   break;
   }
   m_TmrRun = time;
   return ;
}

Timer& Timer::operator=( uint32_t time ) {
	switch ( m_TmrBase ) {
		case DEC:
			time *= DECIMAS; break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	m_TmrRun = time;
	m_TmrEvent = 0 ;
	//habría que considerar el caso del handler y la base
	return *this;
}

bool Timer::operator==( uint32_t t )  {
	if( (uint32_t) m_TmrRun == t ) {
		return  true;
	}
	return false;
}

bool operator==( uint32_t t , Timer &T  ) {
	if( (uint32_t) T.m_TmrEvent == t) {
		return  true;
	}
	return false;
}

Timer::operator bool ( void )
{
		return !m_TmrEvent;
}

void Timer::TmrEvent ( void ) {
	 if ( m_TmrEvent ) {
		 m_TmrEvent = 0 ;
		 m_TmrHandler();
	 }
 }

/**
	\fn void handlerDelPeriferico(void)
	\brief Decremento periodico del Timer. Debe ser llamada periodicamente con la base de tiempos
	\return void
*/
void Timer::handlerDelPeriferico( void )
{
	if( m_TmrRun )
	{
		if ( !m_TmrStandBy )
		{
			m_TmrRun--;
			if( !m_TmrRun )
				m_TmrEvent = true ;
		}
	}
}


Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

