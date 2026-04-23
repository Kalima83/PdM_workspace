#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "stm32f4xx_hal.h"  // Necesario para tipos como uint32_t y funciones HAL
#include <stdbool.h>       // Para usar el tipo bool

typedef bool bool_t;

/****************** Prototipos de funciones públicas ***********************************/
void debounceFSM_init(void); //inicializa las variables
void debounceFSM_update(void); //control del boton B1
bool_t readKey(void); // Devuelve si se presionó y resetea la variable interna

#endif /* API_INC_API_DEBOUNCE_H_ */
