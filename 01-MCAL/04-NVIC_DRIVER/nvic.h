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

/******************************** Interrupts Requests Numbers (240) *************************/
#define 	NVIC_IRQ0  						0x00000001
#define 	NVIC_IRQ1  						0x00000002
#define 	NVIC_IRQ2  						0x00000004
#define 	NVIC_IRQ3  						0x00000008
#define 	NVIC_IRQ4  						0x00000010
#define 	NVIC_IRQ5  						0x00000020
#define 	NVIC_IRQ6  						0x00000040
#define 	NVIC_IRQ7  						0x00000080
#define 	NVIC_IRQ8  						0x00000100
#define 	NVIC_IRQ9  						0x00000200
#define 	NVIC_IRQ10  					0x00000400
#define 	NVIC_IRQ11  					0x00000800
#define 	NVIC_IRQ12 						0x00001000
#define 	NVIC_IRQ13 						0x00002000
#define 	NVIC_IRQ14  					0x00004000
#define 	NVIC_IRQ15  					0x00008000
#define 	NVIC_IRQ16  					0x00010000
#define 	NVIC_IRQ17  					0x00020000
#define 	NVIC_IRQ18  					0x00040000
#define 	NVIC_IRQ19  					0x00080000
#define 	NVIC_IRQ20  					0x00100000
#define 	NVIC_IRQ21  					0x00200000
#define 	NVIC_IRQ22  					0x00400000
#define 	NVIC_IRQ23  					0x00800000
#define 	NVIC_IRQ24  					0x01000000
#define 	NVIC_IRQ25  					0x02000000
#define 	NVIC_IRQ26  					0x04000000
#define 	NVIC_IRQ27  					0x08000000
#define 	NVIC_IRQ28  					0x10000000
#define 	NVIC_IRQ29  					0x20000000
#define 	NVIC_IRQ30  					0x40000000
#define 	NVIC_IRQ31  					0x80000000
#define 	NVIC_IRQ32  					0x00000001
#define 	NVIC_IRQ33  					0x00000002
#define 	NVIC_IRQ34  					0x00000004
#define 	NVIC_IRQ35  					0x00000008
#define 	NVIC_IRQ36  					0x00000010
#define 	NVIC_IRQ37  					0x00000020
#define 	NVIC_IRQ38  					0x00000040
#define 	NVIC_IRQ39  					0x00000080
#define 	NVIC_IRQ40  					0x00000100
#define 	NVIC_IRQ41  					0x00000200
#define 	NVIC_IRQ42  					0x00000400
#define 	NVIC_IRQ43  					0x00000800
#define 	NVIC_IRQ44 						0x00001000
#define 	NVIC_IRQ45 						0x00002000
#define 	NVIC_IRQ46  					0x00004000
#define 	NVIC_IRQ47  					0x00008000
#define 	NVIC_IRQ48  					0x00010000
#define 	NVIC_IRQ49  					0x00020000
#define 	NVIC_IRQ50 						0x00040000
#define 	NVIC_IRQ51  					0x00080000
#define 	NVIC_IRQ52  					0x00100000
#define 	NVIC_IRQ53  					0x00200000
#define 	NVIC_IRQ54  					0x00400000
#define 	NVIC_IRQ55  					0x00800000
#define 	NVIC_IRQ56  					0x01000000
#define 	NVIC_IRQ57  					0x02000000
#define 	NVIC_IRQ58  					0x04000000
#define 	NVIC_IRQ59  					0x08000000
#define 	NVIC_IRQ60  					0x10000000
#define 	NVIC_IRQ61  					0x20000000
#define 	NVIC_IRQ62  					0x40000000
#define 	NVIC_IRQ63  					0x80000000
#define 	NVIC_IRQ64  					0x00000001
#define 	NVIC_IRQ65 						0x00000002
#define 	NVIC_IRQ66  					0x00000004
#define 	NVIC_IRQ67  					0x00000008
#define 	NVIC_IRQ68  					0x00000010
#define 	NVIC_IRQ69  					0x00000020
#define 	NVIC_IRQ70  					0x00000040
#define 	NVIC_IRQ71  					0x00000080
#define 	NVIC_IRQ72  					0x00000100
#define 	NVIC_IRQ73  					0x00000200
#define 	NVIC_IRQ74  					0x00000400
#define 	NVIC_IRQ75  					0x00000800
#define 	NVIC_IRQ76 						0x00001000
#define 	NVIC_IRQ77 						0x00002000
#define 	NVIC_IRQ78  					0x00004000
#define 	NVIC_IRQ79  					0x00008000
#define 	NVIC_IRQ80  					0x00010000
#define 	NVIC_IRQ81  					0x00020000
#define 	NVIC_IRQ82  					0x00040000
#define 	NVIC_IRQ83  					0x00080000
#define 	NVIC_IRQ84  					0x00100000
#define 	NVIC_IRQ85  					0x00200000
#define 	NVIC_IRQ86  					0x00400000
#define 	NVIC_IRQ87  					0x00800000
#define 	NVIC_IRQ88  					0x01000000
#define 	NVIC_IRQ89  					0x02000000
#define 	NVIC_IRQ90  					0x04000000
#define 	NVIC_IRQ91  					0x08000000
#define 	NVIC_IRQ92  					0x10000000
#define 	NVIC_IRQ93  					0x20000000
#define 	NVIC_IRQ94  					0x40000000
#define 	NVIC_IRQ95  					0x80000000
#define 	NVIC_IRQ96  					0x00000001
#define 	NVIC_IRQ97  					0x00000002
#define 	NVIC_IRQ98  					0x00000004
#define 	NVIC_IRQ99  					0x00000008
#define 	NVIC_IRQ100  					0x00000010
#define 	NVIC_IRQ101  					0x00000020
#define 	NVIC_IRQ102 					0x00000040
#define 	NVIC_IRQ103  					0x00000080
#define 	NVIC_IRQ104  					0x00000100
#define 	NVIC_IRQ105  					0x00000200
#define 	NVIC_IRQ106  					0x00000400
#define 	NVIC_IRQ107  					0x00000800
#define 	NVIC_IRQ108 					0x00001000
#define 	NVIC_IRQ109 					0x00002000
#define 	NVIC_IRQ110  					0x00004000
#define 	NVIC_IRQ111  					0x00008000
#define 	NVIC_IRQ112 					0x00010000
#define 	NVIC_IRQ113  					0x00020000
#define 	NVIC_IRQ114 					0x00040000
#define 	NVIC_IRQ115  					0x00080000
#define 	NVIC_IRQ116  					0x00100000
#define 	NVIC_IRQ117  					0x00200000
#define 	NVIC_IRQ118  					0x00400000
#define 	NVIC_IRQ119  					0x00800000
#define 	NVIC_IRQ120  					0x01000000
#define 	NVIC_IRQ121  					0x02000000
#define 	NVIC_IRQ122  					0x04000000
#define 	NVIC_IRQ123  					0x08000000
#define 	NVIC_IRQ124  					0x10000000
#define 	NVIC_IRQ125  					0x20000000
#define 	NVIC_IRQ126  					0x40000000
#define 	NVIC_IRQ127  					0x80000000










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
