/**
 * @file stepperMotor.h
 * @brief Abstracción para el control de motor paso a paso mediante driver TB6600.
 * @details Esta clase permite controlar el sentido, movimiento y parada de un motor
 *          stepper utilizando tres señales digitales (ENA, DIR, PUL). Al heredar de
 *          PerifericoTemporizado, la generación de pulsos se realiza de manera 
 *          no bloqueante mediante el temporizador del sistema (SysTick).
 * @date 2026
 * @author Grupo Proyecto Ascensor - Informática II (UTN FRBA)
 */

#ifndef __STEPPERMOTOR_H
#define __STEPPERMOTOR_H

#include "main.h"

/**
 * @class DriverStepper
 * @brief Clase para el control de un motor paso a paso con el driver industrial TB6600.
 */
class DriverStepper : public PerifericoTemporizado
{
private:
    Gpio m_ena;                 /**< Pin de habilitación del driver (Enable) */
    Gpio m_dir;                 /**< Pin de sentido de giro (Direction) */
    Gpio m_pul;                 /**< Pin de tren de pulsos para el avance (Pulse) */

    volatile bool m_activateMove; /**< Flag de control de movimiento. Volatile por compartirse con interrupción/handler */

public:
    /**
     * @enum stepperDir_t
     * @brief Define los sentidos de giro posibles para el motor.
     */
    enum stepperDir_t
    {
        HORARIO,      /**< Sentido de giro horario */
        ANTIHORARIO,  /**< Sentido de giro antihorario */
    };

    /**
     * @brief Constructor de la clase DriverStepper.
     * @details Inicializa los pines GPIO como salidas Push-Pull y registra el objeto 
     *          en el *scheduler* de periféricos temporizados de la cátedra.
     * @param portEna Puerto del pin Enable (0 o 1).
     * @param bitEna  Bit del pin Enable.
     * @param portDir Puerto del pin Direction (0 o 1).
     * @param bitDir  Bit del pin Direction.
     * @param portPul Puerto del pin Pulse (0 o 1).
     * @param bitPul  Bit del pin Pulse.
     */
    DriverStepper(uint8_t portEna, uint8_t bitEna, uint8_t portDir, uint8_t bitDir, uint8_t portPul, uint8_t bitPul);

    /**
     * @brief Handler periódico del periférico.
     * @details Este método es invocado periódicamente por el sistema (dentro del SysTick
     *          o barrido principal). Si el movimiento está activado, cambia de estado
     *          el pin PUL (Toggle) para generar el tren de pulsos que mueve el motor.
     */
    void HandlerDelPeriferico();

    /**
     * @brief Inicia el movimiento libre y continuo del motor.
     * @details Activa el flag interno para que el handler periódico comience a enviar pulsos.
     */
    void freeMove();

    /**
     * @brief Establece la dirección de giro del motor.
     * @param stepDir Sentido deseado (HORARIO o ANTIHORARIO).
     */
    void setStepperDirection(stepperDir_t stepDir);

    /**
     * @brief Detiene el movimiento del motor preservando el torque.
     * @details Cesa la emisión de pulsos (PUL) pero mantiene el driver habilitado, 
     *          frenando el eje e impidiendo que se mueva libremente por peso o inercia.
     */
    void stop();

    /**
     * @brief Deshabilita o actúa sobre la señal de Enable (ENA) del driver.
     * @details Permite controlar la energía de las bobinas del motor.
     */
    void enStop();
};

#endif // __STEPPERMOTOR_H