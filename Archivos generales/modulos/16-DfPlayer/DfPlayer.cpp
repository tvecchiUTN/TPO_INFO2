#include "main.h"
#include "DfPlayer.h"

#define NO_AVAILABLE 0
#define SELECTING_SD 1
#define AVAILABLE 2

DfPlayer::DfPlayer(uint8_t usart, uint8_t portTx, uint8_t bitTx, uint8_t portRx, uint8_t bitRx) : m_serialCOM(usart, portTx, bitTx, portRx, bitRx, 9600, Uart::ocho_bits, Uart::NoParidad, 40, 40)
{
    START_BYTE = 0x7E;
    VERSION = 0xFF;
    LEN = 0x06;
    FEEDBACK = 0X0;
    END_BYTE = 0xEF;

    isAvailable = NO_AVAILABLE;
    m_ticksWait = 1500;

    #ifdef VERSION_2025
        pushCallback();
    #else
        AddPerifericoTemporizado(this);
    #endif
}

#ifdef VERSION_2025
    void DfPlayer::handlerDelPeriferico()
#else
    void DfPlayer::HandlerDelPeriferico()
#endif
{
    if (isAvailable != AVAILABLE)
    {
        if (!m_ticksWait)
        {
            if (isAvailable == NO_AVAILABLE)
            {
                uint8_t msgRx[10];
                void *ret = m_serialCOM.RxMensaje((void *)msgRx, 10);
                if (ret && msgRx[3] == 0x3f)
                {    
                    isAvailable = SELECTING_SD;
                    specify_pbDevice(SD_CARD);
                    m_ticksWait = 200;
                    isAvailable = SELECTING_SD;
                    return;
                }
            }
            else if (isAvailable == SELECTING_SD)
            {
                isAvailable = AVAILABLE;
                return;
            }
        }

        m_ticksWait--;
    }
}

bool DfPlayer::isMP3_Available() const
{
    if(isAvailable == AVAILABLE)
    {
        return true;
    }
    return false;
}

void DfPlayer::createMsg(uint8_t cmd, uint8_t parameter1, uint8_t parameter2)
{
    uint16_t sum = VERSION + LEN + FEEDBACK + cmd + parameter1 + parameter2;
    uint16_t aux = 0XFFFF - sum + 1;

    divideWord(aux, CHECKSUM1, CHECKSUM2);

    CMD = cmd;
    PARA1 = parameter1;
    PARA2 = parameter2;
}

void DfPlayer::sendMsg()
{
    m_serialCOM.Transmit((void *)&data_MP3, 10);
}

void DfPlayer::divideWord(uint16_t word, uint8_t &r_par1, uint8_t &r_par2)
{
    r_par1 = word >> 8; 
    r_par2 = word & 0x00FF;
}

void DfPlayer::playNext()
{
    createMsg(0x01, 0, 0);
    sendMsg();
}

void DfPlayer::playPrev()
{
    createMsg(0x02, 0, 0);
    sendMsg();
}

void DfPlayer::playTrack(uint16_t trackSelect)
{
    uint8_t par1, par2;
    divideWord(trackSelect, par1, par2);
    createMsg(0x03, par1, par2);
    sendMsg();
}

void DfPlayer::increaseVol()
{
    createMsg(0x04, 0, 0);
    sendMsg();
}

void DfPlayer::decreaseVol()
{
    createMsg(0x05, 0, 0);
    sendMsg();
}

void DfPlayer::specify_Vol(uint8_t volDesired)
{
    uint16_t vol = volDesired;

    if (volDesired > 30)
    {
        vol = 30;
    }

    uint8_t par1, par2;
    divideWord(vol, par1, par2);

    createMsg(0x06, par1, par2);
    sendMsg();
}

void DfPlayer::specify_EQ(typeEQ_t EQ)
{
    createMsg(0x07, 0, EQ);
    sendMsg();
}

void DfPlayer::specify_single_repe_pb(uint8_t number_track)
{
    createMsg(0x08, 0, number_track);
    sendMsg();
}

void DfPlayer::specify_pbDevice(playback_device_t pb_device)
{
    createMsg(0x09, 0, pb_device);
    sendMsg();
}

void DfPlayer::setSleep()
{
    createMsg(0x0A, 0, 0);
    sendMsg();
}

void DfPlayer::reset()
{
    createMsg(0x0C, 0, 0);
    sendMsg();
}

void DfPlayer::play()
{
    createMsg(0x0D, 0, 0);
    sendMsg();
}

void DfPlayer::pause()
{
    createMsg(0x0E, 0, 0);
    sendMsg();
}

void DfPlayer::specify_pbTrack_inFolder(uint8_t folder, uint8_t track)
{
    createMsg(0x0F, folder, track);
    sendMsg();
}

void DfPlayer::setting_AudioAmp(uint8_t setGain)
{
    uint8_t gain = setGain;
    if(setGain > 31)
    {
        gain = 31;
    }

    createMsg(0x10, 1, gain);
    sendMsg();
}

void DfPlayer::set_AllRepeat_pb(repeat_playback_t repeat_playback)
{
    createMsg(0x11, 0, repeat_playback);
    sendMsg();
}

void DfPlayer::specify_pb_folderMP3(uint16_t number_track)
{
    uint8_t par1, par2;

    divideWord(number_track, par1, par2);

    createMsg(0x12, par1, par2);
    sendMsg();
}

void DfPlayer::insertAdv(uint16_t number_track)
{
    uint8_t par1, par2;

    divideWord(number_track, par1, par2);

    createMsg(0x13, par1, par2);
    sendMsg();
}

void DfPlayer::stop(type_stop_t type_stop)
{
    if(type_stop == STOP_ADVERTISEMENT)
    {
        createMsg(0x15, 0, 0);
    }
    else
    {
        createMsg(0x16, 0, 0);
    }
    sendMsg();
}

void DfPlayer::specify_repeat_playback(uint8_t folder)
{
    uint8_t fold = folder;
    if((folder > 99) || (folder == 0))
    {
        fold = 1;
    }
    createMsg(0x17, 0, fold);
    sendMsg();
}

void DfPlayer::random()
{
    createMsg(0x18, 0, 0);
    sendMsg();
}

void DfPlayer::set_repeat_current_track(repeat_track_t repeat_track)
{
    createMsg(0x19, 0, repeat_track);
    sendMsg();
}

void DfPlayer::setDAC(bool turnOFF_dac)
{
    uint8_t par2;
    if (turnOFF_dac)
    {
        par2 = 1;
    }
    else
    {
        par2 = 0;
    }

    createMsg(0x1A, 0, par2);
    sendMsg();
}