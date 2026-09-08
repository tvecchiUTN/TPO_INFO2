/*
 * PerifericoTemporizado.h
 *
 *  Created on: 8 jun. 2025
 *      Author: Gabriel
 */

#ifndef PERIFERICOTEMPORIZADO_H_
#define PERIFERICOTEMPORIZADO_H_

#include "main.h"

/*
 * Ojo que si los métodos virtuale puros no están definidos, cuando queremos hacer un objeto de el
 * siguiente error:
 * "undefined reference to 'vtable..."
 * AL definir los métodos virtuales agregando {}, el problema se resuelve
 *
 * **/

/*! \class PerifericoTemporizado PerifericoTemporizado.h
 *  \brief Clase que representa los perifericos que requieren un motor de timer para ser atendidos
 *
 *
 */
class PerifericoTemporizado
{
	private:
		void (*m_HandlerDelPeriferico)( void );

	public:
		PerifericoTemporizado(void (*CallBack)(void) = nullptr);

		static list <PerifericoTemporizado*> m_ListaDePerifericos;

		void pushCallback ( void );

		virtual void handlerDelPeriferico ( void );

		virtual ~PerifericoTemporizado( );
};



#endif /* PERIFERICOTEMPORIZADO_H_ */
