/*
 * API/src/API_cmdparser.c
*/

#include "API_cmdparser.h"
#include "API_uart.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <ctype.h>

/*
 * Definición de estados
 */
typedef enum {
    CMD_IDLE,
    CMD_RECEIVING,
    CMD_PROCESS,
    CMD_EXEC,
    CMD_ERROR
} cmd_state_t;

/*
 * Variables privadas
 */

static cmd_state_t estadoActual = CMD_IDLE;
static uint8_t buffer[CMD_MAX_LINE];
static uint8_t indice = 0;
static cmd_status_t ultimoError = CMD_OK;

/*
 * Prototipos de funciones privadas
 */

static void cmdProcessLine(void);
static void toUpperCase(char* str);

void cmdParserInit(void) {
    estadoActual = CMD_IDLE;
    indice = 0;
    uartInit();
}

void cmdPoll(void) {
    uint8_t c = 0;

    // Eco básico y recepción de caracteres
    uartReceiveStringSize(&c, 1);

    if (c != 0) {
        // Enviar eco del carácter recibido
        uartSendStringSize(&c, 1);

        switch (estadoActual) {
            case CMD_IDLE:
                // Espera primer carácter que no sea terminador o comentario
                if (c != '\r' && c != '\n' && c != ' ' && c != '#' && c != '/') {
                    indice = 0;
                    buffer[indice++] = c;
                    estadoActual = CMD_RECEIVING;
                }
                break;

            case CMD_RECEIVING:
                if (c == '\r' || c == '\n') {
                    buffer[indice] = '\0';
                    estadoActual = CMD_PROCESS;
                } else {
                    if (indice < (CMD_MAX_LINE - 1)) {
                        buffer[indice++] = c;
                    } else {
                        ultimoError = CMD_ERR_OVERFLOW;
                        estadoActual = CMD_ERROR;
                    }
                }
                break;

            default:
                break;
        }
    }

    // Procesamiento de la MEF para estados sin entrada de caracteres
    switch (estadoActual) {
        case CMD_PROCESS:
            // Validación de línea y tokenización
            cmdProcessLine();
            break;

        case CMD_EXEC:
            // Ejecución de la acción y retorno a IDLE
            // La acción ya se ejecutó en ProcessLine o se dispara aquí
            estadoActual = CMD_IDLE;
            break;

        case CMD_ERROR:
            // Imprime mensaje de error según el código
            if (ultimoError == CMD_ERR_OVERFLOW) {
                uartSendString((uint8_t*)"\r\nError: Buffer Overflow\r\n");
            } else {
                uartSendString((uint8_t*)"\r\nError: Command Unknown\r\n");
            }
            estadoActual = CMD_IDLE;
            break;

        default:
            break;
    }
}

/**
 * @brief Procesa la línea acumulada
 */
static void cmdProcessLine(void) {
    // Convierte a mayúsculas para que sea case-insensitive
    toUpperCase((char*)buffer);

    if (strcmp((char*)buffer, "HELP") == 0) {
        cmdPrintHelp();
        estadoActual = CMD_EXEC;
    }
    else if (strcmp((char*)buffer, "LED ON") == 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        uartSendString((uint8_t*)"\r\nLED IS ON\r\n");
        estadoActual = CMD_EXEC;
    }
    else if (strcmp((char*)buffer, "LED OFF") == 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        uartSendString((uint8_t*)"\r\nLED IS OFF\r\n");
        estadoActual = CMD_EXEC;
    }
    else if (strcmp((char*)buffer, "STATUS") == 0) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET) {
            uartSendString((uint8_t*)"\r\nLED IS ON\r\n");
        } else {
            uartSendString((uint8_t*)"\r\nLED IS OFF\r\n");
        }
        estadoActual = CMD_EXEC;
    }
    else {
        ultimoError = CMD_ERR_UNKNOWN;
        estadoActual = CMD_ERROR;
    }
}

void cmdPrintHelp(void) {
    uartSendString((uint8_t*)"\r\nComandos: HELP, LED ON, LED OFF, STATUS\r\n");
}

/**
 * @brief Convierte una cadena a mayúsculas (Helper)
 */
static void toUpperCase(char* str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}
