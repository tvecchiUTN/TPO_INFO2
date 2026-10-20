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

DfPlayer test(0, 0, 16, 0, 17);

//Gpio LEDROJO(1, 0, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);
//DigitalInputs pulsador(0, 14, Gpio::PULLUP, Gpio::INPUT, Gpio::LOW);

Timer t_testerMP3(Timer::SEG);

void testerMets()
{
	static uint8_t index = 0;

	switch(index)
	{
		case 0:
			test.setDAC(false);
			test.specify_repeat_playback(1);
		break;

		case 1:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 2:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 3:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 4:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 5:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 6:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 7:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 8:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 9:
			//test.play();
			test.insertAdv(index-1);
		break;

		case 10:
			//test.play();
			test.insertAdv(index-1);
		break;
	}

	if(index != 10)
	{
		index++;
		t_testerMP3.SetTimer(10);
	}
	else
	{
		index = 1;
		t_testerMP3.SetTimer(10);
	}
}

Uart testU(1, 0, 25, 0, 24, 9600, Uart::ocho_bits, Uart::NoParidad, 64, 64);

void printf(const char* str)
{
	testU.Transmit(str);
}

int main(void)
{
	inicializacion();

	//t_testerMP3.TimerStart(5, testerMets, Timer::SEG);

	uint8_t msg[5];
	void* msgRx = nullptr;
    while(1)
    {
    	//t_testerMP3.TmrEvent();
		msgRx = testU.RxMensaje(msg, 5);

		if(msgRx)
		{
			printf("Mensaje recibido\n\r");
		}
    }

    return 0;
}
