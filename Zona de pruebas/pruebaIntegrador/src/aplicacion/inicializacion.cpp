#include "main.h"
#include "MdE_Comunicacion.h"

DigitalInputs OpticoPB(0, 23, Gpio::INACTIVE, Gpio::LOW, 5);
DigitalInputs OpticoP1(0, 22, Gpio::INACTIVE, Gpio::LOW, 5);
DigitalInputs OpticoP2(0, 21, Gpio::INACTIVE, Gpio::LOW, 5);
DigitalInputs OpticoP3(0, 20, Gpio::INACTIVE, Gpio::LOW, 5);

DfPlayer reproductor(0, 0, 16, 0, 17);

Uart comPC(1, 0, 25, 0, 24, 9600, Uart::ocho_bits, Uart::NoParidad, 16, 16);

DriverStepper pasoApaso(1, 0, 1, 1, 1, 2);

Gpio Teclado_FILA0(0, 28, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);
Gpio Teclado_FILA1(0, 27, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);

Gpio Teclado_COL0(0, 26, Gpio::INACTIVE, Gpio::INPUT, Gpio::LOW);
Gpio Teclado_COL1(0, 15, Gpio::INACTIVE, Gpio::INPUT, Gpio::LOW);
Gpio Teclado_COL2(0, 8, Gpio::INACTIVE, Gpio::INPUT, Gpio::LOW);

Gpio *Teclado_FILAS[] = {&Teclado_FILA0, &Teclado_FILA1, nullptr};
Gpio *Teclado_COL[] = {&Teclado_COL0, &Teclado_COL1, &Teclado_COL2, nullptr};

Teclado teclado(Teclado_COL, Teclado_FILAS);

Gpio LCD_RS_gpio(0, 1, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH);
Gpio LCD_E_gpio(0, 14, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH);
Gpio LCD_D4_gpio(0, 9, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH);
Gpio LCD_D5_gpio(0, 10, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH);
Gpio LCD_D6_gpio(0, 11, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::HIGH);

Gpio *LCD_Bus[] = {&LCD_RS_gpio, &LCD_E_gpio, &LCD_D4_gpio, &LCD_D5_gpio, &LCD_D6_gpio, nullptr};

//Lcd displayLCD(LCD_Bus);

void inicializacion( void )
{
    inicOScilador();
    SysTick_InstalarCallback( MiFuncionSysTickCallback );
    Inicializar_SysTick( FREQ_SYSTICK );

    pasoApaso.setSteppDir(DriverStepper::HORARIO);
    pasoApaso.setTicks(10);
    pasoApaso.startDriver();

    init_COM_PC();
}
