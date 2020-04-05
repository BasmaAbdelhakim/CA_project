
/*******************************************************************************
 *  FILE         : SYSTICK_interface.h     			                           *
 *  VERSION      : 1.0                                                         *
 *  AUTHOR       : kariman                                                     *
 *  DATE         : 20 March 2020                                               *
 *******************************************************************************/

#ifndef _SYSTICK_INTERFACE_H_
#define _SYSTICK_INTERFACE_H_


/******************************************** Macros *******************************************************/

#define  CLK_PRESCALER_AHB_DIV_8        0x00000000
#define  CLK_PRESCALER_AHB_DIV_1        0x00000004


/******************************************** functions prototypes ******************************************/


/******************************************************************
 * Description : Function to initialize Systick
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SYSTICK_Init(void);


/******************************************************************
 * Description : Function to start Systick
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SYSTICK_Start(void);


/******************************************************************
 * Description : Function to stop Systick
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SYSTICK_Stop(void);


/******************************************************************
 * Description  : Function to set timer value
 * Return Type  : void
 * Input Argument : (u32) Time in msec
 *****************************************************************/
extern void SYSTICK_SetTimerMS(u32 TimeMS);


/*************************************************************************
 * Description : Function to set the  callback function
 * Return Type : Return status
 *                        status_Ok  : if the input argument is correct
 *                        status_NOk : if input argument is null
 *
 * Input Argument : pointer to function
 **************************************************************************/
extern u8 SYSTICK_SetCallBack( void(*Cbf)(void));



#endif
