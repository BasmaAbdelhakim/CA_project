/*******************************************************************************
 *  FILE         : SYSTICK_program.c      			                           *
 *  VERSION      : 1.0                                                         *
 *  AUTHOR       : kariman                                                     *
 *  DATE         : 20 March 2020                                               *
 *******************************************************************************/

#include "../../04-lib/STD_TYPES.h"

#include "SYSTICK_config.h"
#include "SYSTICK_interface.h"




/***************************************** MASKS *****************************************************/

#define SYSTICK_DISABLE_MASK       (u32)0xFFFFFFFE
#define SYSTICK_ENABLE_MASK        (u32)0x00000001
#define SYSTICK_INTERRUPT_ENABLE   (u32)0x00000002

/***************************************** REGISTERS **************************************************/

#define SYSTICK_BASE_ADDRESS       (u32)0xE000E010

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
  
}SYSTICK_Reg;

volatile SYSTICK_Reg* const SYSTICK  = (SYSTICK_Reg*) SYSTICK_BASE_ADDRESS;


/********************************** static functions prototypes **************************************/

static void(*SYSTICK_CallBack)(void);


/**************************************** FUNCTIONS DEFINITION **************************************************/


/******************************************************************
 * Description : Function to initialize Systick
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SYSTICK_Init(void)
{
	SYSTICK->CTRL |= (CLK_PRESCALER | SYSTICK_INTERRUPT_ENABLE);
}

/******************************************************************
 * Description : Function to start Systick
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SYSTICK_Start(void)
{
  SYSTICK->CTRL |= SYSTICK_ENABLE_MASK;
}

/******************************************************************
 * Description : Function to stop Systick
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SYSTICK_Stop(void)
{
	SYSTICK->CTRL &= SYSTICK_DISABLE_MASK;
}

/******************************************************************
 * Description  : Function to set timer value
 * Return Type  :  void
 * Input Argument : (u32) Time in msec
 *****************************************************************/
extern void SYSTICK_SetTimerMS(u32 TimeMS)
{
	u8 PRESCALER;

    #if CLK_PRESCALER == CLK_PRESCALER_AHB_DIV_8

		   PRESCALER= 8;
    #else

		   PRESCALER= 1;
   #endif

	SYSTICK->LOAD =( ( (CLK_FREQUENCY_HZ/PRESCALER)  * TimeMS )   /1000 ) - 1;//N-1
	SYSTICK->VAL=0;
}


/*************************************************************************
 * Description : Function to set the  callback function
 * Return Type : return status
 *                        status_Ok  : if the input argument is correct
 *                        status_NOk : if input argument is null
 *
 * Input Argument : pointer to function
 **************************************************************************/
extern u8 SYSTICK_SetCallBack( void(*Cbf)(void))
{
	u8 Status = status_Ok ;
	if(Cbf)
	{
		SYSTICK_CallBack = Cbf;
	}
	else
	{
		Status= status_NOk;
	}
    return Status;
}


/****************************************************************************************************
 * Description : Systick handler to call the notification function
 * Return Type : void
 * Input Argument :  void
 ****************************************************************************************************/
void SysTick_Handler(void)
{
    if(SYSTICK_CallBack)
    {
    	SYSTICK_CallBack();
    }
}

