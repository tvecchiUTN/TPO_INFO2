/*
 * PerifericoTemporizado.h  —  Informatica II  UTN-FRBA  2026
 */

#ifndef PERIFERICOTEMPORIZADO_H_
#define PERIFERICOTEMPORIZADO_H_

#include "main.h"

#define N_PERIF_TEMPORIZADOS  50

class PerifericoTemporizado
{
public:
    static PerifericoTemporizado* m_perifericosTemporizados[N_PERIF_TEMPORIZADOS];
    static uint8_t                m_countPerifericosTemporizados;

    void AddPerifericoTemporizado( PerifericoTemporizado* periferico );

    virtual void HandlerDelPeriferico( void ) = 0;

    PerifericoTemporizado();
    virtual ~PerifericoTemporizado();
};

#endif /* PERIFERICOTEMPORIZADO_H_ */
