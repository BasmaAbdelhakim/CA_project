/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 26 MAR 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_task.c                     */
/************************************************/

#include "../../04-lib/STD_TYPES.h"

#include "../../01-MCAL/01-RCC/RCC_interface.h"
#include "../../01-MCAL/02-GPIO/GPIO_interface.h"

#include "../../05-OS/SCHEDULER_interface.h"


#include "SWITCH_interface.h"
#include "SWITCH_config.h"

const Task_t Switch_Task ={switchTask,4,READY};

u8 switchState[SWITCH_NUM];

switchmap_t * switchMapElement;


/* 
  Description: This function shall initiate the specified switch num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module

  Input: switchNum -> holds the index of the switch in the switch array 

  Output: ERROR_STATUS

 */
ERROR_STATUS Switch_Init(u32 switchNum)
{

	ERROR_STATUS status = status_Ok;

	/* Creating switch element */
	switchmap_t * switchMapElement;

	/* Getting required switch configurations */
	switchMapElement = getSwitchMap(switchNum);

	/* Initiating GPIO element */
	GPIO_initPin(&switchMapElement->switchElementIO);

	return status;
}


/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED

  Input:
        1- switchNum which holds the index of the switch in the switch array
        2- switchValue -> Pointer to hold the switch value

  Output: status_t

 */
ERROR_STATUS Switch_GetSwitchState(u32 switchNum, u8 * switchValue)
{
	ERROR_STATUS status = status_Ok;

  /* Creating switch element */
  switchmap_t * switchMapElement;
  /* Getting required switch configurations */
  switchMapElement = getSwitchMap(switchNum);

  /* Reading GPIO value */
  GPIO_readPin(&switchMapElement->switchElementIO,switchValue);

  return status;

}


/*
  Description: This function shall return the specified switch state which can be
  PRESSED or RELEASED using SCHEDULER

  Input: 
        1- switchNum which holds the index of the switch in the switch array 
        2- switchValue -> Pointer to hold the switch value

  Output: ERROR_STATUS

 */
ERROR_STATUS SwitchTask_GetSwitchState(u32 switchNum, u8 * switchValue)
{

	ERROR_STATUS status = status_Ok;

	*switchValue = switchState[switchNum];

	return status;

}

/*
  Description: This function is the switch scheduler task

  Input: void

  Output: void

 */
void switchTask (void)
{
	static u8 prevState[SWITCH_NUM];
	static u8 currState;
	static u8 counter[SWITCH_NUM];

	u8 localSwitchLoop;

	/* Looping on existed switches */
	for (localSwitchLoop = 0; localSwitchLoop < SWITCH_NUM; localSwitchLoop ++)
	{

		/* Getting required switch configurations */
		switchMapElement = getSwitchMap(localSwitchLoop);

		/* Reading GPIO value */
		GPIO_readPin(&switchMapElement->switchElementIO,&currState);
		

		if (currState == prevState[localSwitchLoop])
		{
			counter[localSwitchLoop]++;
		}
		else
		{
			counter[localSwitchLoop] =0;
		}

    /* If the state is the same for fixed number of counts, then the recent current state is the actual state*/
		if (counter[localSwitchLoop] == MAX_COUNTS)
		{
			switchState[localSwitchLoop] = currState;
			counter[localSwitchLoop] =0;
		}

		prevState[localSwitchLoop] = currState;
	}



}
