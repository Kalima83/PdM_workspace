/*
 * API_uart_port.c
 *
 *  Created on: 22 abr 2026
 *      Author: danie
 */

#include "API_uart_port.h"
#include <stdint.h>
#include <string.h>
#include <stddef.h>

// La estructura huart2
static UART_HandleTypeDef huart2;

bool_t uartPortConfig(uint32_t baudrate) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = baudrate;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        return false;
    }
    return true;
}

/*
 * función de envío para que la capa alto nivel
 */

void uartPortSend(uint8_t *pdata, uint16_t size) {
    if (pdata != NULL && size > 0) {
        HAL_UART_Transmit(&huart2, pdata, size, 100);
    }
}

bool_t uartPortReceiveByte(uint8_t *pByte) {
    return (HAL_UART_Receive(&huart2, pByte, 1, 0) == HAL_OK);
}


