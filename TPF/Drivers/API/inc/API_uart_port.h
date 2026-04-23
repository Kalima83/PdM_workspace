/*
 * API_uart_port.h
 *
 *  Created on: 22 abr 2026
 *      Author: danie
 */

#ifndef API_INC_API_UART_PORT_H_
#define API_INC_API_UART_PORT_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef bool bool_t;

/* Prototipos para la HAL */
bool_t uartPortConfig(uint32_t baudrate);
void uartPortSend(uint8_t *pdata, uint16_t size);
bool_t uartPortReceiveByte(uint8_t *pByte);

#endif /* API_INC_API_UART_PORT_H_ */
