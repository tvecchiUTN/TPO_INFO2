#include "ascCOM.h"

#define SIZE_MSG 8

#define BEGIN_CHAR '$'
#define END_CHAR '&'
#define INIT_COM_CHAR 255

#define BEGIN_POS 0
#define RESERVED 1
#define DIRECTION_POS 2
#define CMD_POS 3
#define ARG1_POS 4
#define ARG2_POS 5
#define CHECKSUM_POS 6
#define END_POS 7

#define MAX_MP3_CMDs 8

enum direction_com_t
{
    DIRECTION_TX_PC,
    DIRECTION_RX_PC,
    DIRECTION_MP3
};

enum commandMP3_com_t
{
    COMMAND_PAUSE,
    COMMAND_PLAY,
    COMMAND_NEXT,
    COMMAND_PREV,
    COMMAND_VOLUME,
    COMMAND_MUTE,
    COMMAND_SHUFFLE,
    COMMAND_REPEAT,
};

DfPlayer reproductorMP3(0, 0, 16, 0, 17);
Uart comunicacionPC(1, 0, 25, 0, 24, 9600, Uart::ocho_bits, Uart::NoParidad, SIZE_MSG * 2, SIZE_MSG * 2);

uint8_t PisoDeseado = 0;

static uint8_t msg_send[SIZE_MSG];

static volatile bool computerConected = false;

Timer timeInit(Timer::DEC);

static void prepare_msgPC(uint8_t cmd, uint8_t arg1, uint8_t arg2)
{
    uint8_t checksum = 0;

    msg_send[BEGIN_POS] = BEGIN_CHAR;
    msg_send[END_POS] = END_CHAR;

    msg_send[DIRECTION_POS] = DIRECTION_TX_PC;
    msg_send[CMD_POS] = cmd;
    msg_send[ARG1_POS] = arg1;
    msg_send[ARG2_POS] = arg2;

    checksum = 0xFF - cmd - arg1 - arg2 + 1;

    msg_send[CHECKSUM_POS] = checksum;
}

static bool readCheck_msgPC(uint8_t &cmd, uint8_t &arg1, uint8_t &arg2)
{
    uint8_t checksum = 0xFF - msg_send[CMD_POS] - msg_send[ARG1_POS] - msg_send[ARG2_POS] + 1;

    if (checksum == msg_send[CHECKSUM_POS])
    {
        cmd = msg_send[CMD_POS];
        arg1 = msg_send[ARG1_POS];
        arg2 = msg_send[ARG2_POS];
        return true;
    }

    return false;
}

static void send_MP3_comand(commandMP3_com_t cmd)
{
    switch (cmd)
    {
    case COMMAND_PAUSE:
        reproductorMP3.pause();
        break;

    case COMMAND_PLAY:
        reproductorMP3.play();
        break;

    case COMMAND_NEXT:
        reproductorMP3.playNext();
        break;

    case COMMAND_PREV:
        reproductorMP3.playPrev();
        break;

    case COMMAND_VOLUME:
        reproductorMP3.specify_Vol(msg_send[ARG2_POS]);
        break;

    case COMMAND_MUTE:
        reproductorMP3.specify_Vol(0);
        break;

    case COMMAND_SHUFFLE:
        reproductorMP3.random();
        break;

    case COMMAND_REPEAT:
        if (!msg_send[ARG2_POS])
        {
            reproductorMP3.set_repeat_current_track(DfPlayer::repeat_track_t::REPEAT_TURN_ON);
        }
        else
        {
            reproductorMP3.set_repeat_current_track(DfPlayer::repeat_track_t::REPEAT_TURN_OFF);
        }
        break;
    }
}

void timeCheckPerifericos()
{
    static uint8_t estadoInicio = 0;

    switch (estadoInicio)
    {
    case 0:
        if (reproductorMP3.isMP3_Available())
        {
            reproductorMP3.setDAC(false);   // Seteo modo DAC en el reproductor MP3
            reproductorMP3.specify_Vol(30); // Establezco un volumen de 30
            estadoInicio = 1;
        }
        break;

    case 1:
        uint8_t msg[8];
        void *rxMsg = comunicacionPC.RxMensaje(msg, 8);
        if (rxMsg)
        {
            uint8_t cmd, arg1, arg2;
            readCheck_msgPC(cmd, arg1, arg2);

            if (cmd == 0 && arg1 == 'u' && arg2 == 'C')
            {
                timeInit.TimerStop();
                computerConected = true;
                return;
            }
        }
        else
        {
            prepare_msgPC(INIT_COM_CHAR, 'Q', 't'); // Preparo el mensaje de inicio hacia el Qt
            comunicacionPC.Transmit(msg_send, SIZE_MSG);
            // A este punto la computadora debe recibir el mensaje de inicio (255) y sus argumentos.
            // En caso de que la misma no la haya recibido, debo enviar devuelta hasta que la reciba
        }
        break;
    }

    timeInit.SetTimer(1);
}

void initComs()
{
    timeInit.TimerStart(1, timeCheckPerifericos, Timer::DEC);
}

enum estados_COM_t
{
    ESPERANDO_MENSAJE,
    DECODIFICANDO_MENSAJE,
    PARA_MP3,
    PARA_CABINA
};

void estado_EsperandoMensaje(estados_COM_t &estado)
{
    void *rxMsg = comunicacionPC.RxMensaje(msg_send, SIZE_MSG);
    if (!rxMsg)
    {
        estado = DECODIFICANDO_MENSAJE;
    }
}

void estado_DecodificandoMensaje(estados_COM_t &estado)
{
    bool dataRight = false;

    if ((msg_send[BEGIN_POS] == BEGIN_CHAR) && (msg_send[END_POS] == END_CHAR))
    {
        uint8_t checksum = 0xFF - msg_send[CMD_POS] - msg_send[ARG1_POS] - msg_send[ARG2_POS] + 1;

        if (checksum == msg_send[CHECKSUM_POS])
        {
            dataRight = true;
        }
    }

    if (dataRight)
    {
        if (msg_send[DIRECTION_POS] == DIRECTION_RX_PC)
        {
            estado = PARA_CABINA;
            return;
        }
        else if (msg_send[DIRECTION_POS] == DIRECTION_MP3)
        {
            estado = PARA_MP3;
            return;
        }
    }
    else
    {
        estado = ESPERANDO_MENSAJE;
    }
}

void estado_ParaMP3(estados_COM_t &estado)
{
    if (msg_send[ARG1_POS] < MAX_MP3_CMDs)
    {
        send_MP3_comand((commandMP3_com_t)msg_send[CMD_POS]);
    }

    estado = ESPERANDO_MENSAJE;
}

void estado_ParaCabina(estados_COM_t &estado)
{
    if (msg_send[ARG1_POS] < MAX_PISOS)
    {
        PisoDeseado = msg_send[ARG1_POS];
    }

    estado = ESPERANDO_MENSAJE;
}

void (*arr_estados[])(estados_COM_t &estado) = {
    estado_EsperandoMensaje, estado_DecodificandoMensaje, estado_ParaMP3, estado_ParaCabina};

void MdE_comunicaciones()
{
    static estados_COM_t estadoCOM = ESPERANDO_MENSAJE;

    if (computerConected)
    {
        arr_estados[estadoCOM](estadoCOM);
    }

    timeInit.TmrEvent();
}