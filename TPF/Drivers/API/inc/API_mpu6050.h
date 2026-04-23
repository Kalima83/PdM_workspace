/*
 * API_mpu6050.h
 *
 *  Created on: 19 abr 2026
 *      Author: danie
 */

#ifndef API_INC_API_MPU6050_H_
#define API_INC_API_MPU6050_H_

#include <stdbool.h>
#include <stdint.h>

typedef bool bool_t;

/* Estructura para los datos */
typedef struct {
    float x;
    float y;
    float z;
    float angle_x;
    float angle_y;
} imu_data_t;

/* Prototipos de la API - Nivel Aplicación */

/*
 * @brief Inicializa el sensor MPU6050 y verifica comunicación.
 */
bool_t MPU6050_Init(void);

/**
 * @brief Realiza la toma de muestras para eliminar el offset.
 * "Debe llamarse con la placa en reposo y horizontal".
 */
void MPU6050_Calibrate(void);

/**
 * @brief Lee los datos ya procesados (con offset restado) - calcula ángulos.
 */
void MPU6050_Read_All(imu_data_t *accel);

#endif /* API_INC_API_MPU6050_H_ */
