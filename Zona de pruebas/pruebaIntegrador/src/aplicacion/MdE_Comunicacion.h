#ifndef __MDE_COMUNICACION_H
#define __MDE_COMUNICACION_H

enum ESTADOS_COMUNICACION
{
    ESPERANDO_RX,
    PARA_MP3,
    PARA_PULSADOR,
    ENVIAR_DATOS
};

enum COMANDOS
{
    PULSADORES,
    MUSICA
};

enum CMD_MUSICA
{
    PAUSAR,
    REPRODUCIR,
    SIGUIENTE,
    ANTERIOR
};

void init_COM_PC();

void MdE_Comunicacion();

#endif
