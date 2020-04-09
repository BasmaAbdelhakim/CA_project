
/************************************
 * Author: Esraa Awad                *
 * Date: 26/3/2020                   *
 * File: UART_Config.c               *
 * Target: STM                       *
 ************************************/
#include "../../../04-lib/STD_TYPES.h"

#include "../../../01-MCAL/02-GPIO/GPIO_interface.h"


/* 	UARTX IO configure pins */
GPIO_t HUART_GPIO_CONFIG[2] =
{

	{
		.pin   = PIN9,
		.mode  = MODE_OUTPUT_SPEED_50,
		.configuration = CONFIG_OUTPUT_ALTERNATE_FUNCTION_PUSH_PULL,
		.port  = PORTA,
	},


	{
		.pin   = PIN10,
		.mode  = MODE_INPUT,
		.configuration = CONFIG_INPUT_PULL_DOWN,
		.port  = PORTA,
	}
};

