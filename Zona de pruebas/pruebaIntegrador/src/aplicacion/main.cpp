#include <cr_section_macros.h>
#include "main.h"

#include "MdE_Ascensor.h"
#include "MdE_Comunicacion.h"

int main( void )
{
    // ── Inicialización — NO modificar ────────────────────────────────────
    inicializacion();

    // ── Loop principal ───────────────────────────────────────────────────
    while( 1 ) 
    {
        MdE_Ascensor(); //Maquina de estados del ascensor
        MdE_Comunicacion(); //Maquina de estados para la comunicacion
    }

    return 0;
}
