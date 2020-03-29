/*
 * SYSTICK_program.c
 *
 *  Created on: Mar 9, 2020
 *      Author: Areej Ayman Helal
 */

#include "STD_TYPES.h"
#include "MYSYSTICK_interface.h"
#include "MYSYSTICK_registers.h"

/*Masks..............*/
#define  ENABLEINT         0x00000002
#define  DISABLEINT        0xFFFFFFFD
#define  ENABLETIMER       0x00000001
#define  DISABLETIMER      0xFFFFFFFE
#define  ENABLE_AHB_CLOCK  0x00000004
#define  ENABLE_AHB_8_CLOCK 0xFFFFFFFB
/*...................*/

void (*SystickCallBack)(void);

void voidMYSYSTIC_init(void)
{
	STK_CTRL |= ENABLEINT;
	STK_CTRL &= ENABLE_AHB_8_CLOCK;

}

void voidMYSYSTIC_SetTime(u32 Time_US , const u32 Input_Clock  )
{

	u32 Preload = Time_US * (Input_Clock / Sys_PRESCALER);
	STK_LOAD = Preload;
}

void voidMYSYSTIC_Start(void)
{
	STK_CTRL |= ENABLETIMER;
}

void voidMYSYSTIC_Stop(void)
{
	STK_CTRL &= DISABLETIMER;
}

void voidMYSYSTIC_SetCallBack(void (*CPF)(void))
{
	if (CPF)
	{
		SystickCallBack = CPF;
	}
}

void SysTick_Handler(void)
{
	if(SystickCallBack)
	{
		SystickCallBack();
	}
}
