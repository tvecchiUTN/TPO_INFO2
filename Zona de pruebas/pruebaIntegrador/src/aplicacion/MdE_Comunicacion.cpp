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

extern volatile bool huboCambio;
extern volatile uint8_t DESTINO;
extern volatile uint8_t PISO;

#define COMANDO_INICIO 0 //Comando utilizado al transmitir indicando que me quiero comunicar con la PC

// Trama que se envia
// Byte 0: Inicio de la trama; &
// Byte 1: Hacia donde apunta el mensaje; 0 para el ascensor, 1 para los pulsadores, 2 para la musica
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
    if ((msg[0] != '&') || (msg[3] != '#')) //Verificacion de inicio y fin
    {
        return false;
    }
    if ((msg[1] > '3') && ((msg[1] < '0'))) //Verificacion de comando
    {
        return false;
    }
    if ((msg[1] == '1') && (msg[2] > '3')) //Verificacion de parametro
    {
        return false;
    }
    return true;
}

void estado_esperandoRx(ESTADOS_COMUNICACION &state) //Estado esperando del protocolo de comunicacion
{
    if (comPC.RxMensaje(msgRx, 4)) //Si recibi un mensaje de 4 bytes
    {
        if (!descifrarMsg(msgRx)) //Si el mensaje cumple con el protocolo de mensaje
        {
            prepareMsg(msgTx, 'E', 'R'); //Si no cumplio, envio un mensaje de error, para enviar devuelta o descartar
            comPC.Transmit(msgTx, 4); //Lo envio
        }
        else
        {
            switch (msgRx[1]-'0') //Verifico que fue el comando, si fue un pulsador o la musica
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

    if(huboCambio) //Si hubo cambios
    {
        huboCambio = false;
        state = ENVIAR_DATOS;
    }
}

void estado_paraMP3(ESTADOS_COMUNICACION &state)
{
    switch (msgRx[2]) //Veo el parametro recibido del mensaje
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

void estado_paraPulsador(ESTADOS_COMUNICACION &state) //Establezco el valor de destino hecho por los pulsadores de Qt
{
    DESTINO = msgRx[2]-'0';
    state = ESPERANDO_RX;
}

void estado_enviarDatos(ESTADOS_COMUNICACION &state) //Envio el estado actual del ascensor
{
    prepareMsg(msgTx, PISO, DESTINO);

    comPC.Transmit(msgTx, sizeof(msgTx));

    state = ESPERANDO_RX;
}

void (*funcs_MdEAsc[])(ESTADOS_COMUNICACION &state) = {estado_esperandoRx, estado_paraMP3, estado_paraPulsador, estado_enviarDatos, nullptr};

//Timer para la comunicacion inicial
Timer init_COMS(Timer::DEC);

bool isCOM_exitosa = false;
bool isTimer_inited = false;

//Funcion que envia constantemente mensaje a la PC para que inicie la comunicacion
//Envia cada 1 segundo (se puede cambiar) mensajes a la pc de que me quiero comunicar con el
//La PC debe responder con OK
void init_COM_PC()
{
    if(!isTimer_inited) //Inicio el timer
    {
        isTimer_inited = true;
        init_COMS.TimerStart(10, init_COM_PC, Timer::DEC);
    }

    if(comPC.RxMensaje(msgRx, sizeof(msgRx)))
    {
        if((msgRx[0] == '&') && (msgRx[1] == 'O') && (msgRx[2] == 'K') && (msgRx[3] == '#')) //El mensaje de la PC fue el correcto
        {
            isCOM_exitosa = true; 
        }
    }

    if(isCOM_exitosa)
    {
        init_COMS.TimerStop();
        return;
    }

    prepareMsg(msgTx, COMANDO_INICIO, MAX_PISOS);
    //Envio mi comando de inicio y de argumento la cantidad de pisos del ascensor

    //Si la comunicacion fue exitosa, me tiene que enviar lo siguiente:
    //Posicion comando: la letra 'O' mayuscula
    //Posicion argmento: la letra 'K' mayuscula

    comPC.Transmit(msgTx, sizeof(msgTx));

    init_COMS.SetTimer(10); //Envio esto cada 1 segundo
}

//Maquina de estados para la comunicacion
void MdE_Comunicacion()
{
    static ESTADOS_COMUNICACION state = ESPERANDO_RX; //Inicio en ESPERANDO RX

    if(isCOM_exitosa) //Solo empiezo la MdE si la comunicacion fue exitosa
    {
        if(funcs_MdEAsc[state])
        {
            funcs_MdEAsc[state] (state);
        }
    }

    init_COMS.TmrEvent();
}
