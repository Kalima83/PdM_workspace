/*
 * API/inc/API_cmdparser.h
*/

#ifndef API_INC_API_CMDPARSER_H_
#define API_INC_API_CMDPARSER_H_

#include "API_uart.h"
#include <stdint.h>
#include <stdbool.h>

#define CMD_MAX_LINE    64   // Incluye '\0'
#define CMD_MAX_TOKENS  3    // COMANDO + máximo 2 argumentos

typedef enum {
    CMD_OK = 0,
    CMD_ERR_OVERFLOW,
    CMD_ERR_SYNTAX,
    CMD_ERR_UNKNOWN,
    CMD_ERR_ARG
} cmd_status_t;

/* Prototipos obligatorios */
void cmdParserInit(void);
void cmdPoll(void);
void cmdPrintHelp(void);

#endif
