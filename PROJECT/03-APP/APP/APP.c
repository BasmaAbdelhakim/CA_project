/*
 * APP.c
 *
 *  Created on: Apr 5, 2020
 *      Author: kimoz
 */


#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "../../../04-lib/STD_TYPES.h"
#include "../../../01-MCAL/01-RCC/RCC_interface.h"
#include "../../../01-MCAL/02-GPIO/GPIO_interface.h"
#include "../../../01-MCAL/05-UART/UART_interface.h"
#include "../../../05-OS/SCHEDULER_interface.h"
#include "../../../02-HAL/02-HCLCD/HCLCD_interface.h"
#include "../../../02-HAL/01-SWITCH/SWITCH_interface.h"
#include "APP.h"



const Task_t APP_Task ={Application,20,READY};


typedef union
{
    uint8_t data[4];
    uint32_t fullFrame;

}frame_t;

frame_t  TX_frame, RX_frame;





void APP_Init(void)
{
	RCC_EnablePrephiralClock(APB2ENR_BUS, PORTA_Enable);
	RCC_EnablePrephiralClock(APB2ENR_BUS, PORTB_Enable);
	RCC_EnablePrephiralClock(APB2ENR_BUS, UART_Enable);

	Switch_Init(SWITCH_1);

	HCLCD_init();

	UART_voidInit();
}



/* every 20 ms  */
void Application(void)
{
	 char string_Buffer[20];
	 static u32 switch_counter ;
	 static u32 ticks_counter ;
	 static u8 prevSwitchState = RELEASED;
	 static u8 currentSwitchState = RELEASED;


	/* SWITCH READ TASK */
	if(ticks_counter % 1 == 0) //20 ms
    {
		  SwitchTask_GetSwitchState(SWITCH_1, &currentSwitchState);

		  if (currentSwitchState == PRESSED  &&  prevSwitchState == RELEASED)
		  {
			  switch_counter++;
			  trace_printf("switch_counter  =  %d  ", switch_counter);
			  prevSwitchState = PRESSED;

			  TX_frame.fullFrame = switch_counter;
		  }
		  prevSwitchState = currentSwitchState;
    }


     /*  RX TASK  */
	 else if(ticks_counter % 3 == 0 )//60 ms
	 {
		UART_u8Recieve(RX_frame.data, 4);
	 }


	 /* LCD DISPLAY TASK */
	 else if(ticks_counter % 5 == 0 )//100 ms
	 {
		itoa(RX_frame.fullFrame,string_Buffer,10);
		HCLCD_writeString((u8*)string_Buffer,1);
	 }


	 /* TX TASK */
	 else if(ticks_counter % 6 == 0 )//120 ms
	 {
		UART_u8Send(TX_frame.data,4);
	 }

	 else
	 {}

}




