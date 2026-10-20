/*******************************************************************************************************************************//**
 *
 * @file		adc.cpp
 * @brief		Descripcion del modulo
 * @date		9 nov. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "main.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define	ISE_ADC_SEQA			16
#define START					26
#define BURST					27
#define SINGLESTEP				28

#define	TAMANIO_BUFFER_ADC		16
#define	CANTIDAD_DE_CANALES		12

#define SEQA					0
#define SEQB					1

#define CANAL0					0
#define CANAL1					1

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
struct canal
{
	uint16_t 		indice;
	Gpio::port_t	port;
	uint8_t 		bit;
};

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/


struct canal CanalesEnUso[] =
{
		{ 0 , Gpio::PORT0 ,   7 },	//canal 0
		{ 0 , Gpio::PORT0 ,   6 },	//canal 1
};

uint8_t AnalogInput::m_inicializar = 0 ;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
AnalogInput	*g_adc = nullptr ;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/*Matriz de buffers para almacenar muestras de potencialmente 12 canales*/
static uint32_t g_muestrasADC [12][TAMANIO_BUFFER_ADC] ;


/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
AnalogInput::AnalogInput( uint8_t canal ,  resultado_t TipoDeFiltro )
{
	m_callback = nullptr;
	m_NumeroCanal = canal ;
	m_TipoDeFiltro = TipoDeFiltro ;
	InicializarADC();
}

AnalogInput::AnalogInput( uint8_t canal , int32_t (*callback)(int32_t) )
{
	m_callback = callback;
	m_NumeroCanal = canal ;
	m_TipoDeFiltro = CALLBACK ;
	InicializarADC();
}

void AnalogInput::InicializarADC( void )
{
	if ( !m_inicializar )
	{
		m_inicializar = true;
		// #### 1 ####
		SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_ADC_MASK;		// Habilitamos alimentacion del periferico analógico

		// #### 2 ####
		SYSCON->SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_ADC_MASK;	// Habilitamos clock del periferico

		// #### 3 ####
		SYSCON->ADCCLKSEL = 0;
		SYSCON->ADCCLKDIV = 1; 										// 1 Setea divisor de ADC en 1

		// #### 4 ####
		//Opero con la SWM para habilitar el/los canales que use
		SYSCON->SYSAHBCLKCTRL0 |= ((uint32_t)(0x01 << 7));			// Habilito clock de SWM
		SWM0->PINENABLE0 &= ~( 1 <<  (m_NumeroCanal + 14) );  //en SWM habilito canal 0 ADC para ESTE ejemplo
		/*Aquí habilitaría el resto de canales que quiera usar ....
		* SWM0->PINENABLE0 &= ~( 1 <<  ("CANALN" + 14) );
		* Los canales del ADC estan en bits consecutivos en PINENABLE0 a partir del bit14 */
		SYSCON->SYSAHBCLKCTRL0 &= ~((uint32_t)(0x01 << 7));			// Deshabilito clock de SWM

		// #### 5 ####
		Calibrar( );

		// #### 6 ####
		ADC0->CTRL &= ~(uint32_t)ADC_CTRL_ASYNMODE_MASK; // Modo Sincrónico de clock
		Set_clk_div( 12 );
		ADC0->CTRL &= ~(uint32_t)ADC_CTRL_LPWRMODE_MASK; // Modo Low Power off

		// Configuramos los canales que van en cada secuencia de conversion
		Set_channels( SEQA , m_NumeroCanal );	//Aquí se configuró el canal0 en la secuencia A

		// Configuramos modo para que la interrupcion se efectue al finalizar toda la secuencia
		Set_mode_end_of_conversion( SEQA );
		// Habilitamos secuencia de conversion A
		Enable_sequence( SEQA );
		// Habilitamos interrupciones para fin de conversion de secuencia A
		Enable_interrupt( SEQA );
		Set_step_mode( SEQA ) ;

		g_adc = this ;

		NVIC->ISER[0] |= (1 << ISE_ADC_SEQA);
		Start_conversion( SEQA );		//disparamos la medición porque así lo requerimos en nuestra aplicación
	}
}

void AnalogInput::Set_mode_end_of_conversion( uint8_t seq )
{
	ADC0->SEQ_CTRL[ seq ] &= ~(1 << 30);
}

void AnalogInput::Set_mode_end_of_sequence( uint8_t seq )
{
	ADC0->SEQ_CTRL[ seq ] |= (1 << 30);
}

void AnalogInput::Enable_sequence( uint8_t seq )
{
	ADC0->SEQ_CTRL[ seq ] |= (1 << 31) ;
}

void AnalogInput::Enable_interrupt( uint8_t seq )
{
	ADC0->INTEN |= (1 << seq ) ;
}

void AnalogInput::Disable_interrupt( uint8_t seq )
{
	ADC0->INTEN &= ~(1 << seq ) ;
}

void AnalogInput::Set_clk_div( uint8_t div )
{
	ADC0->CTRL &= ~0x000000FF;
	ADC0->CTRL |= div;
}

void AnalogInput::Set_channels( uint8_t seq , uint16_t canal )
{
	uint32_t canales = 0; //variable auxiliar

	canales = 1 << canal ;
	ADC0->SEQ_CTRL[ seq ] |= ( canales & 0x03FF ) ; //con 0x03FF limpio resto de los bits
}

void AnalogInput::Start_conversion( uint8_t seq )
{
	ADC0->SEQ_CTRL[ seq ] |= (1 << 26) ;
}

void AnalogInput::Set_burst_mode( uint8_t seq )
{
	ADC0->SEQ_CTRL[ seq ] &= ~( 1 << START);
	ADC0->SEQ_CTRL[ seq ] &= ~( 1 << SINGLESTEP);
	ADC0->SEQ_CTRL[ seq ] |=  ( 1 << BURST);
}

void AnalogInput::Set_single_sequence_mode( uint8_t seq )
{
	ADC0->SEQ_CTRL[ seq ] &= ~( 1<< SINGLESTEP );
	ADC0->SEQ_CTRL[ seq ] &= ~( 1<< BURST );
	ADC0->SEQ_CTRL[ seq ] |=  ( 1 << START );
}

void AnalogInput::Set_step_mode( uint8_t seq )
{
	ADC0->SEQ_CTRL[ seq ] &= ~( 1 << BURST );
	ADC0->SEQ_CTRL[ seq ] &= ~( 1 << START );
	ADC0->SEQ_CTRL[ seq ] |=  ( 1 << SINGLESTEP );
}

		
void AnalogInput::SeqA_IRQHandler(void)
{
	uint32_t resultado;
	uint8_t canal ;

	resultado =  ADC0->SEQ_GDAT[0];
	canal = ( resultado >> 26 ) & 0xf;

	switch ( m_TipoDeFiltro )
	{
		case CRUDO:
			g_muestrasADC[ canal ][ 0 ] = ((resultado >> 4) & 0xFFF);
			break;
		case PROMEDIO:
		case CALLBACK:
			g_muestrasADC[ canal ][CanalesEnUso[canal].indice] = ((resultado >> 4) & 0xFFF);

			break;
	}
	CanalesEnUso[canal].indice ++;
	CanalesEnUso[canal].indice %= TAMANIO_BUFFER_ADC;
	Start_conversion( SEQA );
}



void AnalogInput::SeqB_IRQHandler(void)
{
	// ### codigo de la funcion  ##

	return ;
}
void AnalogInput::Thcmp_IRQHandler(void)
{
	// ### codigo de la funcion  ##

	return ;
}
void AnalogInput::Ovr_IRQHandler(void)
{
	// ### codigo de la funcion  ##
	return ;
}

void AnalogInput::Calibrar( void )
{
	uint32_t temporal;
    uint32_t frecuencia = 0U;

	// 4-Calibra ADC
	//a-Se debe obtener la frecuencia del ADC
	frecuencia = FREQ_CLOCK;
	temporal = ADC0->CTRL;
	//b-Se debe llevar la frecuencia del ADC a 500kHz
	ADC0->CTRL &= ~ADC_CTRL_CLKDIV_MASK;
	ADC0->CTRL |= ADC_CTRL_CLKDIV((frecuencia / 500000U) - 1U);
	/* Clear the LPWR bit. */
	ADC0->CTRL &= ~ADC_CTRL_LPWRMODE_MASK;

	/* Start ADC self-calibration. */
	ADC0->CTRL |= ADC_CTRL_CALMODE_MASK;

	while( ADC0->CTRL &= 0x40000000) {
		// No hago nada hasta que no termine la calibracion del ADC.
	}; 

	/* Restore the contents of the ADC CTRL register. */
	ADC0->CTRL = temporal;
}


void ADC_SEQA_IRQHandler(void)
{
	if ( g_adc )
		g_adc->SeqA_IRQHandler( );
}

void ADC_SEQB_IRQHandler(void)
{
	if ( g_adc )
		g_adc->SeqB_IRQHandler( );

}
void ADC_THCMP_IRQHandler(void)
{
	if ( g_adc )
		g_adc->Thcmp_IRQHandler( );

}
void ADC_OVR_IRQHandler(void)
{
	if ( g_adc )
		g_adc->Ovr_IRQHandler( );

}

int32_t AnalogInput::Get_resultado(void) {

	uint32_t resultadoParcial;

	switch ( m_TipoDeFiltro )
	{
		case CRUDO :
			resultadoParcial = g_muestrasADC[m_NumeroCanal][0];
			break;
		case PROMEDIO:
			resultadoParcial = Promedio( );
			break;
		case CALLBACK:
			resultadoParcial = Promedio( );
			resultadoParcial = m_callback ( resultadoParcial );
			break;
	}

	return resultadoParcial;
}

uint32_t AnalogInput::Promedio( void )
{
	uint32_t resultadoParcial = 0;
	for (uint32_t i=0 ; i < TAMANIO_BUFFER_ADC ; i++)
		resultadoParcial += g_muestrasADC [m_NumeroCanal][i];
	resultadoParcial /= TAMANIO_BUFFER_ADC;
	return resultadoParcial ;
}




AnalogInput::~AnalogInput()
{
	// TODO Auto-generated destructor stub
}
