#include "main.h"
#include "Lcd.h"
#include "Teclado.h"
#include "DriverStepper.h"
#include "DfPlayer.h"

#include "MdE_Ascensor.h"

extern DigitalInputs OpticoPB;
extern DigitalInputs OpticoP1;
extern DigitalInputs OpticoP2;
extern DigitalInputs OpticoP3;

extern DriverStepper pasoApaso;

extern Teclado teclado;

#define ASCENSOR_BAJAR pasoApaso.setSteppDir(DriverStepper::HORARIO);

#define ASCENSOR_SUBIR pasoApaso.setSteppDir(DriverStepper::ANTIHORARIO);

uint8_t DESTINO = 0;
uint8_t PISO = 0;

void estado_quieto(ESTADOS_ASCENSOR &state)
{
    if (PISO == DESTINO)
    {
        pasoApaso.stopDriver();
    }

    if (OpticoPB.get())
    {
        PISO = 0;
    }
    else if (OpticoP1.get())
    {
        PISO = 1;
    }
    else if (OpticoP2.get())
    {
        PISO = 2;
    }
    else if (OpticoP3.get())
    {
        PISO = 3;
    }

    uint8_t tecla = teclado.GetKey();
    if (tecla != NO_KEY && tecla < MAX_PISOS)
    {
        DESTINO = tecla;
    }

    if (PISO > DESTINO)
    {
        ASCENSOR_BAJAR
        pasoApaso.startDriver();
        state = BAJAR;
    }
    else if (PISO < DESTINO)
    {
        ASCENSOR_SUBIR
        pasoApaso.startDriver();
        state = SUBIR;
    }

    // SISTEMA DE SEGURIDAD PARA NO EXCEDERSE
    if ((PISO == (MAX_PISOS - 1)) || (PISO == 0))
    {
        pasoApaso.stopDriver();
    }
}

void estado_subir_bajar(ESTADOS_ASCENSOR &state)
{
    if (OpticoPB.get() || OpticoP1.get() || OpticoP2.get() || OpticoP3.get())
    {
        state = QUIETO;
    }
}

void (*funcs_MdECom[])(ESTADOS_ASCENSOR &estado) = {estado_quieto, estado_subir_bajar, estado_subir_bajar, nullptr};

void MdE_Ascensor()
{
    static ESTADOS_ASCENSOR state = QUIETO;

    if(funcs_MdECom[state])
    {
        funcs_MdECom[state](state);
    }
}
