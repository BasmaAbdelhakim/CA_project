/********************************************************************************
 *  FILENAME     : SCHEDULER_program.c     			                            *
 *  VERSION      : 1.0                                                          *
 *  AUTHOR       : kariman Mohamed                                              *
 *  DATE         : 20 March 2020                                                *
*********************************************************************************/

#include "../../04-lib/STD_TYPES.h"
#include "../../01-MCAL/04-SYSTIC/SYSTICK_interface.h"

#include "SCHEDULER_interface.h"
#include "SCHEDULER_config.h"


/*********************************************** types **************************************************/

typedef struct
{
	SysTaskInfo_t*     Task     ;
	u32     RemainTickToExecute ;
	u32     PeriodTicks         ;
	u8      State               ;

}SysTask_t;

/***************************************** Global Variables ***********************************************/

static SysTask_t  SysTasks[NUMBER_OF_TASKS];
static u8 OS_Flag;

/**************************************** functions prototypes ********************************************/

extern SysTaskInfo_t* SysTasksInfoFunc(void);


static void OsFlag_Set(void);
static void Scheduler(void);

/**************************************** Functions definitions *******************************************/



/******************************************************************
 * Description : Function to initialize SCHEDULER
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
void SCHEDULER_Init(void)
{
	u32 TaskNumber;
	//OS_Flag = 0 ;

	SysTaskInfo_t* SysTaskInfoFunction = SysTasksInfoFunc();

	SYSTICK_Init();
	SYSTICK_SetTimerMS(SYSTICK_TICK_TIME_MS);
	SYSTICK_SetCallBack(&OsFlag_Set);

	for(TaskNumber=0 ; TaskNumber < NUMBER_OF_TASKS ; TaskNumber++)
	{
		SysTasks[TaskNumber].Task                = &SysTaskInfoFunction[TaskNumber];

		SysTasks[TaskNumber].PeriodTicks         = (SysTasks[TaskNumber].Task->AppTask->Period_TimeMS) / SYSTICK_TICK_TIME_MS ;

		SysTasks[TaskNumber].RemainTickToExecute =  SysTasks[TaskNumber].Task->delayTicks ;

		SysTasks[TaskNumber].State = SysTasks[TaskNumber].Task->AppTask->State ;
	}
}


/******************************************************************
 * Description : Function to start SCHEDULER
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SCHEDULER_Start(void)
{
	SYSTICK_Start();

	while(1)
	{
		if(OS_Flag)
		{
			OS_Flag=0;
			Scheduler();
		}
	}
}


/******************************** static functions definition **************************************************/

static void Scheduler(void)
{
	u8 TaskNumber;
	for(TaskNumber=0 ; TaskNumber < NUMBER_OF_TASKS ; TaskNumber++)
	{
		if(SysTasks[TaskNumber].State == READY)
		{
			if( SysTasks[TaskNumber].RemainTickToExecute == 0 )
			{
				SysTasks[TaskNumber].Task->AppTask->TaskRunnable();
				SysTasks[TaskNumber].RemainTickToExecute = SysTasks[TaskNumber].PeriodTicks ;
			}
			SysTasks[TaskNumber].RemainTickToExecute-- ;
		}
	}
}



static void OsFlag_Set(void)
{
	OS_Flag = 1;
}


