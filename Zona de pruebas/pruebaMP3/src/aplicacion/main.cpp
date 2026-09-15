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
		break;

		case 1:
			test.play();
		break;
	}

	if(index != 1)
	{
		index++;
		t_testerMP3.SetTimer(5);
	}
}

int main(void)
{
	inicializacion();

	t_testerMP3.TimerStart(5, testerMets, Timer::SEG);

    while(1)
    {
    	t_testerMP3.TmrEvent();
    }

    return 0;
}
