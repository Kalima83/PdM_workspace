/*
 * API_delay.h
 *
 *  Created on: 19 mar 2026
 *      Author: danie
 */

#ifndef API_API_DELAY_H_
#define API_API_DELAY_H_

// Librerias
#include <stdint.h>  // Para uint32_t
#include <stdbool.h> // Para el tipo bool
#include "main.h"

typedef uint32_t tick_t;
typedef bool bool_t;

// estructura

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

typedef struct {
    tick_t period;
    uint8_t iterations;
} sequence_t;

/* Fin  definiciones  */


// Funciones

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
bool_t delayIsRunning(delay_t * delay);


#endif /* API_API_DELAY_H_ */
