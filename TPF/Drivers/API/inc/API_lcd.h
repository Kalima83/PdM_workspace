/*
 * API_lcd.h
 *
 *  Created on: 19 abr 2026
 *      Author: danie
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;

/* Funciones públicas para el main */
bool_t LCD_init(void);
void LCD_clear(void);
void LCD_write_string(char* str);
void LCD_mostrarDatosEnLCD(float x, float y);
void LCD_goto_xy(uint8_t x, uint8_t y);

#endif /* API_INC_API_LCD_H_ */
