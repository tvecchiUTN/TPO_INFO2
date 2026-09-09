/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#include <cr_section_macros.h>
#include "main.h"

Uart testSend(0, 0, 16, 0, 17, 9600, Uart::ocho_bits, Uart::NoParidad, 40, 40);

typedef struct
{
    uint8_t startByte;
    uint8_t Version;
    uint8_t Len;
    uint8_t CMD;
    uint8_t FeedBack;
    uint8_t para1;
    uint8_t para2;
    uint8_t checksum1;
    uint8_t checksum2;
    uint8_t endByte;
} data_MP3_t;

void cmd_play(data_MP3_t *InitMP3)
{
    InitMP3->startByte = 0X7E;
    InitMP3->Version = 0XFF;
    InitMP3->Len = 6;
    InitMP3->CMD = 0x0D;
    InitMP3->FeedBack = 0x00;
    InitMP3->para1 = 0X00;
    InitMP3->para2 = 0X00;
    InitMP3->checksum1 = 0XFE;
    InitMP3->checksum2 = 0XEE;
    InitMP3->endByte = 0XEF;
}

void cmd_specify_FolderTrack(data_MP3_t *InitMP3, uint8_t folder, uint8_t track)
{
    InitMP3->startByte = 0X7E;
    InitMP3->Version = 0XFF;
    InitMP3->Len = 6;
    InitMP3->CMD = 0x0F;
    InitMP3->FeedBack = 0x00;
    InitMP3->para1 = folder;
    InitMP3->para2 = track;
    InitMP3->checksum1 = 0X00;
    InitMP3->checksum1 = 0X00;
    InitMP3->endByte = 0XEF;
}

Timer t_maxWait(Timer::SEG);
volatile bool isTimeLimit = false;
volatile bool mp3Hab = false;

void timeLimit()
{
    isTimeLimit = true;
}

int main(void)
{
	inicializacion();

    data_MP3_t CMD_MP3 = {0};

    t_maxWait.TimerStart(10, timeLimit, Timer::SEG);

    uint8_t msgRx[10];

    while(1)
    {
        t_maxWait.TmrEvent();
        if(!isTimeLimit)
        {
            void* ret = testSend.RxMensaje((void*)msgRx, 10);
            if(ret)
            {
                if(msgRx[3] == 0x3F)
                {
                    isTimeLimit = true;
                    mp3Hab = true;
                }
            }
        }

        if(mp3Hab)
        {
            cmd_specify_FolderTrack(&CMD_MP3, 1, 1);
            testSend.Transmit((void*)&CMD_MP3, 10);

            cmd_play(&CMD_MP3);
            testSend.Transmit((void*)&CMD_MP3, 10);
        }
    }

    return 0;
}
