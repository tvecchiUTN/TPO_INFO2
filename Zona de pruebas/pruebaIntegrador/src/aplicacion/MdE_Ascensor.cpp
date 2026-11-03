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

#define ASCENSOR_BAJAR pasoApaso.setSteppDir(DriverStepper::HORARIO); //Defino bajar como horario

#define ASCENSOR_SUBIR pasoApaso.setSteppDir(DriverStepper::ANTIHORARIO); //Defino subir como antihorario

volatile uint8_t DESTINO = 0; //Destino del ascensor, cambia al presionar una tecla con el matricial o con QT
volatile uint8_t PISO = 0; //Piso actual del ascensor

volatile bool huboCambio = false; //Variable para mostrar cambios. Se se ha leido, cambiar a false

void estado_quieto(ESTADOS_ASCENSOR &state) //Estado en reposo o ascensor quieto
{
    if (PISO == DESTINO) //Verificacion de piso actual y destino
    {
        pasoApaso.stopDriver(); //Detengo la cabina
    }

    if (OpticoPB.get()) //Sensor PB detectado
    {
        PISO = 0; //Estoy en piso 0
        huboCambio = true; //Hubo cambios
    }
    else if (OpticoP1.get())
    {
        PISO = 1; //Estoy en piso 1
        huboCambio = true; //Hubo cambios
    }
    else if (OpticoP2.get())
    {
        PISO = 2; //Estoy en piso 2
        huboCambio = true; //Hubo cambios
    }
    else if (OpticoP3.get())
    {
        PISO = 3; //Estoy en piso 3
        huboCambio = true; //Hubo cambios
    }

    uint8_t tecla = teclado.GetKey(); //Variable tecla matricial
    if (tecla != NO_KEY && tecla < MAX_PISOS) //Si se presiono una tecla y es menor a 4
    {
        DESTINO = tecla; //El destino es la tecla presionada
        huboCambio = true; //Hubo cambios
    }

    if (PISO > DESTINO) //EL piso actual es mayor al destino
    {
        ASCENSOR_BAJAR //Desciendo
        pasoApaso.startDriver(); //Inicio motor
        state = BAJAR; //Estoy bajando
    }
    else if (PISO < DESTINO) //EL piso actual es menor al destino
    {
        ASCENSOR_SUBIR //Subo
        pasoApaso.startDriver(); //Inicio motor
        state = SUBIR; //Estoy subiendos
    }

    // SISTEMA DE SEGURIDAD PARA NO EXCEDERSE
    if ((PISO == (MAX_PISOS - 1)) || (PISO == 0))
    {
        pasoApaso.stopDriver();
    }
}

void estado_subir_bajar(ESTADOS_ASCENSOR &state) //Estado de ascensor bajando o subiendo
{
    if (OpticoPB.get() || OpticoP1.get() || OpticoP2.get() || OpticoP3.get()) //Si detecte cualquier sensor
    {
        state = QUIETO; //Paso al estado queiro para verificar estado
    }
}

//Array de funciones estado, reciben una referencia para modificar el estado de la MdE
void (*funcs_MdECom[])(ESTADOS_ASCENSOR &estado) = {estado_quieto, estado_subir_bajar, estado_subir_bajar, nullptr}; 

//Maquina de estados del ascensor
void MdE_Ascensor()
{
    static ESTADOS_ASCENSOR state = QUIETO; //Inicio en QUIETO

    if(funcs_MdECom[state])
    {
        funcs_MdECom[state](state);
    }
}
