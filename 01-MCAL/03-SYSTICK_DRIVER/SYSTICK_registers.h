/*
 * SYSTICK_registers.h
 *
 *  Created on: Mar 9, 2020
 *      Author: Areej Ayman Helal
 */

#define STK_CTRL *((volatile u32 *)0xE000E010)
#define STK_LOAD *((volatile u32 *)0xE000E014)
#define STK_VAL  *((volatile u32 *)0xE000E018)

