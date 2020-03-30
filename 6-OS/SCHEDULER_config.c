
/********************************************************************************
**  FILENAME     : SCHEDULER_config.c     			                           **
**  VERSION      : 1.0                                                         **
**  DATE         : 20 March 2020                                               **
**  PLATFORM     : STM32F103                                                   **
**  AUTHOR       : kariman Mohamed                                             **
*********************************************************************************/

#include "STD_TYPES.h"
#include "SCHEDULER_interface.h"
#include "SCHEDULER_config.h"



/********************************************* Global Variables **************************************************/

/* tasks and first delay  may be changed according to the application */


extern Task_t Lcd_Task;
extern Task_t Debounce_Task;
extern Task_t APP_Task;



static SysTaskInfo_t SysTasksInfo[]={
  
										{&Lcd_Task,0},        //LCD EN
										{&Debounce_Task,0},  //DEBOUNCING
										{&APP_Task,0},      //APP

									};


/***************************************** function prototype *******************************************************/

SysTaskInfo_t* SysTasksInfoFunc(void);



/****************************************** function definition *****************************************************/
SysTaskInfo_t* SysTasksInfoFunc(void)
{
	return SysTasksInfo;
}

