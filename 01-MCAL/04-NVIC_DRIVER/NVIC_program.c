/************************************
 * nvic.c							              *									
 * Created on: Mar 14, 2020			    *
 * Author: Esraa Awad				        *
 * *********************************/

#include "STD_TYPES.h"

#include "NVIC_interface.h"



/**** MASKS  of numbers of sub group and preemption bits for stm23***/
#define   NVIC_PRIGROUP_CLRMask	  0xfffff8ff
#define  	NVIC_NonSubPriority			0x00000300
#define 	NVIC_OneSubthreeGroup		0x00000400
#define 	NVIC_TwoSubTwoGroup			0x00000500
#define 	NVIC_ThreeSubOneGroup		0x00000600
#define 	NVIC_NonGroupPriority		0x00000700
/********************************************************************/

#define   NVIC_AIRC 		  *((volatile u32*)0xE000ED0C)    // to set number of sub group bits
#define 	MAX_NUM_IRQ 		240
#define 	BITS_NUM			  32




typedef struct
{
	u32 Padding_0[64];
	u32 SETENA[8];
	u32 Dummy_Arr1[24];
	u32 CLRENA[8];
	u32 Dummy_Arr2[24];
	u32 SETPEND[8];
	u32 Dummy_arr3[24];
	u32 CLRPEND[8];
	u32 Dummy_arr4[24];
	u32 ACTIVE[8];
	u32 Dummy_arr5[56];
	u8  IPR[240];
	u32 Dummy_arr6[644];
	u32 STIR;            

}NVIC_t;

NVIC_t * NVIC = (const NVIC_t *)0xE000E000;





/* Description: this API shall initialize Interrupt by set the Bits number of priority sub group Bits and premation bits
 * Input: void
 * Output: void */
void NVIC_voidInitPriority (void)
{
	/*set number of priority sub group Bits and preemption bits (8:10)  */

	NVIC_AIRC &= NVIC_PRIGROUP_CLRMask ;
	NVIC_AIRC |= NVIC_PRIGROUP;
}



/*Description: This API shall set priority of interrupt request number
 * Input:  Interrupt request number 0:240 , PriorityLevel
 * Output: void
 * */
void NVIC_u8SetPriority(u8 Copy_u8IntReqNum , u8 Copy_u8PriorityLevel)
{

		NVIC-> IPR [Copy_u8IntReqNum] = Copy_u8PriorityLevel;

}




/*Description : This API shall Enable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */

ERROR_STATUS NVIC_u8EnableIRQ (u8 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;
  
  if (Copy_u8IntReqNum < MAX_NUM_IRQ)
	{
		NVIC -> SETENA [Copy_u8IntReqNum/BITS_NUM] |= (1<<(Copy_u8IntReqNum % BITS_NUM));
	}
\
	else
	{
		Local_u8Error = status_NOk;
	}
	return (Local_u8Error);

}




/*Description : This API shall Disable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */

ERROR_STATUS NVIC_u8DisbaleIRQ (u8 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;

		if (Copy_u8IntReqNum < MAX_NUM_IRQ)
		{
      NVIC -> CLRENA [Copy_u8IntReqNum/BITS_NUM] |= (1<<(Copy_u8IntReqNum % BITS_NUM));
		}
		else
		{
			Local_u8Error = status_NOk;
		}
		return (Local_u8Error);
}


/*Description : This API shall get active status of interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 active status zero if not active and larger than 1 if active */
u8 NVIC_u8IsActive (u8 Copy_u8IntReqNum)
{
	u8 u8IsActive_val = 0;
	if (Copy_u8IntReqNum <MAX_NUM_IRQ)
		{
			u8IsActive_val = (NVIC -> ACTIVE[Copy_u8IntReqNum/BITS_NUM]) &  (1<< (Copy_u8IntReqNum % BITS_NUM));
		}

	return (u8IsActive_val);
}



/*Description : This API shall get priority of interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 priority value */

u8 NVIC_u8GetPriority (u8 Copy_u8IntReqNum)
{
	u8 u8priority_val;

	u8priority_val = NVIC ->IPR [Copy_u8IntReqNum];

	return u8priority_val;

}




/*Description : This API generate software interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 ERROR STATUS*/

ERROR_STATUS NVIC_u8SWIntGenerate(u8 Copy_u8IntReqNum)  //NVIC_SetPendingIRQ(3);NVIC->STIR = 3;
{
	u8 Local_u8Error = status_Ok;
	if (Copy_u8IntReqNum < MAX_NUM_IRQ)
			{
				NVIC -> SETPEND [Copy_u8IntReqNum/BITS_NUM] |= (1<<(Copy_u8IntReqNum % BITS_NUM));
			}
	else
	{
		Local_u8Error = status_NOk;
	}
	return (Local_u8Error);

}





/*Description : This API clear pending of interrupt request number
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 ERROR STATUS*/

ERROR_STATUS NVIC_u8ClearPending (u8 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;
	if (Copy_u8IntReqNum < MAX_NUM_IRQ)
			{
				NVIC -> CLRPEND [Copy_u8IntReqNum/BITS_NUM] |= (1<<(Copy_u8IntReqNum % BITS_NUM));
			}
	else
	{
		Local_u8Error = status_NOk;
	}
	return (Local_u8Error);


}








