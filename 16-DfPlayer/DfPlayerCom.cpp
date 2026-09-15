#include "main.h"
#include "DfPlayerCom.h"

#define NO_AVAILABLE 0
#define SELECTING_SD 1
#define AVAILABLE 2

DfPlayer::DfPlayer(uint8_t usart, uint8_t portTx, uint8_t bitTx, uint8_t portRx, uint8_t bitRx) 
    : m_serialCOM(usart, portTx, bitTx, portRx, bitRx, 9600, Uart::ocho_bits, Uart::NoParidad, 40, 40)
{
    START_BYTE = 0x7E;
    VERSION = 0xFF;
    LEN = 0x06;
    FEEDBACK = 0X0;
    END_BYTE = 0xEF;

    isAvailable = NO_AVAILABLE;
    m_ticksWait = 1500; // Ticks iniciales para esperar estabilización según datasheet

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
                
                // Espera el mensaje de inicialización del dispositivo (0x3F)
                if (ret && msgRx[3] == 0x3f)
                {    
                    isAvailable = SELECTING_SD;
                    setPlaybackDevice(SD_CARD);
                    m_ticksWait = 200; // Según datasheet: esperar 200ms tras inicializar el file system
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
    return (isAvailable == AVAILABLE);
}

void DfPlayer::createMsg(uint8_t cmd, uint8_t parameter1, uint8_t parameter2)
{
    uint16_t sum = VERSION + LEN + FEEDBACK + cmd + parameter1 + parameter2;
    uint16_t aux = 0XFFFF - sum + 1; // Formula del Checksum según Datasheet

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

void DfPlayer::increaseVolume()
{
    createMsg(0x04, 0, 0);
    sendMsg();
}

void DfPlayer::decreaseVolume()
{
    createMsg(0x05, 0, 0);
    sendMsg();
}

void DfPlayer::setVolume(uint8_t volDesired)
{
    uint16_t vol = volDesired;

    if (volDesired > 30) // Límite máximo de volumen según datasheet
    {
        vol = 30;
    }

    uint8_t par1, par2;
    divideWord(vol, par1, par2);

    createMsg(0x06, par1, par2);
    sendMsg();
}

void DfPlayer::setEQ(typeEQ_t EQ)
{
    createMsg(0x07, 0, EQ);
    sendMsg();
}

void DfPlayer::playAndRepeatTrack(uint8_t number_track)
{
    createMsg(0x08, 0, number_track);
    sendMsg();
}

void DfPlayer::setPlaybackDevice(playback_device_t pb_device)
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

void DfPlayer::playTrackInFolder(uint8_t folder, uint8_t track)
{
    createMsg(0x0F, folder, track);
    sendMsg();
}

void DfPlayer::setAudioGain(uint8_t setGain)
{
    uint8_t gain = setGain;
    if(setGain > 31) // Amplificación límite es 31 (0 a 31)
    {
        gain = 31;
    }

    createMsg(0x10, 1, gain);
    sendMsg();
}

void DfPlayer::repeatAll(repeat_playback_t repeat_playback)
{
    createMsg(0x11, 0, repeat_playback);
    sendMsg();
}

void DfPlayer::playTrackInMP3Folder(uint16_t number_track)
{
    uint8_t par1, par2;

    divideWord(number_track, par1, par2);

    createMsg(0x12, par1, par2);
    sendMsg();
}

void DfPlayer::insertAdvert(uint16_t number_track)
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

void DfPlayer::repeatFolder(uint8_t folder)
{
    uint8_t fold = folder;
    if((folder > 99) || (folder == 0))
    {
        fold = 1;
    }
    createMsg(0x17, 0, fold);
    sendMsg();
}

void DfPlayer::playRandom()
{
    createMsg(0x18, 0, 0);
    sendMsg();
}

void DfPlayer::repeatCurrentTrack(repeat_track_t repeat_track)
{
    createMsg(0x19, 0, repeat_track);
    sendMsg();
}

void DfPlayer::setDAC(bool turnOFF_dac)
{
    uint8_t par2 = turnOFF_dac ? 1 : 0;
    createMsg(0x1A, 0, par2);
    sendMsg();
}