#ifndef I1_USART_UART_H_
#define I1_USART_UART_H_

//#include <stdint.h>
#include <cola_circular.h>
#include "inicializacion.h"

#ifdef __cplusplus
extern "C" {
    void UART0_IRQHandler(void);
    void UART1_IRQHandler(void);
    void UART2_IRQHandler(void);
    void UART3_IRQHandler(void);
    void UART4_IRQHandler(void);
}
#endif

class Uart
{
private:
    uint8_t      	m_usart;
    ColaCircular 	m_rx;
    ColaCircular   	m_tx;
    bool          	m_flagTx;

public:
    enum paridad_t     { NoParidad = 0, par = 2, impar };
    enum bits_de_datos { siete_bits = 0, ocho_bits };

    ~Uart();
    Uart(uint8_t usart,
         uint8_t portTx , uint8_t pinTx ,
         uint8_t portRx , uint8_t pinRx ,
         uint32_t baudrate,
         bits_de_datos BitsDeDatos,
         paridad_t paridad,
         uint32_t maxRx , uint32_t maxTx);

    void Transmit(const char* msg);
    void Transmit(void* msg, uint32_t n);
    void* RxMensaje(void* msg, uint32_t n);

    void UART_IRQHandler(void);

private:
    void Tx_EnableInterupt(void);
    void Tx_DisableInterupt(void);
};

// arreglo global para ISRs
//extern Uart* g_usart[5];

#endif /* I1_USART_UART_H_ */
