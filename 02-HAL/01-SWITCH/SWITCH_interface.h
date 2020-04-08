/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 26 Mar 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_task.h                     */
/************************************************/

#include "SWITCH_config.h"

#ifndef SWITCH_H
#define SWITCH_H

#define PRESSED  1
#define RELEASED 0 

#define MAX_COUNTS 5

typedef struct 
{
	GPIO_t  switchElementIO;

} switchmap_t;

/* 
  Description: This function shall initiate the specified switch num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module

  Input: switchNum -> holds the index of the switch in the switch array 

  Output: ERROR_STATUS

 */
extern ERROR_STATUS Switch_Init(u32 switchNum);

/*
  Description: This function shall return the specified switch state which can be
  PRESSED or RELEASED

  Input:
        1- switchNum which holds the index of the switch in the switch array
        2- switchValue -> Pointer to hold the switch value

  Output: status_t

 */
extern ERROR_STATUS Switch_GetSwitchState(u32 switchNum, u8 * switchValue);


/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED using SCHEDULER

  Input: 
        1- switchNum which holds the index of the switch in the switch array 
        2- switchValue -> Pointer to hold the switch value

  Output: ERROR_STATUS

 */
extern ERROR_STATUS SwitchTask_GetSwitchState(u32 switchNum, u8 * switchValue);

/*
  Description: This function is the switch scheduler task

  Input: void

  Output: void

 */
extern void switchTask (void);

#endif
