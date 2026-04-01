#include "API_debounce.h"
#include "main.h"


/*************************Prototipos de funciones PRIVADAS **********************/
static void buttonPressed(void);
static void buttonReleased(void);
/*************************Fin prototipos de funciones PRIVADAS **********************/


/************************ Definiciones privadas************************/
typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING
} debounceState_t;


static debounceState_t state;
static uint32_t time_push;
static const uint32_t time = 40;
static bool_t keyPressedFlag = false; // Variable global privada

/************************ Fin definiciones privadas************************/


/****************************Funciones públicas*************************/

/*
* Inicializa las variables globales
*/
void debounceFSM_init()
{
	state = BUTTON_UP; // Inicializo el estado en Button_up
	keyPressedFlag = false;
}


/*
 * La función readKey debe leer una variable interna del módulo y devolver true o false si la tecla fue presionada.
 * Si devuelve true, debe resetear (poner en false) el estado de la variable
 */
bool_t readKey(void) {
    bool_t status = keyPressedFlag;
    keyPressedFlag = false; // Resetea el estado al leer
    return status;
}

/*
* debe leer las entradas, resolver la lógica de
  transición de estados y actualizar las salidas
*/

void debounceFSM_update()
{
	    bool isPressed = (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET);

	    switch (state) {
	        case BUTTON_UP:
	            if (isPressed) {
	                state = BUTTON_FALLING;
	                time_push = HAL_GetTick();
	            }
	            break;

	        case BUTTON_FALLING:
	            if ((HAL_GetTick() - time_push) >= time) {
	                if (isPressed) {
	                    state = BUTTON_DOWN;
	                    keyPressedFlag = true; // Flanco descendente detectado y validado
	                } else {
	                    state = BUTTON_UP;
	                }
	            }
	            break;

	        case BUTTON_DOWN:
	            if (!isPressed) {
	                state = BUTTON_RAISING;
	                time_push = HAL_GetTick();
	            }
	            break;

	        case BUTTON_RAISING:
	            if ((HAL_GetTick() - time_push) >= time) {
	                if (!isPressed) {
	                    state = BUTTON_UP;
	                    buttonReleased();
	                } else {
	                    state = BUTTON_DOWN;
	                }
	            }
	            break;

	        default:
	            debounceFSM_init();
	            break;
	    }
}

/****************************Fin de funciones publicas*************************/


//*****************************Funciones privadas*********************/
/*
 * Se enciende el LED
 */

void buttonPressed()
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); // Enciende LED Verde Boton B1
}

/*
* Se apaga el led
*/
void buttonReleased()
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); // Apaga LED Verde boton  B1
}

/****************************Fin de funciones privadas*************************/
