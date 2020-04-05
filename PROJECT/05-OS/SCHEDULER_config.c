
/********************************************************************************
**  FILENAME     : SCHEDULER_config.c     			                           **
**  VERSION      : 1.0                                                         **
**  DATE         : 20 March 2020                                               **
**  PLATFORM     : STM32F103                                                   **
**  AUTHOR       : kariman Mohamed                                             **
*********************************************************************************/

#include "../../04-lib/STD_TYPES.h"

#include "SCHEDULER_interface.h"
#include "SCHEDULER_config.h"



/********************************************* Global Variables **************************************************/



extern Task_t APP_Task;

extern Task_t Lcd_Task;

extern Task_t Switch_Task;


static SysTaskInfo_t SysTasksInfo[]={

										{&Switch_Task,0},
										{&Lcd_Task,0},
										{&APP_Task,0}

									};


/***************************************** function prototype *******************************************************/

extern SysTaskInfo_t* SysTasksInfoFunc(void);



/****************************************** function definition *****************************************************/

SysTaskInfo_t* SysTasksInfoFunc(void)
{
	return SysTasksInfo;
}

