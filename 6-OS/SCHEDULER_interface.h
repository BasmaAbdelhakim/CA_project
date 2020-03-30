
/*******************************************************************************
 *  FILENAME     : SCHEDULER_interface.c    			                       *
 *  VERSION      : 1.0                                                         *
 *  AUTHOR       : kariman Mohamed                                             *
 *  DATE         : 20 March 2020                                               *
 *******************************************************************************/


#ifndef _SCHEDULER_INTERFACE_H_
#define _SCHEDULER_INTERFACE_H_



/************************************ Macros and types********************************************/

#define  READY       1
#define  SUSPEND     0

typedef void (*TaskRunnable_t)(void);

typedef struct
{
	TaskRunnable_t    TaskRunnable;
	u32               Period_TimeMS;
	u8                  State;

}Task_t;


typedef struct
{
   const Task_t* const AppTask;
   u32                 delayTicks;


}SysTaskInfo_t;


/******************************************functions prototypes ***********************************/


/******************************************************************
 * Description : Function to initialize SCHEDULER
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SCHEDULER_Init(void);


/******************************************************************
 * Description : Function to start SCHEDULER
 * Return Type : void
 * Input Argument : void
 *****************************************************************/
extern void SCHEDULER_Start(void);



#endif
