#include "main.h"

/*
#define NVIC_SHIFT_PININT 24

static SensorHall* vec_sensores[8];

static void enableIntr(uint8_t numPININT)
{
    NVIC->ISER[0] = 1U << (NVIC_SHIFT_PININT + numPININT);
}

static void disableIntr(uint8_t numPININT)
{
    NVIC->ICER[0] = 1U << (NVIC_SHIFT_PININT + numPININT);
}

static void func_enablePININT0()
{
    enableIntr(vec_sensores[0]->getNumIntr());
}

static void func_enablePININT1()
{
    enableIntr(vec_sensores[1]->getNumIntr());
}

static void func_enablePININT2()
{
    enableIntr(vec_sensores[2]->getNumIntr());
}

static void func_enablePININT3()
{
    enableIntr(vec_sensores[3]->getNumIntr());
}

static void func_enablePININT4()
{
    enableIntr(vec_sensores[4]->getNumIntr());
}

static void func_enablePININT5()
{
    enableIntr(vec_sensores[5]->getNumIntr());
}

static void func_enablePININT6()
{
    enableIntr(vec_sensores[6]->getNumIntr());
}

static void func_enablePININT7()
{
    enableIntr(vec_sensores[7]->getNumIntr());
}

static void (*vec_funcsEnable[8]) (void) = {func_enablePININT0, func_enablePININT1, func_enablePININT2, func_enablePININT3, func_enablePININT4, func_enablePININT5, func_enablePININT6, func_enablePININT7};

SensorHall::SensorHall(uint8_t port, uint8_t bit, Gpio::activity_t activity, uint8_t numIntr, void(*callback)(void)) : m_inputSig(port, bit, Gpio::PULLUP, activity, 10), m_intr(numIntr, port, bit, IntExt::FLANCO, IntExt::DESCENDENTE_BAJO, nullptr), timeIntr(vec_funcsEnable[numIntr], Timer::DEC)
{
    m_logicState = 0;
    m_numIntr = numIntr;
    m_callback = callback;
    vec_sensores[m_numIntr] = this;
}
*/

SensorHall::SensorHall(uint8_t port, uint8_t bit, Gpio::activity_t activity) : m_inputSig(port, bit, Gpio::PULLUP, activity, 5)
{
    if(checkError(port, bit) == Gpio::ERROR)
    {
        m_error = Gpio::ERROR;
    }
}

uint8_t SensorHall::isMagnetic()
{
    if(m_error == Gpio::ERROR)
    {
        return Gpio::ERROR;
    }

    if(m_inputSig.get())
    {
        m_logicState = DETECTADO;
    }
    else
    {
        m_logicState = NO_DETECTADO;
    }

    return m_logicState;
}

Gpio::error_t SensorHall::getError() const
{
    return m_error;
}

/*
uint8_t SensorHall::getNumIntr() const
{
    return m_numIntr;
}

void SensorHall::PININT_SensHall()
{

}
*/