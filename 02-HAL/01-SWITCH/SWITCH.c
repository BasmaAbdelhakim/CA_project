/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 26 MAR 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_task.c                     */
/************************************************/

#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "GPIO.h"

#include "SWITCH.h"
#include "SWITCH_cfg.h"


u8 switchState[SWITCH_NUM];

switchmap_t * switchMapElement;

/* 
  Description: This function shall initiate the specified switch num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module

  Input: switchNum -> holds the index of the switch in the switch array 

  Output: ERROR_STATUS

 */
extern ERROR_STATUS SwitchTask_Init(u32 switchNum)
{

	ERROR_STATUS status = status_Ok;

	/* Creating GPIO element */
	GPIO_t switchElement;

	/* Creating switch element */
	switchmap_t * switchMapElement;

	/* Getting required switch configurations */
	switchMapElement = getSwitchMap(switchNum);

	/* Assigning switch element configurations to GPIO element */
	switchElement.pin = switchMapElement->pin;
	switchElement.port = switchMapElement->port;
	switchElement.mode = MODE_INPUT;
	switchElement.configuration = CONFIG_INPUT_PULL_UP_DOWN ;

	/* Initiating GPIO element */
	GPIO_initPin(&switchElement);

	/* Setting bit in ODR in case of pull up switch and reseting it in case of pull down switch */
	if (PULL_UP == switchMapElement->pullState)
	{
		GPIO_writePin (&switchElement,PIN_SET);
	}
	else if (PULL_DOWN == switchMapElement->pullState)
	{
		GPIO_writePin (&switchElement,PIN_RESET);
	}

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
extern ERROR_STATUS Switch_GetSwitchState(u32 switchNum, u8 * switchValue)
{
	ERROR_STATUS status = status_Ok;

  /* Creating switch element */
  switchmap_t * switchMapElement;
  /* Getting required switch configurations */
  switchMapElement = getSwitchMap(switchNum);

  /* Reading GPIO value */
	GPIO_directReadPin(switchMapElement->port,switchMapElement->pin,switchValue);

  /* Toggling switchValue in case of pull up switch */
  if (PULL_UP == switchMapElement->pullState)
  {
    * switchValue = * switchValue ^ 0x01;
  }

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
extern ERROR_STATUS SwitchTask_GetSwitchState(u32 switchNum, u8 * switchValue)
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
extern void switchTask (void)
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
		GPIO_directReadPin(switchMapElement->port,switchMapElement->pin,&currState);

		/* Toggling switchValue in case of pull up switch */
		if (PULL_UP == switchMapElement->pullState)
		{
			currState = currState ^ 0x01;
		}


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
