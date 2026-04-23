/*
 * API_uart.h
 *
 *  Created on: 9 abr 2026
 *      Author: danie
 */


#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdint.h>
#include <stdbool.h>

/* Definición de tipos para compatibilidad */
typedef bool bool_t;

/* Prototipos de funciones de la UART */

/* Inicializa la UART y envía mensaje de bienvenida */
bool_t uartInit(uint32_t baudrate);

/* mensajeria interna */
void uartSendString(uint8_t * pstring);

/* comunicacion no bloqueante */
bool_t uartReceiveByte(uint8_t * pByte);

#endif /* API_INC_API_UART_H_ */
