/*
 * main.cpp  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 */

#include <cr_section_macros.h>
#include "main.h"

void change_dir();

Timer t_mov(change_dir, Timer::SEG);

static volatile bool isUp = true;

void change_dir()
{
    if(isUp)
    {
        t_mov.SetTimer(10);
        motorPAP.setSteppDir(DriverStepper::ANTIHORARIO);
        isUp = false;
    }
    else 
    {
        t_mov.SetTimer(5);
        motorPAP.setSteppDir(DriverStepper::HORARIO);
        isUp = true;
    }
}

//La analogia es la siguiente:
//Si duro 5 segundos es horario
//Si duro 10 segundos es antihorario

int main( void )
{
    // ── Inicialización — NO modificar ────────────────────────────────────
    inicializacion();

    LED_ROJO.ClrPin();
    LED_AZUL.ClrPin();
    motorPAP.setTicks(10);
    motorPAP.setSteppDir(DriverStepper::HORARIO);

    motorPAP.startDriver();

    t_mov.TimerStart(5);

    // ── Loop principal ───────────────────────────────────────────────────
    while( 1 )
    {
        t_mov.TmrEvent();
    }

    return 0;
}
