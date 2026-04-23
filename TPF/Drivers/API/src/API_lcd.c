/*
 * API_lcd.c
 *
 *  Created on: 19 abr 2026
 *      Author: danie
 */

#include "API_delay.h"
#include <stdbool.h>
#include <stdio.h>
#include "API_lcd.h"     // capa alto nivel
#include "APILCD_port.h" // capa bajo nivel


#define LCD_CLR             0x01
#define LCD_HOME            0x02
#define LCD_ENTRY_MODE      0x06
#define LCD_DISP_CTRL       0x0C
#define LCD_FUNC_SET        0x28 // 4 bits, 2 líneas, 5x8 dots

/**
 * @brief Inicialización
 */
bool_t LCD_init(void) {
    LCD_port_delay(50); //tiempo para estabilizar la energía

    // Secuencia de reset enviando SOLO UN NIBBLE
    LCD_port_write_nibble(0x30);
    LCD_port_delay(5);
    LCD_port_write_nibble(0x30);
    LCD_port_delay(1);
    LCD_port_write_nibble(0x30);
    LCD_port_delay(1);

    // Pasar a modo 4 bits (SOLO UN NIBBLE)
    LCD_port_write_nibble(0x20);
    LCD_port_delay(1);

    LCD_port_write_cmd(LCD_FUNC_SET);   // 0x28: 4 bits, 2 líneas, 5x8
    LCD_port_write_cmd(LCD_DISP_CTRL);  // 0x0C: Display ON, Cursor OFF
    LCD_port_write_cmd(LCD_CLR);        // 0x01: Limpiar pantalla
    LCD_port_delay(2);
    LCD_port_write_cmd(LCD_ENTRY_MODE); // 0x06: Incrementar cursor a la derecha

    return true;
}

/**
 * @brief Imprime una cadena de caracteres (Nivel PdM)
 */
void LCD_write_string(char* str) {
    while (*str) {
        LCD_port_write_data(*str++); // Envía cada char con RS=1
    }
}

/**
 * @brief Posiciona el cursor (Nivel PdM)
 */
void LCD_goto_xy(uint8_t row, uint8_t col) {
    uint8_t address;
    switch (row) {
        case 0: address = 0x80 + col; break;
        case 1: address = 0xC0 + col; break;
        case 2: address = 0x94 + col; break;
        case 3: address = 0xD4 + col; break;
        default: address = 0x80;
    }
    LCD_port_write_cmd(address);
}

/**
 * @brief Muestra los ángulos de inclinación formateados
 * @param x: Ángulo en el eje X
 * @param y: Ángulo en el eje Y
 */
void LCD_mostrarDatosEnLCD(float x, float y) {
    char buffer[17]; // Buffer para una línea de 16 caracteres + null

    // Línea 0: Título o estado
    LCD_goto_xy(0, 0);
    LCD_write_string("Angulos:        ");
    // Línea 1: Formatea X e Y
    LCD_goto_xy(1, 0);
    sprintf(buffer, "X:%4.1f  Y:%4.1f", x, y);
    LCD_write_string(buffer);
}

/**
 * @brief Limpia la pantalla
 */
void LCD_clear(void) {
    LCD_port_write_cmd(LCD_CLR);
    LCD_port_delay(2);
}
