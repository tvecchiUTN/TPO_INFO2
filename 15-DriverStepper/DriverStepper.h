#ifndef __DRIVERSTEPPER_H
#define __DRIVERSTEPPER_H

#include "main.h"

class DriverStepper : public PerifericoTemporizado
{
private:
    Gpio m_ena;
    Gpio m_dir;
    Gpio m_pul;

    volatile uint32_t m_countTicks;

    volatile uint32_t m_waitTicks;

    volatile bool m_activateMove;

    Gpio::error_t m_error;

public:
    enum stepperDir_t
    {
        HORARIO,
        ANTIHORARIO,
    };

    DriverStepper(uint8_t portEna, uint8_t bitEna, uint8_t portDir, uint8_t bitDir, uint8_t portPul, uint8_t bitPul);

    Gpio::error_t getError() const;

    void HandlerDelPeriferico();

    void freeMove();

    void moveTicks(uint32_t waitTicks);

    void setSteppDir(stepperDir_t stepDir);

    void toogleSteppDir();

    void digitalStop();

    void enStart();

    void enStop();
};

#endif