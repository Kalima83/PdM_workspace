/*
 * API_uart.c
 */

#include "API_uart.h"
#include "stm32f4xx_hal.h"
#include <string.h>

/*
 Estructura de control de la UART
 */

static UART_HandleTypeDef huart2;


/*
 * Definiciones privadas
 */

#define UART_TIMEOUT 100
#define MAX_BUFFER_SIZE 256

/**
 * @brief Configura e inicializa el periférico UART2 a 115200, 8N1.
 * @return true si el hardware se inicializa correctamente.
 */
bool_t uartInit() {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        return false;
    }

    uint8_t msg[] = "\n\r--- UART Inicializada ---\n\r";
    HAL_UART_Transmit(&huart2, msg, sizeof(msg)-1, UART_TIMEOUT);

    return true;
}

/**
 * @brief Envía una cadena de caracteres terminada en cero por UART.
 * @param pstring: Puntero a la cadena de caracteres.
 */
void uartSendString(uint8_t * pstring) {
    if (pstring == NULL) {
        return;
    }
    uint16_t length = (uint16_t)strlen((char*)pstring);
    uartSendStringSize(pstring, length);
}

/**
 * @brief Envía una cantidad específica de bytes por UART.
 * @param pstring: Puntero a los datos.
 * @param size: Cantidad de bytes a transmitir.
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size) {
    if (pstring == NULL || size == 0 || size > MAX_BUFFER_SIZE) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        return;
    }

    if (HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT) != HAL_OK) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}

/**
 * @brief Recibe una cantidad específica de bytes por UART en modo polling.
 * @param pstring: Puntero donde se almacenarán los datos recibidos.
 * @param size: Cantidad de bytes a recibir.
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
    if (pstring == NULL || size == 0 || size > MAX_BUFFER_SIZE) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        return;
    }

    // Ejecuta la recepción con un tiempo de espera reducido para evitar bloqueos del sistema
    if (HAL_UART_Receive(&huart2, pstring, size, 10) == HAL_OK) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}
