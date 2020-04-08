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



const Task_t APP_Task ={Application,30,READY};


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

	 TX_frame.fullFrame=0;
	 RX_frame.fullFrame=0;
}



/* every 30 ms  */
void Application(void)
{
	 static u32 switch_counter ;
	 static u32 ticks_counter ;
	 static u8 prevSwitchState ;
	 static u8 currentSwitchState;

	 ticks_counter++;

	/* SWITCH  TASK */
	if(ticks_counter ) //30 ms
    {
		  SwitchTask_GetSwitchState(SWITCH_1, &currentSwitchState);

		  if (currentSwitchState == PRESSED  &&  prevSwitchState == RELEASED)
		  {
			  switch_counter++;
			  TX_frame.fullFrame = switch_counter;
			  prevSwitchState = PRESSED;
		  }
		  prevSwitchState = currentSwitchState;
    }


     /*  RX TASK  */
	 if(ticks_counter % 2 == 0 )//60 ms
	 {
		UART_u8Recieve(RX_frame.data, 4);
	 }


	 /* LCD DISPLAY TASK */
	 if(ticks_counter % 3 == 0  )//90 ms
	 {
		HCLCD_writeString(RX_frame.data,4);
	 }


	 /* TX TASK */
	 if(ticks_counter % 4 == 0 )//120 ms
	 {
		UART_u8Send(TX_frame.data,4);//TX
	 }


}




