/*
 * SYSTICK_interface.h

 *
 *  Created on: Mar 9, 2020
 *      Author: Areej Ayman Helal
 */
#define AHB_CLOCK 8

#define Sys_PRESCALER PRE_AHB_div_8

#define PRE_AHB			1
#define PRE_AHB_div_8	8

void voidMYSYSTIC_init(void);
void voidMYSYSTIC_SetTime(u32 Time_US,const u32 Input_Clock );
void voidMYSYSTIC_Start(void);
void voidMYSYSTIC_Stop(void);
void voidMYSYSTIC_SetCallBack(void (*CPF)(void));
void voidMYSYSTIC_Handler(void);
