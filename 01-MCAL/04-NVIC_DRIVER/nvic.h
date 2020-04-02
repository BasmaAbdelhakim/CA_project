/************************************
 * nvic.c							              *								
 * Created on: Mar 14, 2020			    *
 *  Author: Esraa Awad				      *
 * *********************************/
#ifndef NVIC_H
#define NVIC_H



/**** Configuration of numbers of sub group bits for stm23***
 * options:													                        *
 *			1-NVIC_PRIGROUP								                      *
 * 			2-NVIC_NonSubPriority							                  *
 * 			3-NVIC_OneSubthreeGroup							                *
 * 			4-NVIC_TwoSubTwoGroup							                  *
 * 			5-NVIC_ThreeSubOneGroup							                *
 * 			6-NVIC_NonGroupPriority							                *
 *															                            *
 ************************************************************/

#define 	NVIC_PRIGROUP				NVIC_TwoSubTwoGroup











/******************************* FUNCTIONS PROTOTYPES **************************/


/* Description: this API shall initialize Interrupt by set the Bits number of priority sub group Bits and premation bits
 * Input: void
 * Output: void */
void NVIC_voidInitPriority (void);


/*Description: This API shall set priority of interrupt request number
 * Input:  Interrupt request number NVIC_IRQx , PriorityLevel
 * Output: void
 * */
void NVIC_u8SetPriority(u8 Copy_u8IntReqNum , u8 Copy_u8PriorityLevel);


/*Description : This API shall Enable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */
ERROR_STATUS NVIC_u8EnableIRQ (u8 Copy_u8IntReqNum);



/*Description : This API shall Disable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */
ERROR_STATUS NVIC_u8DisbaleIRQ (u8 Copy_u8IntReqNum);



/*Description : This API shall get active status of interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 active status zero if not active and larger than 1 if active */
u8 NVIC_u8IsActive (u8 Copy_u8IntReqNum);



/*Description : This API shall get priority of interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 priority value */

u8 NVIC_u8GetPriority (u8 Copy_u8IntReqNum);



/*Description : This API generate software interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 ERROR STATUS*/

ERROR_STATUS NVIC_u8SWIntGenerate(u8 Copy_u8IntReqNum);  //NVIC_SetPendingIRQ(3);NVIC->STIR = 3;



/*Description : This API clear pending of interrupt request number
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 ERROR STATUS*/

ERROR_STATUS NVIC_u8ClearPending (u8 Copy_u8IntReqNum);








#endif
