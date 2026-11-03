#include "main.h"
#include "MdE_Comunicacion.h"

DigitalInputs OpticoPB(0, 23, Gpio::INACTIVE, Gpio::LOW, 5); //Sensor optico de la planta baja
DigitalInputs OpticoP1(0, 22, Gpio::INACTIVE, Gpio::LOW, 5); //Sensor optico del piso 1
DigitalInputs OpticoP2(0, 21, Gpio::INACTIVE, Gpio::LOW, 5); //Sensor optico del piso 2
DigitalInputs OpticoP3(0, 20, Gpio::INACTIVE, Gpio::LOW, 5); //Sensor optico del piso 3

DfPlayer reproductor(0, 0, 16, 0, 17); //Reproductor MP3

Uart comPC(1, 0, 25, 0, 24, 9600, Uart::ocho_bits, Uart::NoParidad, 16, 16); //Objeto UART para la comunicacion con la PC

DriverStepper pasoApaso(1, 0, 1, 1, 1, 2); //Motor paso a paso

Gpio Teclado_FILA0(0, 28, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);
Gpio Teclado_FILA1(0, 27, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);

Gpio Teclado_COL0(0, 26, Gpio::INACTIVE, Gpio::INPUT, Gpio::LOW);
Gpio Teclado_COL1(0, 15, Gpio::INACTIVE, Gpio::INPUT, Gpio::LOW);
Gpio Teclado_COL2(0, 8, Gpio::INACTIVE, Gpio::INPUT, Gpio::LOW);

Gpio *Teclado_FILAS[] = {&Teclado_FILA0, &Teclado_FILA1, nullptr};
Gpio *Teclado_COL[] = {&Teclado_COL0, &Teclado_COL1, &Teclado_COL2, nullptr};

Teclado teclado(Teclado_COL, Teclado_FILAS); //Teclado matricial del Infotronic

Gpio g_d4 ( Gpio::PORT0,  9, Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_d5 ( Gpio::PORT0, 10, Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_d6 ( Gpio::PORT0, 11, Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_d7 ( Gpio::PORT0, 13, Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_rs ( Gpio::PORT0,  1, Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_en ( Gpio::PORT0, 14, Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );

Gpio *BusLcd[] = { &g_d4 ,&g_d5 ,&g_d6 ,&g_d7 ,&g_rs,&g_en};
Lcd LCD(BusLcd); //LCD del Infotronic

void inicializacion( void )
{
    inicOScilador();
    SysTick_InstalarCallback( MiFuncionSysTickCallback );
    Inicializar_SysTick( FREQ_SYSTICK );

    pasoApaso.setSteppDir(DriverStepper::HORARIO); //Establezco sentido inicial
    pasoApaso.setTicks(10); //Establesco una velocidad
    pasoApaso.startDriver(); //Inicio el motor

    init_COM_PC();
}
