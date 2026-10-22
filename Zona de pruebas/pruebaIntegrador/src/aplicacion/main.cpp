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
        MdE_Ascensor();
        MdE_Comunicacion();
    }

    return 0;
}
