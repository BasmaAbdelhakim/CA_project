/*
 * HCLCD_interface.h
 *
 *  Created on: 25 Mar 2020
 *      Author: Basma Abdelhakim
 */

#ifndef HCLCD_INTERFACE_H_
#define HCLCD_INTERFACE_H_

typedef void (*notify_t) (void);

#define LINE_1                  0x80
#define LINE_2                  0xC0

#define COLUMN_0                 0U
#define COLUMN_1                 1U
#define COLUMN_2                 2U
#define COLUMN_3                 3U
#define COLUMN_4                 4U
#define COLUMN_5                 5U
#define COLUMN_6                 6U
#define COLUMN_7                 7U
#define COLUMN_8                 8U
#define COLUMN_9                 9U
#define COLUMN_10                10U
#define COLUMN_11                11U
#define COLUMN_12                12U
#define COLUMN_13                13U
#define COLUMN_14                14U
#define COLUMN_15                15U

/************************************************************************************************
 * Description:
 *            This function is used to configure GPIO pins of LCD according to
 *              the corresponding  structure defined in the beginning of HCLCD_program.c
 *
 ******************************************************************************************* ***/
ERROR_STATUS HCLCD_init(void);


/************************************************************************************************
 * Description:
 *            This function is used to save write string request on LCD with value equal to
 *               userWord and length equal to userLenght  to be handled  later using
 *                                        LCD  Runnable.
 *
 ***********************************************************************************************/
ERROR_STATUS HCLCD_writeString(const u8 * userWord,u8 userLenght);



/************************************************************************************************
 * Description:
 *            This function is used by application to define callback function to be  called
 *               after the end of write process by LCD runnable.
 *
 ************************************************************************************************/
ERROR_STATUS HCLCD_writeDoneApp(notify_t appFunction);


/***********************************************************************************************
 * Description:
 *            This function is used by application to save clear request to be handled later
 *            using LCD runnable
 * *********************************************************************************************/
ERROR_STATUS HCLCD_clear(void);


/***********************************************************************************************
 * Description:
 *            This function is used by application to define callback function to be  called
 *               after the end of clear process by LCD runnable.
 *
 ***********************************************************************************************/
ERROR_STATUS HCLCD_clearDoneApp(notify_t appFunction);


/***********************************************************************************************
 * Description:
 *        This function is used to move cursor of LCD according to the values of row and column.
 * row options are:
 *               1.LINE_1
 *               2.LINE_2
 * column options are:
 *                    COLUMN_0 , COLUMN_1  , COLUMN_2 ,  COLUMN_3
 *                    COLUMN_4 , COLUMN_5  , COLUMN_6 ,  COLUMN_7
 *                    COLUMN_8 , COLUMN_9  , COLUMN_10 , COLUMN_11
 *                    COLUMN_12 ,COLUMN_13 , COLUMN_14 , COLUMN_15
 ***********************************************************************************************/
ERROR_STATUS HCLCD_moveCursorLocation(u8 row , u8 column);


/************************************************************************************************
 * Description:
 *            This function is used by application to define callback function to be  called
 *               after the end of move cursor process by LCD runnable.
 *
 ************************************************************************************************/
ERROR_STATUS HCLCD_moveCursorDoneApp(notify_t appFunction);


/***********************************************************************************************
 * Description:
 *            This  is the runnable function of LCD.
 * *********************************************************************************************/
void HCLCD_task(void);

#endif /* HCLCD_INTERFACE_H_ */
