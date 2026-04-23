/*
 * API_mpu6050.c
 *
 *  Created on: 19 abr 2026
 *      Author: danie
 */


#include "API_mpu6050.h"
#include "MPU_port.h"
#include <math.h>

#define RAD_A_DEG 57.2957795f
#define PWR_MGMT_1 0x6B
#define WHO_AM_I   0x75

/* Variables privadas */
static imu_data_t offset = {0};

/* Función privada */
static void MPU_read_raw(imu_data_t *raw);


bool_t MPU6050_Init(void) {
    uint8_t check;
    // Verifica identidad
    if (!MPU_port_read(WHO_AM_I, &check, 1) || check != 0x68) {
        return false; // El sensor no responde o no es el correcto
    }
    // Saca al sensor del modo Sleep
    return MPU_port_write(PWR_MGMT_1, 0x00);
}

// Esta función promedia 100 muestras y guarda los offsets internamente (static)
void MPU6050_Calibrate(void) {
    float sum_x = 0, sum_y = 0, sum_z = 0;
    const int num_samples = 200;

    for (int i = 0; i < num_samples; i++) {
        imu_data_t raw_data;
        MPU_read_raw(&raw_data);
        sum_x += raw_data.x;
        sum_y += raw_data.y;
        sum_z += raw_data.z;
        HAL_Delay(5);
    }
    // Guarda el promedio como el error fijo (offset)
    offset.x = sum_x / num_samples;
    offset.y = sum_y / num_samples;
    offset.z = (sum_z / num_samples) - 1.0f;
}

void MPU6050_Read_All(imu_data_t *data_out) {
    imu_data_t raw;
    MPU_read_raw(&raw);
    // Obtengo la diferencia del offset
    data_out->x = raw.x - offset.x;
    data_out->y = raw.y - offset.y;
    data_out->z = raw.z - offset.z;

    // Calcula los ángulos de inclinación
    data_out->angle_x = atan2f(data_out->y, data_out->z) * RAD_A_DEG;
    float resultante_yz = sqrtf(data_out->y * data_out->y + data_out->z * data_out->z);
    data_out->angle_y = atan2f(-data_out->x, resultante_yz) * RAD_A_DEG;
}

static void MPU_read_raw(imu_data_t *raw) {
    uint8_t buffer[6];
    if (MPU_port_read(0x3B, buffer, 6)) { // 0x3B es ACCEL_XOUT_H
        int16_t ax = (int16_t)(buffer[0] << 8 | buffer[1]);
        int16_t ay = (int16_t)(buffer[2] << 8 | buffer[3]);
        int16_t az = (int16_t)(buffer[4] << 8 | buffer[5]);
        raw->x = (float)ax / 16384.0f; // Escala +/- 2g
        raw->y = (float)ay / 16384.0f;
        raw->z = (float)az / 16384.0f;
    }
}

