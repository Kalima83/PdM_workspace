/*
 * MPU_port.h
 *
 *  Created on: 20 abr 2026
 *      Author: danie
 */

#ifndef API_INC_MPU_PORT_H_
#define API_INC_MPU_PORT_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>


typedef bool bool_t;

/* Prototipos del driver de bajo nivel */
bool_t MPU_port_init(void);
bool_t MPU_port_write(uint8_t reg, uint8_t value);
bool_t MPU_port_read(uint8_t reg, uint8_t *pData, uint16_t size);

#endif /* API_INC_MPU_PORT_H_ */
