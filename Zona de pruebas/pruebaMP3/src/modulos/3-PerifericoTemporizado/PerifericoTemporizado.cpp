/*
 * PerifericoTemporizado.cpp
 *
 *  Created on: 8 jun. 2025
 *      Author: Gabriel
 */

#include "main.h"


/**
	\fn 		PerifericoTemporizado(void(*Callback)(void))
	\brief 		Función constructor de clase PerifericoTemporizado
 	\details 	Crea objeto de clase PerifericoTemporizado, recibe callback y lo encola
 	\param 		void(*Callback)(void): puntero a función callback
	\return 	void
*/
list <PerifericoTemporizado*> PerifericoTemporizado::m_ListaDePerifericos;

PerifericoTemporizado::PerifericoTemporizado( void (*CallBack) (void) ):m_HandlerDelPeriferico(CallBack)
{

	if ( m_HandlerDelPeriferico )
			pushCallback();
}

PerifericoTemporizado::~PerifericoTemporizado() {
}

void PerifericoTemporizado::handlerDelPeriferico (void)
{
	if ( m_HandlerDelPeriferico )
		m_HandlerDelPeriferico();
}

void PerifericoTemporizado::pushCallback (void)
{
	m_ListaDePerifericos.push_back( this );
}



