/*
 * aplicacion.h  —  Proyecto Base Parcial 1  —  Informatica II  UTN-FRBA  2026
 *
 * Declarar aquí los prototipos de las funciones de la aplicación.
 */

#ifndef APLICACION_H_
#define APLICACION_H_

void MiFuncionSysTickCallback( void );

Gpio::error_t checkError(uint8_t port, uint8_t bit);

#endif /* APLICACION_H_ */
