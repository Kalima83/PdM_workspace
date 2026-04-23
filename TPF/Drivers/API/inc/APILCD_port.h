/*
 * APILCD_port.h
 *
 *  Created on: 20 abr 2026
 *      Author: danie
 */

#ifndef API_INC_APILCD_PORT_H_
#define API_INC_APILCD_PORT_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/* Enumeración de estados */
typedef enum {
    LCD_OK,
    LCD_ERROR_I2C,
    LCD_ERROR_TIMEOUT
} lcd_status_t;

/* Prototipos */
void LCD_port_write_nibble(uint8_t nibble);
void LCD_port_init(void);void LCD_port_write_cmd(uint8_t cmd);   // Para comandos (RS=0)
void LCD_port_write_data(uint8_t data); // Para datos (RS=1)
void LCD_port_delay(uint32_t ms);       // Para los retardos de inicialización

#endif /* API_INC_APILCD_PORT_H_ */
