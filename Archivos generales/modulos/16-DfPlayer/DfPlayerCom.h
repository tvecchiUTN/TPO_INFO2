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

#define VERSION_2025

/**
 * @class DfPlayer
 * @brief Clase para el control del módulo reproductor MP3 FN-M16P (DFPlayer Mini).
 * 
 * Permite el control asíncrono de la reproducción de archivos de audio ubicados 
 * en una tarjeta SD o memoria USB a través de comunicación UART. Hereda de 
 * PerifericoTemporizado para gestionar los tiempos de inicialización de hardware 
 * sin bloquear el flujo principal del programa (Bare-Metal).
 */
class DfPlayer : public PerifericoTemporizado
{
public:
    /**
     * @brief Tipos de ecualización soportados por el módulo.
     */
    enum typeEQ_t
    {
        NORMAL = 0,
        POP,
        ROCK,
        JAZZ,
        CLASSIC,
        BASS
    };

    /**
     * @brief Dispositivos de almacenamiento soportados.
     */
    enum playback_device_t
    {
        USB_FLASH_DRIVE = 1,
        SD_CARD
    };

    /**
     * @brief Tipos de parada para la reproducción.
     */
    enum type_stop_t
    {
        STOP_ADVERTISEMENT, /*!< Detiene solo el anuncio intercalado y reanuda el audio de fondo */
        STOP_ALL_PLAYBACKS  /*!< Detiene toda la reproducción activa */
    };

    /**
     * @brief Control de la repetición de todas las pistas.
     */
    enum repeat_playback_t
    {
        STOP_REPEAT_PB = 0, /*!< Detiene la repetición de pistas */
        START_REPEAT_PB     /*!< Inicia la repetición de todas las pistas */
    };

    /**
     * @brief Control de la repetición de la pista actual.
     */
    enum repeat_track_t
    {
        REPEAT_TURN_ON = 0, /*!< Activa la repetición de la pista actual */
        REPEAT_TURN_OFF     /*!< Desactiva la repetición de la pista actual */
    };

private:
    Uart m_serialCOM;               /*!< Objeto UART para la comunicación con el módulo */
    uint8_t data_MP3[SIZE_MSG];     /*!< Buffer de transmisión del mensaje de 10 bytes */
    uint32_t m_ticksWait;           /*!< Contador de ticks para la máquina de estados de inicialización */
    uint8_t isAvailable;            /*!< Estado actual de la disponibilidad del módulo (Máquina de estados) */

    /**
     * @brief Empaqueta el comando y los parámetros en el buffer de transmisión, calculando el checksum.
     * @param cmd Comando a enviar según el datasheet (ej. 0x01 para Play Next).
     * @param parameter1 Byte más significativo (MSB) del parámetro.
     * @param parameter2 Byte menos significativo (LSB) del parámetro.
     */
    void createMsg(uint8_t cmd, uint8_t parameter1, uint8_t parameter2);

    /**
     * @brief Envía el buffer pre-ensamblado `data_MP3` a través de la UART.
     */
    void sendMsg();

    /**
     * @brief Divide una palabra de 16 bits en dos bytes (MSB y LSB).
     * @param word Palabra de 16 bits a dividir.
     * @param r_par1 Referencia al byte donde se guardará el MSB.
     * @param r_par2 Referencia al byte donde se guardará el LSB.
     */
    void divideWord(uint16_t word, uint8_t &r_par1, uint8_t &r_par2);

public:
    /**
     * @brief Constructor de la clase DfPlayer.
     * @param usart Número de USART a utilizar.
     * @param portTx Puerto del pin TX.
     * @param bitTx Bit del pin TX.
     * @param portRx Puerto del pin RX.
     * @param bitRx Bit del pin RX.
     */
    DfPlayer(uint8_t usart, uint8_t portTx, uint8_t bitTx, uint8_t portRx, uint8_t bitRx);

#ifdef VERSION_2025
    /**
     * @brief Rutina de atención temporizada. 
     * Gestiona la espera necesaria para la inicialización y el montaje del sistema de archivos.
     */
    void handlerDelPeriferico();
#else
    void HandlerDelPeriferico();
#endif

    /**
     * @brief Verifica si el módulo ha terminado de inicializarse y está listo para recibir comandos.
     * @return true si el módulo está listo, false en caso contrario.
     */
    bool isMP3_Available() const;

    /**
     * @brief Reproduce la siguiente pista de audio. (Comando 0x01)
     */
    void playNext();

    /**
     * @brief Reproduce la pista de audio anterior. (Comando 0x02)
     */
    void playPrev();

    /**
     * @brief Reproduce una pista específica ubicada en el directorio raíz. (Comando 0x03)
     * @param trackSelect Número de pista física (0001 a 3000).
     */
    void playTrack(uint16_t trackSelect);

    /**
     * @brief Sube el volumen un nivel. (Comando 0x04)
     */
    void increaseVolume();

    /**
     * @brief Baja el volumen un nivel. (Comando 0x05)
     */
    void decreaseVolume();

    /**
     * @brief Establece un nivel de volumen específico. (Comando 0x06)
     * @param volDesired Nivel de volumen deseado (0 a 30).
     */
    void setVolume(uint8_t volDesired);

    /**
     * @brief Establece el modo de ecualización. (Comando 0x07)
     * @param EQ Modo de ecualización (ej. NORMAL, POP, ROCK).
     */
    void setEQ(typeEQ_t EQ);

    /**
     * @brief Reproduce una pista específica y la repite indefinidamente. (Comando 0x08)
     * @param number_track Número de pista física.
     */
    void playAndRepeatTrack(uint8_t number_track);

    /**
     * @brief Establece la fuente de almacenamiento a utilizar. (Comando 0x09)
     * @param pb_device Dispositivo de origen (USB_FLASH_DRIVE o SD_CARD).
     */
    void setPlaybackDevice(playback_device_t pb_device);

    /**
     * @brief Pone el módulo en modo de bajo consumo (Sleep). (Comando 0x0A)
     */
    void setSleep();

    /**
     * @brief Reinicia el módulo MP3. (Comando 0x0C)
     */
    void reset();

    /**
     * @brief Reanuda la reproducción actual. (Comando 0x0D)
     */
    void play();

    /**
     * @brief Pausa la reproducción actual. (Comando 0x0E)
     */
    void pause();

    /**
     * @brief Reproduce una pista específica dentro de una carpeta específica. (Comando 0x0F)
     * Las carpetas deben llamarse "01" a "99" y los archivos "001.mp3" a "255.mp3".
     * @param folder Número de la carpeta (1 a 99).
     * @param track Número de la pista (1 a 255).
     */
    void playTrackInFolder(uint8_t folder, uint8_t track);

    /**
     * @brief Ajusta la ganancia del amplificador de audio interno. (Comando 0x10)
     * @param setGain Valor de ganancia (0 a 31).
     */
    void setAudioGain(uint8_t setGain);

    /**
     * @brief Activa o desactiva la repetición de todas las pistas del almacenamiento. (Comando 0x11)
     * @param repeat_playback Estado de repetición (STOP_REPEAT_PB o START_REPEAT_PB).
     */
    void repeatAll(repeat_playback_t repeat_playback);

    /**
     * @brief Reproduce una pista ubicada específicamente en la carpeta llamada "MP3". (Comando 0x12)
     * @param number_track Número de pista dentro de la carpeta "MP3" (0001 a 3000).
     */
    void playTrackInMP3Folder(uint16_t number_track);

    /**
     * @brief Interrumpe la pista actual para reproducir un anuncio de la carpeta "ADVERT". (Comando 0x13)
     * Al terminar el anuncio, la pista anterior se reanuda desde donde se interrumpió.
     * @param number_track Número de pista dentro de la carpeta "ADVERT" (0001 a 3000).
     */
    void insertAdvert(uint16_t number_track);

    /**
     * @brief Detiene la reproducción. (Comandos 0x15 y 0x16)
     * Puede detener un anuncio intercalado para volver a la pista de fondo, o detener por completo la reproducción.
     * @param type_stop Tipo de parada a ejecutar.
     */
    void stop(type_stop_t type_stop);

    /**
     * @brief Repite continuamente todas las pistas de una carpeta específica. (Comando 0x17)
     * @param folder Número de la carpeta a repetir (1 a 99).
     */
    void repeatFolder(uint8_t folder);

    /**
     * @brief Inicia la reproducción de pistas en orden aleatorio. (Comando 0x18)
     */
    void playRandom();

    /**
     * @brief Activa o desactiva la repetición en bucle de la pista que está sonando actualmente. (Comando 0x19)
     * @param repeat_track Estado de repetición (REPEAT_TURN_ON o REPEAT_TURN_OFF).
     */
    void repeatCurrentTrack(repeat_track_t repeat_track);

    /**
     * @brief Habilita o deshabilita el conversor digital-analógico (DAC). (Comando 0x1A)
     * @param turnOFF_dac Si es true (1) apaga el DAC, si es false (0) lo enciende.
     */
    void setDAC(bool turnOFF_dac);
};

#endif