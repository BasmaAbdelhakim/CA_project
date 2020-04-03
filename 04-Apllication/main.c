#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "SYSTICK_interface.h"
#include "SCHEDULER_interface.h"

#include "HCLCD_interface.h"
#include "SWITCH_interface.h"
#include "SWITCH_config.h"



void Application(void);
Task_t APP_Task ={Application,20,READY};

u8 SENT_DATA [255];
u8 RECEVIED_DATA [255];


int main(int argc, char* argv[]) {

	RCC_EnablePrephiralClock(APB2ENR_BUS, PORTA_Enable);
	RCC_EnablePrephiralClock(APB2ENR_BUS, PORTB_Enable);
	RCC_EnablePrephiralClock(APB2ENR_BUS, UART_Enable);

	UART_voidInit();

	SwitchTask_Init(SWITCH_COUNTER);
	HCLCD_init();

	SCHEDULER_Init();
	SCHEDULER_Start();
}

/* every 20 ms  */
void Application(void) {

	static u16 counter ;
	static u8 switchrecievedValue = 0;
	static u8 switchTransmittedValue = 0;
	char * Stingvalue=0;
	u8 switchState;

	counter ++;


	 if(counter % 1 == 0) //20 ms
	 {
		SwitchTask_GetSwitchState(SWITCH_COUNTER,&switchState);

		if (switchState == 1)
		{
			switchTransmittedValue++;
		}
	 }

	 else if(counter % 3 == 0 )//60 ms
	 {
		UART_u8Recieve(RECEVIED_DATA, 1);
		switchrecievedValue = RECEVIED_DATA[0];

	 }

	 else if(counter % 5 == 0 )//100 ms
	 {
		itoa(switchrecievedValue,Stingvalue,10);
		HCLCD_writeString((const u8*)Stingvalue,1);

	 }

	 else if(counter % 6 == 0 )//120 ms
	 {
		UART_u8Send(&switchTransmittedValue,1);

	 }
	 else
	 {

	 }


}





#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
