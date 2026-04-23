/*
 * APILCD_port.c
 *
 *  Created on: 20 abr 2026
 *      Author: danie
 */

#include "stm32f4xx_hal.h" // Dependencia de hardware (Capa de Portabilidad)
#include "stm32f4xx_hal_i2c.h"
#include "APILCD_port.h"


extern I2C_HandleTypeDef hi2c1; // Objeto configurado en el .ioc

// Dirección I2C de 7 bits
#define LCD_I2C_ADDR    (0x27 << 1)

// Bits de control
#define PIN_RS    (1 << 0) // Register Select
#define PIN_RW    (1 << 1) // Read/Write
#define PIN_EN    (1 << 2) // Enable
#define BACKLIGHT (1 << 3) // Control de luz de fondo

/**
 * @brief Envía un nibble (4 bits) al LCD a través de I2C
 * Implementa el protocolo I2C con verificación de ACK
 */
static lcd_status_t I2C_send(uint8_t data) {
    // Se agrega el bit de Backlight para que la pantalla siempre esté prendida
    uint8_t i2c_data = data | BACKLIGHT;

    // Transmisión I2C con control de error
    if (HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &i2c_data, 1, 100) != HAL_OK) {
        return LCD_ERROR_I2C;
    }
    return LCD_OK;
}

/**
 * @brief Ejecuta el flanco de bajada en el pin Enable (E) del LCD.
 */
static void pulse_enable(uint8_t data) {
    I2C_send(data | PIN_EN);  // EN = 1
    LCD_port_delay(1);
    I2C_send(data & ~PIN_EN); // EN = 0 (Flanco de bajada)
    LCD_port_delay(1);
}

/**
 * @brief Envía un byte completo dividiéndolo en dos nibbles (Modo 4 bits)
 */
void LCD_port_write_cmd(uint8_t cmd) {
    uint8_t up = cmd & 0xF0;        // Parte alta
    uint8_t lo = (cmd << 4) & 0xF0; // Parte baja (desplazada)

    // Para comandos, RS debe ser 0
    pulse_enable(up);
    pulse_enable(lo);
}

void LCD_port_write_data(uint8_t data) {
    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    // Para datos, RS debe ser 1
    pulse_enable(up | PIN_RS);
    pulse_enable(lo | PIN_RS);
}

void LCD_port_delay(uint32_t ms) {
    HAL_Delay(ms); // Abstracción del delay
}

/**
 * @brief Envía un solo nibble (4 bits) al LCD.
 * Usa exclusivamente para la secuencia de inicialización.
 */
void LCD_port_write_nibble(uint8_t nibble) {
    pulse_enable(nibble & 0xF0);
}
