/*
 * Timer.h  —  Informatica II  UTN-FRBA  2026
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "main.h"

typedef void (*Timer_Handler_t)(void);

class Timer : public PerifericoTemporizado {
protected:
    volatile uint32_t   m_TmrRun;
    volatile bool       m_TmrEvent;
    void              (*m_TmrHandler)(void);
    volatile bool       m_TmrStandBy;
    volatile uint8_t    m_TmrBase;

public:
    enum bases_t        { DEC, SEG, MIN };
    enum ticks_t        { DECIMAS = 100, SEGUNDOS = 10, MINUTOS = 60 };
    enum erroresTimers_t{ errorTimer, OKtimers };
    enum standby_t      { RUN, PAUSE };

    Timer();
    Timer( const Timer_Handler_t handler, const bases_t base );
    Timer( const bases_t base );

    void    TimerStart( uint32_t time, const Timer_Handler_t handler, const bases_t base );
    void    TimerStart( uint32_t time );
    void    SetTimer( uint32_t time );
    void    GetTimer( uint32_t &time ) const;
    void    TimerPause( const standby_t accion );
    void    TimerStop( void );
    void    TmrEvent( void );

    Timer&  operator=( uint32_t t );
    bool    operator==( uint32_t t );
    friend bool operator==( uint32_t t, Timer &T );
    explicit operator bool();

    void    HandlerDelPeriferico( void );
    virtual ~Timer();
};

#endif /* TIMER_H_ */
