/*
 * API_cmdparser.h
 *
 *  Created on: 22 abr 2026
 *      Author: danie
 */

#ifndef API_INC_API_CMDPARSER_H_
#define API_INC_API_CMDPARSER_H_

#include <stdbool.h>
#include <stdint.h>

/* Prototipos */
void cmdParserInit(uint32_t baudrate); // Inicializa la UART internamente
bool cmdParserUpdate(void);            // Escanea la UART y retorna true si hay orden de cambio

#endif /* API_INC_API_CMDPARSER_H_ */
