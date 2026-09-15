#ifndef __DFPLAYER_H
#define __DFPLAYER_H

#include "main.h"

#define START_BYTE data_MP3[0]
#define VERSION data_MP3[1]
#define LEN data_MP3[2]
#define CMD data_MP3[3]
#define FEEDBACK data_MP3[4]
#define PARA1 data_MP3[5]
#define PARA2 data_MP3[6]
#define CHECKSUM1 data_MP3[7]
#define CHECKSUM2 data_MP3[8]
#define END_BYTE data_MP3[9]

#define SIZE_MSG 10

/**
 * @brief Clase para el control del módulo reproductor MP3 FN-M16P (DFPlayer).
 * Se comunica mediante UART y permite el control asíncrono de la reproducción
 * de archivos de audio ubicados en una tarjeta SD o memoria USB.
 * 
 * 
 * 
*/
class DfPlayer : public PerifericoTemporizado
{
public:
    enum typeEQ_t
    {
        NORMAL = 0,
        POP,
        ROCK,
        JAZZ,
        CLASSIC,
        BASS  
    };

private:
    Uart m_serialCOM;
    uint8_t data_MP3[SIZE_MSG];

    uint32_t m_ticksWait;

    uint8_t isAvailable;

    void createMsg(uint8_t cmd, uint8_t parameter1, uint8_t parameter2);

    void sendMsg();

    void divideWord(uint16_t word, uint8_t& r_par1, uint8_t& r_par2);
public:
    DfPlayer(uint8_t usart, uint8_t portTx, uint8_t bitTx, uint8_t portRx, uint8_t bitRx);

    void handlerDelPeriferico();

    bool isMP3_Available() const;

    void playNext();

    void playPrev();

    void playTrack(uint16_t trackSelect);

    void increaseVol();

    void decreaseVol();

    void specify_Vol(uint8_t volDesired);

    void specify_EQ(typeEQ_t EQ);

    void specify_single_repe_pb(uint8_t number_track);

    enum playback_device_t
    {
        USB_FLASH_DRIVE = 1,
        SD_CARD
    };
    void specify_pbDevice(playback_device_t pb_device);

    void setSleep();

    void reset();

    void play();

    void pause();

    void specify_pbTrack_inFolder(uint8_t folder, uint8_t track);

    void setting_AudioAmp(uint8_t setGain);

    enum repeat_playback_t
    {
        STOP_REPEAT_PB = 0,
        START_REPEAT_PB
    };

    void set_AllRepeat_pb(repeat_playback_t repeat_playback);

    void specify_pb_folderMP3(uint16_t number_track);

    void insertAdv(uint16_t number_track);


    enum type_stop_t
    {
        STOP_ADVERTISEMENT,
        STOP_ALL_PLAYBACKS
    };

    void stop(type_stop_t type_stop);

    void specify_repeat_playback(uint8_t folder);

    void random();

    enum repeat_track_t
    {
        REPEAT_TURN_ON,
        REPEAT_TURN_OFF
    };

    void set_repeat_current_track(repeat_track_t repeat_track);

    void setDAC(bool turnOFF_dac);
};

#endif