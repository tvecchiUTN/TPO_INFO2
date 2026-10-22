#include "main.h"

#include "Lcd.h"
#include "Teclado.h"
#include "DriverStepper.h"
#include "DfPlayer.h"

#include "MdE_Ascensor.h"
#include "MdE_Comunicacion.h"

extern DfPlayer reproductor;
extern Lcd displayLCD;
extern Uart comPC;

// Trama que se envia
// Byte 0: Inicio de la trama; &
// Byte 1: Hacia donde apunta el mensaje; 0 para el ascensor, 1 para los pulsadores, 2 para la musica y 3 cuando inicio la COM
// Byte 2: Argumento: por ejemplo, el piso seleccionado o el comando para el MP3
// Byte 3: Fin de la trama; #

uint8_t msgTx[4];
uint8_t msgRx[4];

void prepareMsg(uint8_t *msg, uint8_t cmd, uint8_t arg)
{
    msg[0] = '&';
    msg[1] = cmd;
    msg[2] = arg;
    msg[3] = '#';
}

// Devuelve true si cumple con las especificaciones de protocolo
bool descifrarMsg(uint8_t *msg)
{
    if ((msg[0] != '&') || (msg[3] != '#'))
    {
        return false;
    }
    if (msg[1] > 3)
    {
        return false;
    }
    if (msg[1] == 1 && msg[2] > 3)
    {
        return false;
    }
    return true;
}

void estado_esperandoRx(ESTADOS_COMUNICACION &state)
{
    if (comPC.RxMensaje(msgRx, 4))
    {
        if (!descifrarMsg(msgRx))
        {
            prepareMsg(msgTx, 'E', 'R');
            comPC.Transmit(msgTx, 4);
        }
        else
        {
            switch (msgRx[1])
            {
            case PULSADORES:
                state = PARA_PULSADOR;
                break;

            case MUSICA:
                state = PARA_MP3;
                break;
            }
        }
    }
}

void estado_paraMP3(ESTADOS_COMUNICACION &state)
{
    switch (msgRx[2])
    {
    case PAUSAR:
        reproductor.pause();
        break;

    case REPRODUCIR:
        reproductor.play();
        break;

    case SIGUIENTE:
        reproductor.playNext();
        break;

    case ANTERIOR:
        reproductor.playPrev();
        break;
    }

    state = ESPERANDO_RX;
}

void estado_paraPulsador(ESTADOS_COMUNICACION &state)
{
    DESTINO = msgRx[2];
    state = ESPERANDO_RX;
}

void (*funcs_MdEAsc[])(ESTADOS_COMUNICACION &state) = {estado_esperandoRx, estado_paraMP3, estado_paraPulsador, nullptr};

void MdE_Comunicacion()
{
    static ESTADOS_COMUNICACION state = ESPERANDO_RX;

    if(funcs_MdEAsc[state])
    {
        funcs_MdEAsc[state] (state);
    }
}
