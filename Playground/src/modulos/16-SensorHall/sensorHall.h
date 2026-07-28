#ifndef __SENSORHALL_H
#define __SENSORHALL_H

#include "main.h"

#define NO_DETECTADO 0
#define DETECTADO 1

class SensorHall
{
private:
    DigitalInputs m_inputSig;
    //IntExt m_intr;
    //Timer timeIntr;

    volatile uint8_t m_logicState;
    //uint8_t m_numIntr;
    //void (*m_callback)(void);

public:
    //SensorHall(uint8_t port, uint8_t bit, Gpio::activity_t activity, uint8_t numIntr, void(*callback)(void));
    SensorHall(uint8_t port, uint8_t bit, Gpio::activity_t activity);
    uint8_t isActive();
    //void PININT_SensHall();
    //uint8_t getNumIntr() const;
};

#endif