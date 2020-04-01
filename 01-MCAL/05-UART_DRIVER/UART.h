/************************************
* Author: Esraa Awad                *
* Date: 3/26/2020                   *
* File: Systick.h                   *
* Target: STM                       * 
************************************/

#ifndef UART_H
#define UART_H


typedef void (*Txcbf_t)(void);
typedef void (*Rxcbf_t)(void);

/*******  FUNCTION PROTOTYPES *******/
/*
*
* Description: This API initialize UART
* Input:   1-USART1    
           2-USART2   
           3-USART3    
           4-UART4     
           5-UART5   
* Output: void
*
*/
extern void UART_voidInit(void);

/*
*
* Description: This API send a data through UART 
* Input: u8 Array and the length of array
* Output: void
*
*/
extern ERROR_STATUS UART_u8Send(u8 * Buffer , u16 Copy_u16Length);

/*
*
* Description: This API receive a data through UART
* Input: Array and the length of the array
* Output: void
*
*/
extern ERROR_STATUS UART_u8Recieve(u8* Buffer , u16 Copy_u16Length);

/*
*
* Description: This API to Configure parameters of UART 
* Input: BaudRate , numbers of stop bits , the type of parity and flow control
* Output: void
*
*/
extern void UART_voidConfigure(u32 Copy_u32BaudRate , u8 Copy_u8StopBits , u8 Copy_u8Parity, u8 Copy_u8FlowControl);

/*
*
* Description: This API take the call back function which execute when transmission is done
* Input: function name 
* Output: void
*
*/
extern ERROR_STATUS UART_u8SetTxCbf(Txcbf_t Txcbf);

/*
*
* Description: This API take the call back function which execute when receiving is done
* Input: Function name 
* Output: void
*
*/
extern ERROR_STATUS UART_u8SetRxCbf(Rxcbf_t Rxcbf);









#endif 











