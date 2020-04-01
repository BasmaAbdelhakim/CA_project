/************************************
 * nvic.c							              *									
 * Created on: Mar 14, 2020			    *
 * Author: Esraa Awad				        *
 * *********************************/

#include "STD_TYPES.h"
#include "nvic.h"


/**** MASKS  of numbers of sub group and preemption bits for stm23***/
#define   NVIC_PRIGROUP_CLRMask	  0xfffff8ff
#define  	NVIC_NonSubPriority			0x00000300
#define 	NVIC_OneSubthreeGroup		0x00000400
#define 	NVIC_TwoSubTwoGroup			0x00000500
#define 	NVIC_ThreeSubOneGroup		0x00000600
#define 	NVIC_NonGroupPriority		0x00000700
/********************************************************************/

#define NVIC_AIRC 		*((volatile u32*)0xE000ED0C)    // to set number of sub group bits




typedef struct
{
	u32 Padding_0[64];
	u32 SETENA0;
	u32 SETENA1;
	u32 SETENA2;
	u32 SETENA3;
	u32 SETENA4;
	u32 SETENA5;
	u32 SETENA6;
	u32 SETENA7;
	u32 Dummy_Arr1 [24];
	u32 CLRENA0;
	u32 CLRENA1;
	u32 CLRENA2;
	u32 CLRENA3;
	u32 CLRENA4;
	u32 CLRENA5;
	u32 CLRENA6;
	u32 CLRENA7;
	u32 Dummy_Arr2 [24];
	u32 SETPEND0;
	u32 SETPEND1;
	u32 SETPEND2;
	u32 SETPEND3;
	u32 SETPEND4;
	u32 SETPEND5;
	u32 SETPEND6;
	u32 SETPEND7;
	u32 Dummy_arr3[24];
	u32 CLRPEND0;
	u32 CLRPEND1;
	u32 CLRPEND2;
	u32 CLRPEND3;
	u32 CLRPEND4;
	u32 CLRPEND5;
	u32 CLRPEND6;
	u32 CLRPEND7;
	u32 Dummy_arr4[24];
	u32 ACTIVE0;
	u32 ACTIVE1;
	u32 ACTIVE2;
	u32 ACTIVE3;
	u32 ACTIVE4;
	u32 ACTIVE5;
	u32 ACTIVE6;
	u32 ACTIVE7;
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
void NVIC_u8SetPriority(u32 Copy_u8IntReqNum , u8 Copy_u8PriorityLevel)
{

		NVIC-> IPR [Copy_u8IntReqNum] = Copy_u8PriorityLevel;

}




/*Description : This API shall Enable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */

ERROR_STATUS NVIC_u8EnableIRQ (u32 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;

	if (Copy_u8IntReqNum < 32 )
	{
		NVIC -> SETENA0 |= Copy_u8IntReqNum;
	}
	else if (Copy_u8IntReqNum < 64 )
	{
		NVIC -> SETENA1 |= Copy_u8IntReqNum;
	}

	else if (Copy_u8IntReqNum < 96 )
	{

		NVIC -> SETENA2 |= Copy_u8IntReqNum;
	}

	else
	{
		Local_u8Error = status_NOk;
	}
	return (Local_u8Error);

}




/*Description : This API shall Disable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */

ERROR_STATUS NVIC_u8DisbaleIRQ (u32 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;

		if (Copy_u8IntReqNum < 32 )
		{
			NVIC -> CLRENA0 |= Copy_u8IntReqNum;
		}
		else if (Copy_u8IntReqNum < 64 )
		{
			NVIC -> CLRENA1 |= Copy_u8IntReqNum;
		}

		else if (Copy_u8IntReqNum < 96 )
		{

			NVIC -> CLRENA2 |= Copy_u8IntReqNum;
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
u8 NVIC_u8IsActive (u32 Copy_u8IntReqNum)
{
	u8 u8IsActive_val = 0;
	if (Copy_u8IntReqNum < 32)
	{
		u8IsActive_val = (NVIC -> ACTIVE0) & Copy_u8IntReqNum ;
	}
	else if (Copy_u8IntReqNum <64)
	{
		u8IsActive_val = (NVIC -> ACTIVE1) & Copy_u8IntReqNum ;
	}

	return (u8IsActive_val);
}



/*Description : This API shall get priority of interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 priority value */

u8 NVIC_u8GetPriority (u32 Copy_u8IntReqNum)
{
	u8 u8priority_val;

	u8priority_val = NVIC ->IPR [Copy_u8IntReqNum];

	return u8priority_val;

}




/*Description : This API generate software interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 ERROR STATUS*/

ERROR_STATUS NVIC_u8SWIntGenerate(u32 Copy_u8IntReqNum)  //NVIC_SetPendingIRQ(3);NVIC->STIR = 3;
{
	u8 Local_u8Error = status_Ok;
	if (Copy_u8IntReqNum <32)
	{
		NVIC -> SETPEND0 |= Copy_u8IntReqNum;
	}
	else if (Copy_u8IntReqNum < 64)
	{
		NVIC -> SETPEND1|= Copy_u8IntReqNum;
	}
	else if (Copy_u8IntReqNum < 96)
	{
		NVIC -> SETPEND2 |= Copy_u8IntReqNum;
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

ERROR_STATUS NVIC_u8ClearPending (u32 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;
		if (Copy_u8IntReqNum <32)
		{
			NVIC -> SETPEND0 &= ~Copy_u8IntReqNum;
		}
		else if (Copy_u8IntReqNum < 64)
		{
			NVIC -> SETPEND1 &= ~Copy_u8IntReqNum;
		}
		else if (Copy_u8IntReqNum < 96)
		{
			NVIC -> SETPEND2 &= ~Copy_u8IntReqNum;
		}
		else
		{
			Local_u8Error = status_NOk;
		}
		return (Local_u8Error);


}








