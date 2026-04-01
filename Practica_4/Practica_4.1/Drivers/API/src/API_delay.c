/*
 * API_delay.c
 *
 *  Created on: 19 mar 2026
 *      Author: daniel Bazán
 */

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"
#include <stddef.h>
#include "stm32f4xx_hal.h"


/**
 * @brief Inicializa la estructura de delay.
 */
void delayInit( delay_t * delay, tick_t duration ) {
   if( delay != NULL ) {
      delay->duration = duration;
      delay->running = false;
      delay->startTime = 0;
   }
}

/**
 * @brief Lee el estado del delay.
 * @return true si el tiempo se cumplió, false en caso contrario.
 */
bool_t delayRead( delay_t * delay ) {
   bool_t timeReached = false;

   if( delay != NULL ) {
      // Si no está corriendo, iniciamos el conteo
      if( !delay->running ) {
         delay->startTime = HAL_GetTick();
         delay->running = true;
      } else {
         // Si está corriendo, verificamos si ya pasó el tiempo
         // La resta (Actual - Inicial) maneja correctamente el overflow del tick
         if( (HAL_GetTick() - delay->startTime) >= delay->duration ) {
            timeReached = true;
            delay->running = false; // Reset para el próximo ciclo
         }
      }
   }
   return timeReached;
}

/**
 * @brief Permite cambiar la duración de un delay existente.
 */
void delayWrite( delay_t * delay, tick_t duration ) {
   if( delay != NULL ) {
      delay->duration = duration;
   }
}

// Punto 3
/**
 * @brief Verifica si el delay se encuentra en ejecución.
 * @param delay: puntero a la estructura del delay.
 * @return bool_t: copia del estado 'running'.
 */
bool_t delayIsRunning(delay_t * delay) {
    // Verificación de seguridad para evitar punteros NULL
    if (delay == NULL) {
        return false;
    }
    return delay->running;
}
