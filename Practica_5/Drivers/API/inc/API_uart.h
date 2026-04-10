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
bool_t uartInit(void);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
