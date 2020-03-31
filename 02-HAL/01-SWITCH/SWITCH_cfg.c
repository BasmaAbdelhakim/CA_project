/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 07 Feb 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_cfg.c                      */
/************************************************/

#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "GPIO.h"

#include "SWITCH.h"
#include "SWITCH_cfg.h"


/*
  Creating an array of switch struct that holds switches in the system
*/
const switchmap_t switchMap [SWITCH_NUM] = {
  {SWITCH_ALARM_PIN,SWITCH_ALARM_PORT,SWITCH_ALARM_PULL_STATE},
  {SWITCH_INDICATOR_PIN,SWITCH_INDICATOR_PORT,SWITCH_INDICATOR_PULL_STATE}
};


/* 
  Description: This function shall return an element of switch from switchMap array
  
  Input: 
        1- switchNum -> holds the index of the switch in the switch array 
  
  Output: Address of switch struct that maps the switchNum 

 */
extern switchmap_t * getSwitchMap (u32 switchNum)
{
  return &switchMap[switchNum];
}
