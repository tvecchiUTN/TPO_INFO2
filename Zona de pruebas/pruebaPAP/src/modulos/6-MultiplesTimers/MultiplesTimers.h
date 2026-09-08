/*
 * MultiplesTimers.h  —  Informatica II  UTN-FRBA  2026
 */

#ifndef MULTIPLESTIMERS_H_
#define MULTIPLESTIMERS_H_

#include "main.h"

#define MAX_TIMERS  20

class MultiplesTimers {
private:
    Timer*   m_timers[MAX_TIMERS];
    uint8_t  m_count;
public:
    MultiplesTimers();
    MultiplesTimers& operator<<( Timer* t );
    MultiplesTimers& operator<<( Timer& t );
    void TmrEventosVencidos( void );
    virtual ~MultiplesTimers();
};

#endif /* MULTIPLESTIMERS_H_ */
