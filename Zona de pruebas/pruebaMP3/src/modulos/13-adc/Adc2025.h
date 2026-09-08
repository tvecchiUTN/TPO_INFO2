/*******************************************************************************************************************************//**
 *
 * @file		adc.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		9 nov. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef CLASES_I1_ADC_ADC_H_
#define CLASES_I1_ADC_ADC_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "main.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#if defined (__cplusplus)
	extern "C" {
	void ADC_SEQA_IRQHandler(void);
	void ADC_SEQB_IRQHandler(void) ;
	void ADC_THCMP_IRQHandler(void);
	void ADC_OVR_IRQHandler(void);
	}
#endif

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/


class AnalogInput
{
	private:
		uint8_t  m_NumeroCanal;
		static 	uint8_t m_inicializar;
		uint32_t m_TipoDeFiltro ;
		int32_t (*m_callback)(int32_t);

	public:
		enum resultado_t	{ CRUDO , PROMEDIO , CALLBACK };
		AnalogInput(uint8_t , resultado_t);
		AnalogInput(uint8_t , int32_t (*callback)(int32_t));
		virtual ~AnalogInput();

		void SeqA_IRQHandler( void );
		void SeqB_IRQHandler( void );
		void Thcmp_IRQHandler( void );
		void Ovr_IRQHandler( void ) ;
		int32_t Get_resultado( void );
		void Start_conversion( uint8_t);

	private:
		void InicializarADC( void );
		void Set_clk_div( uint8_t);
		void Set_mode_end_of_conversion( uint8_t);
		void Set_mode_end_of_sequence( uint8_t);
		void Set_burst_mode( uint8_t);
		void Set_channels( uint8_t, uint16_t);
		void Set_single_sequence_mode( uint8_t);
		void Set_step_mode( uint8_t);
		void Enable_sequence( uint8_t);
		void Enable_interrupt( uint8_t);
		void Disable_interrupt( uint8_t);
		uint32_t Promedio( void );
		void Calibrar( void );
};



#endif /* CLASES_I1_ADC_ADC_H_ */
