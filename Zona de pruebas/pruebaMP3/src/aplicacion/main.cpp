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
			test.playNext();
		break;

		case 1:
			test.playPrev();
		break;

		case 2:
			test.playTrack(2);
		break;

		case 3:
			test.increaseVol();
		break;
		
		case 4:
			test.decreaseVol();
		break;

		case 5:
			test.specify_Vol(0x15);
		break;

		case 6:
			test.specify_EQ(DfPlayer::JAZZ);
		break;

		case 7:
			test.specify_single_repe_pb(1);
		break;

		case 8:
			test.setSleep();
		break;

		case 9:
			test.reset();
		break;

		case 10:
			test.play();
		break;

		case 11:
			test.pause();
		break;

		case 12:
			test.play();
			test.specify_pbTrack_inFolder(1, 1);
		break;
		
		case 13:
			test.setting_AudioAmp(10);
		break;

		case 14:
			test.set_AllRepeat_pb(DfPlayer::START_REPEAT_PB);
		break;

		case 15:
			test.stop(DfPlayer::STOP_ALL_PLAYBACKS);
		break;

		case 16:
			test.specify_repeat_playback(1);
		break;

		case 17:
			test.random();
		break;

		case 18:
			test.set_repeat_current_track(DfPlayer::REPEAT_TURN_OFF);
		break;

		case 19:
			test.setDAC(false);
		break;
	}

	if(index != 19)
	{
		index++;
	}
	else 
	{
		index = 0;
	}

	t_testerMP3.SetTimer(10);
}

int main(void)
{
	inicializacion();

	//t_testerMP3.TimerStart(10, testerMets, Timer::SEG);

    while(1)
    {
    	t_testerMP3.TmrEvent();
    }

    return 0;
}
