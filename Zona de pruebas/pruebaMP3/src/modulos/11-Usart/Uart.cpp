

#include "main.h"

// instancias globales
Uart* g_usart[5] = { 0, 0, 0, 0, 0 };

// punteros a USART reales (del LPC845.h)
static USART_Type* const USARTS[5] = { USART0, USART1, USART2, USART3, USART4 };

Uart::~Uart() {
    if (m_usart < 5 && g_usart[m_usart] == this)
        g_usart[m_usart] = 0;
}

Uart::Uart(uint8_t usart,
           uint8_t portTx , uint8_t pinTx ,
           uint8_t portRx , uint8_t pinRx ,
           uint32_t baudrate,
           bits_de_datos BitsDeDatos,
           paridad_t paridad,
           uint32_t maxRx , uint32_t maxTx)
: m_usart(usart), m_rx(maxRx), m_tx(maxTx), m_flagTx(false)
{
    uint8_t iser ;

    if ( m_usart == 0 ) g_usart[0] = this ;
    if ( m_usart == 1 ) g_usart[1] = this ;
    if ( m_usart == 2 ) g_usart[2] = this ;
    if ( m_usart == 3 ) g_usart[3] = this ;
    if ( m_usart == 4 ) g_usart[4] = this ;

    if ( m_usart == 0 ) { SYSCON->SYSAHBCLKCTRL0 |= ( 1u << 14 ); iser = 3;  }
    if ( m_usart == 1 ) { SYSCON->SYSAHBCLKCTRL0 |= ( 1u << 15 ); iser = 4;  }
    if ( m_usart == 2 ) { SYSCON->SYSAHBCLKCTRL0 |= ( 1u << 16 ); iser = 5;  }
    if ( m_usart == 3 ) { SYSCON->SYSAHBCLKCTRL0 |= ( 1u << 30 ); iser = 30; }
    if ( m_usart == 4 ) { SYSCON->SYSAHBCLKCTRL0 |= ( 1u << 31 ); iser = 31; }

    if ( m_usart == 0 ) SYSCON->FCLKSEL[0] = 1;
    if ( m_usart == 1 ) SYSCON->FCLKSEL[1] = 1;
    if ( m_usart == 2 ) SYSCON->FCLKSEL[2] = 1;
    if ( m_usart == 3 ) SYSCON->FCLKSEL[3] = 1;
    if ( m_usart == 4 ) SYSCON->FCLKSEL[4] = 1;

    // SWM para asignar pines
    SYSCON->SYSAHBCLKCTRL0 |= (1u << 7);
    if ( m_usart == 0 ) { PINASSIGN_Config(PA_U0_TXD, portTx, pinTx); PINASSIGN_Config(PA_U0_RXD, portRx, pinRx); }
    if ( m_usart == 1 ) { PINASSIGN_Config(PA_U1_TXD, portTx, pinTx); PINASSIGN_Config(PA_U1_RXD, portRx, pinRx); }
    if ( m_usart == 2 ) { PINASSIGN_Config(PA_U2_TXD, portTx, pinTx); PINASSIGN_Config(PA_U2_RXD, portRx, pinRx); }
    if ( m_usart == 3 ) { PINASSIGN_Config(PA_U3_TXD, portTx, pinTx); PINASSIGN_Config(PA_U3_RXD, portRx, pinRx); }
    if ( m_usart == 4 ) { PINASSIGN_Config(PA_U4_TXD, portTx, pinTx); PINASSIGN_Config(PA_U4_RXD, portRx, pinRx); }
    SYSCON->SYSAHBCLKCTRL0 &= ~(1u << 7);

    // CFG: enable=0 aquí; datos/paridad según enums
    USARTS[m_usart]->CFG = ( 0u << 0 )
                         | ( ((uint32_t)BitsDeDatos) << 2 )
                         | ( ((uint32_t)paridad)    << 4 )
                         | ( 0u << 6 )
                         | ( 0u << 9 )
                         | ( 0u << 11 );

    // BRG = ((FREQ_CLOCK/baud) / (OSR+1)) - 1
    USARTS[m_usart]->BRG = (( FREQ_CLOCK / baudrate ) / (USARTS[m_usart]->OSR + 1u)) - 1u;

    // Habilito RX Ready y su IRQ
    USARTS[m_usart]->INTENSET |= (1u << 0);   // RXRDY
    NVIC->ISER[0] |= ( 1u << iser );

    // Enable UART
    USARTS[m_usart]->CFG |= ( 1u << 0 );     // ENABLE
}

void Uart::Transmit(const char* msg)
{
    if (!msg) return;

    while (*msg)
    {
        m_tx.push((uint8_t)(*msg));

        if (m_flagTx == false)
        {
            m_flagTx = true;
            Tx_EnableInterupt();
        }

        msg++;
    }
}

void Uart::Transmit(void* msg, uint32_t n)
{
    if (!msg || n == 0) return;

    uint8_t* p = (uint8_t*)msg;

    for (uint32_t i = 0; i < n; i++)
    {
        m_tx.push(p[i]);

        if (m_flagTx == false)
        {
            m_flagTx = true;
            Tx_EnableInterupt();
        }
    }
}

void* Uart::RxMensaje(void* msg, uint32_t n)
{
    static uint32_t cont = 0;
    if (!msg || n == 0) 
			return nullptr;

    char*   p    = (char*)msg;
    uint8_t dato;

    if (m_rx.pop(dato)) {
        p[cont] = (char)dato;
        cont++;

        if (cont >= n || dato == '\n')  {
            cont = 0;
            return (void*)p;
        }
    }
    return nullptr;
}

void Uart::Tx_EnableInterupt(void)
{
    USARTS[m_usart]->INTENSET = (1u << 2);
}

void Uart::Tx_DisableInterupt(void)
{
    USARTS[m_usart]->INTENCLR = (1u << 2);
}

void Uart::UART_IRQHandler(void)
{
    uint8_t  dato;
    uint32_t stat = USARTS[m_usart]->STAT;   // STAT se borra al leerlo

    if (stat & (1 << 0))                    // RXRDY
    {
        dato = (uint8_t)USARTS[m_usart]->RXDAT;
        m_rx.push(dato);
    }

    if (stat & (1 << 2))                    			// TXRDY
    {
        if (m_tx.pop(dato))
            USARTS[m_usart]->TXDAT = (uint32_t)dato;
        else {
            Tx_DisableInterupt();
            m_flagTx = false;
        }
    }
}

// ----------- ISRs -----------
// (ajustá nombres si tus IRQ reales para USART3/4 difieren)
extern "C" void UART0_IRQHandler(void) 
	{ if (g_usart[0]) 
			g_usart[0]->UART_IRQHandler(); }
extern "C" void UART1_IRQHandler(void) 
	{ if (g_usart[1]) 
			g_usart[1]->UART_IRQHandler(); }
extern "C" void UART2_IRQHandler(void) 
	{ if (g_usart[2]) 
			g_usart[2]->UART_IRQHandler(); }
extern "C" void UART3_IRQHandler(void) 
	{ if (g_usart[3]) 
			g_usart[3]->UART_IRQHandler(); }
extern "C" void UART4_IRQHandler(void) 
{ if (g_usart[4]) 
		g_usart[4]->UART_IRQHandler(); }
