/*
 * API_cmdparser.c
 *
 *  Created on: 22 abr 2026
 *      Author: danie
 */


#include "API_cmdparser.h"
#include "API_uart.h"

void cmdParserInit(uint32_t baudrate) {
    uartInit(baudrate);
}

bool cmdParserUpdate(void) {
    uint8_t c;
    if (uartReceiveByte(&c)) {
             if (c == 's' || c == 'S') {
            uartSendString((uint8_t*)"Comando 'Switch' recibido\r\n");
            return true;
        }
    }
    return false;
}
