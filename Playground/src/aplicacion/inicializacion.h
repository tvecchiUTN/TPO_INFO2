/*
 * inicializacion.h  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 *
 * Declaraciones extern de los objetos globales instanciados en inicializacion.cpp.
 * Agregar aquí los extern de los objetos que se declaren.
 */

#ifndef INICIALIZACION_H_
#define INICIALIZACION_H_

#include "DriverStepper.h"

// ── Declaraciones extern de objetos globales ──────────────────────────────
// (completar según los objetos instanciados en inicializacion.cpp)

extern DriverStepper pasoPaso;
extern Timer tiempoPaso;

void inicializacion( void );

#endif /* INICIALIZACION_H_ */
