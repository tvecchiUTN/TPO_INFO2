#ifndef COLA_CIRCULAR_H_
#define COLA_CIRCULAR_H_

//#include <stdint.h>

class Uart; // forward

class ColaCircular {
public:
    explicit ColaCircular(uint32_t capacidad);
    ~ColaCircular();

    // Encola SIEMPRE (no se controla “lleno”).
    uint8_t push(uint8_t dato);

    // Desencola: 1 si leyó, 0 si estaba vacía.
    uint8_t pop(uint8_t& dato);

private:
    uint8_t*  m_buf;
    uint32_t  m_tam;              // tamaño dinámico
    volatile uint32_t m_inxIn;    // próximo a escribir
    volatile uint32_t m_inxOut;   // próximo a leer

    //friend class Uart;            // Uart puede tocar índices si quiere
};

#endif // COLA_CIRCULAR_H_
