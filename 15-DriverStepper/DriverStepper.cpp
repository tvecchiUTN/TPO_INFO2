#include "main.h"

DriverStepper::DriverStepper(uint8_t portEna, uint8_t bitEna, uint8_t portDir, uint8_t bitDir, uint8_t portPul, uint8_t bitPul) : m_ena(portEna, bitEna, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH), m_dir(portDir, bitDir, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH), m_pul(portPul, bitPul, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH)
{
    if ((checkError(portEna, bitEna) == Gpio::ERROR) || (checkError(portDir, bitDir) == Gpio::ERROR) || (checkError(portPul, bitPul) == Gpio::ERROR))
    {
        m_error = Gpio::ERROR;
        return;
    }

    // Queda prendido
    m_ena.ClrPin();

    // No lo enciendo, me aseguro que no se mueva
    m_pul.ClrPin();

    // Sentido horario
    m_dir.ClrPin();

    m_activateMove = false;

    m_countTicks = 0;
    m_waitTicks = 0;

    AddPerifericoTemporizado(this);
}

Gpio::error_t DriverStepper::getError() const
{
    return m_error;
}

void DriverStepper::HandlerDelPeriferico()
{
    if (m_activateMove)
    {
        if (m_countTicks >= m_waitTicks)
        {
            m_pul.SetPin();
            m_countTicks = 0;
            return;
        }
        m_pul.ClrPin();
        m_countTicks++;
    }
}

void DriverStepper::freeMove()
{
    if (m_error != Gpio::ERROR)
    {
        m_activateMove = true;
        m_waitTicks = 0;
    }
}

void DriverStepper::moveTicks(uint32_t waitMs)
{
    if (m_error != Gpio::ERROR)
    {
        m_activateMove = true;
        m_waitTicks = waitMs;
    }
}

void DriverStepper::setSteppDir(stepperDir_t stepDir)
{
    if (m_error != Gpio::ERROR)
    {
        if (stepDir == HORARIO)
        {
            m_dir.ClrPin();
        }
        else if (stepDir == ANTIHORARIO)
        {
            m_dir.SetPin();
        }
    }
}

void DriverStepper::toogleSteppDir()
{
    if (m_error != Gpio::ERROR)
    {
        m_dir.SetTogglePin();
    }
}

void DriverStepper::digitalStop()
{
    if (m_error != Gpio::ERROR)
    {
        m_activateMove = false;
        m_pul.ClrPin();
    }
}

void DriverStepper::enStart()
{
    if (m_error != Gpio::ERROR)
    {
        m_activateMove = true;
        m_ena.ClrPin();
    }
}

void DriverStepper::enStop()
{
    if (m_error != Gpio::ERROR)
    {
        m_activateMove = false;
        m_ena.SetPin();
    }
}