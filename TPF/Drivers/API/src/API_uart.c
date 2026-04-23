/*
 * API_uart.c
 */

#include "API_uart.h"
#include "API_uart_port.h"
#include <string.h>
#include <stddef.h>

bool_t uartInit(uint32_t baudrate) {
    if (!uartPortConfig(baudrate)) return false;

    uint8_t msg[] = "\r\n--- UART Inicializada correctamente ---\r\n";
    uartPortSend(msg, sizeof(msg)-1);
    return true;
}

void uartSendString(uint8_t * pstring) {
    if (pstring != NULL) {
        uartPortSend(pstring, (uint16_t)strlen((char*)pstring));
    }
}

bool_t uartReceiveByte(uint8_t * pByte) {
    return uartPortReceiveByte(pByte);
}
