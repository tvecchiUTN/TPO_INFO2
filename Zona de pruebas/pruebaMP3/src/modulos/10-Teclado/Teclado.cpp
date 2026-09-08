/*
 * Teclado.cpp
 *
 *  Created on: 21 sep. 2025
 *      Author: Gabriel
 */

#include "Teclado.h"

Teclado::Teclado ( Gpio **r , Gpio **s = nullptr):m_ret(r),m_scn(s){
	// TODO Auto-generated constructor stub
	m_ticks = DIVISOR_BARRIDO_TECLADO;
		m_CantRebotes = 0;
		m_BufferTeclado = NO_KEY;
		m_MaxRebotes = MAX_BOUNCES;
		uint8_t i;


		if ( m_scn )
		{
			for (i = 0 ; m_scn[i] ; i++);
			m_MaxScans = i ;
		}

		for (i = 0 ; m_ret[i] ; i++);
		m_MaxReturns = i;


		pushCallback();
}

uint8_t Teclado::TecladoHW ( void ) {
	uint8_t j;
	if ( m_scn )
	{
		for ( uint8_t i = 0 ; i < m_MaxScans ; i++) {
			// Pongo todos en estado neutro
			for ( uint8_t j = 0 ; j < m_MaxScans ; j++ )
				m_scn[j]->SetPin() ;

			// Activo el pin a chequear
			m_scn[i]->ClrPin();

			for ( j = 0 ; j < m_MaxReturns ; j++) {
				if ( m_ret[j]->GetPin( ) )
					return j + i * m_MaxReturns ;
			}
		}
	}
	else {
		for ( uint8_t j = 0 ; j < m_MaxReturns ; j++) {
			if ( m_ret[j]->GetPin( ) )
				return j ;
		}
	}
	return NO_KEY;
}

uint8_t  Teclado::GetKey ( void )
{
	uint8_t key = m_BufferTeclado;

	m_BufferTeclado = NO_KEY;

	return key;
}

void Teclado::handlerDelPeriferico (void) {
	uint8_t  tecla;
	m_ticks--;
    if ( !m_ticks ){
    	m_ticks = DIVISOR_BARRIDO_TECLADO;
    	tecla = TecladoHW ( );
    	TecladoSW ( tecla );
    }
}

void Teclado::TecladoSW ( uint8_t TeclaActual ) {
	if (TeclaActual == NO_KEY ) {	//REPOSO
		m_CantRebotes = 0;
		m_TeclaAnterior= NO_KEY;
		return ;
	}

	if ( m_CantRebotes == 0 ) {
		 m_TeclaAnterior = TeclaActual;
		 m_CantRebotes ++;
		 return;
	}
	if ( TeclaActual == m_TeclaAnterior)	{
		if ( m_CantRebotes < m_MaxRebotes ){
			m_CantRebotes ++;
		return;
		}
		if (m_CantRebotes == m_MaxRebotes ) {
			m_BufferTeclado = TeclaActual;
			m_CantRebotes = MAX_BOUNCES;
			return;
		}
	}//				//PROTECCION
	else	{		//RESTABLEZCO CHEQUEO NUEVA TECLA
		m_CantRebotes = 0;
		m_TeclaAnterior = NO_KEY;
	}
	return ;
}


Teclado::~Teclado() {
	// TODO Auto-generated destructor stub
}

