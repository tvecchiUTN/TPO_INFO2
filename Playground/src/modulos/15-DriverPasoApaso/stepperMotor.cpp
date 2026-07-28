#include "main.h"

DriverStepper::DriverStepper(uint8_t portEna, uint8_t bitEna, uint8_t portDir, uint8_t bitDir, uint8_t portPul, uint8_t bitPul) : m_ena(portEna, bitEna, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH), m_dir(portDir, bitDir, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH), m_pul(portPul, bitPul, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH)
{
    //Queda prendido
    m_ena.ClrPin();

    //No lo enciendo, me aseguro que no se mueva
    m_pul.ClrPin();

    //Sentido horario
    m_dir.ClrPin();

    m_activateMove = false;

    m_countTicks = 0;
    m_waitTicks = 0;
    
    AddPerifericoTemporizado(this);
}

void DriverStepper::HandlerDelPeriferico()
{

    if(m_activateMove)
    {
    	if(!m_waitTicks)
    	{
    		m_pul.SetTogglePin();
    		return;
    	}
    	else if(m_countTicks >= m_waitTicks)
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
    m_activateMove = true;
    m_waitTicks = 0;
}

void DriverStepper::moveTicks(uint32_t waitMs)
{
    m_activateMove = true;
    m_waitTicks = waitMs;
}

void DriverStepper::setStepperDirection(stepperDir_t stepDir)
{
    if(stepDir == HORARIO)
    {
        m_dir.ClrPin();
        return;
    }
    else if(stepDir == ANTIHORARIO)
    {
        m_dir.SetPin();
    }
}    

void DriverStepper::stop()
{
    m_activateMove = false;
    m_pul.ClrPin();
}

void DriverStepper::enStart()
{
    m_ena.ClrPin();
}

void DriverStepper::enStop()
{
    m_ena.SetPin();
}
