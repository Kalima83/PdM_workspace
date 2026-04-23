/*
 * MPU_port.c
 *
 *  Created on: 20 abr 2026
 *      Author: danie
 */


#include "MPU_port.h"

extern I2C_HandleTypeDef hi2c1;

/* Dirección de 7 bits desplazada */
#define MPU_ADDR (0x68 << 1)

bool_t MPU_port_write(uint8_t reg, uint8_t value) {
    /* Implementa: START -> ADDR+W -> REG -> DATA -> STOP */
    if (HAL_I2C_Mem_Write(&hi2c1, MPU_ADDR, reg, 1, &value, 1, 100) != HAL_OK) {
        return false; // Error de ACK: Evento para estado ERROR - Tabla 1
    }
    return true;
}

bool_t MPU_port_read(uint8_t reg, uint8_t *pData, uint16_t size) {
    /* Implementa: START -> ADDR+W -> REG -> REPEATED START -> ADDR+R -> DATA -> STOP */
    if (HAL_I2C_Mem_Read(&hi2c1, MPU_ADDR, reg, 1, pData, size, 100) != HAL_OK) {
        return false; // Error de comunicación
    }
    return true;
}
