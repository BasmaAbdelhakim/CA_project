/*
 * UART_program.c
 *
 *  Created on: Apr 5, 2020
 *      Author: pc
 */



/**
 * @brief
 * @file
 *
 */

/************************************
 * Author: Esraa Awad                *
 * Date: 26/3/2020                   *
 * File: Systick.h                   *
 * Target: STM                       *
 ************************************/

#include "STD_TYPES.h"

#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"



/*********** MASKS ************/
#define SR_TXE       0x00000080
#define SR_RXNE      0x00000020
#define CR1_UE       0x00002000
#define CR1_TE       0x00000008
#define CR1_RE       0x00000004
#define SR_TXE       0x00000080
#define SR_RXNE      0x00000020
#define SR_TXE_CLR   0xffffff7f
#define SR_RXNE_CLR  0xffffffdf
#define CR1_RXNEIE	 0x00000020
#define CR1_TXIE	 0x00000080
#define SR_TC_CLR    0xffffffbf
#define SR_TC		 0x00000040
#define CR1_TCIE     0x00000040
#define CR1_PCE		 0x00000100
#define CR3_CTSE	 0x00000200
#define CR3_RTSE	 0x00000100


#define WORD_LENGTH_8 0x00001000
#define WORD_LENGTH_9 0x00000000
#define STOP_BITS_CLR 0xffffdfff
#define STOP_BITS_1   0x00000000
#define STOP_BITS_2   0x00002000
#define BUADRATE_9600 (u32)7500


#define ON 			1
#define OFF 		2
/******************************/



#define USART1_BASE_ADDRESS   (u32)0x40013800
#define USART2_BASE_ADDRESS   (u32)0x40004400
#define USART3_BASE_ADDRESS   (u32)0x40004800
#define UART4_BASE_ADDRESS    (u32)0x40004C00
#define UART5_BASE_ADDRESS    (u32)0x40005000

typedef struct {

	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GPTR;

}UartPeri_t;

volatile UartPeri_t * UART =(UartPeri_t *)USART1_BASE_ADDRESS;
volatile UartPeri_t * UART2 =(UartPeri_t *)USART2_BASE_ADDRESS;
volatile UartPeri_t * UART3 =(UartPeri_t *)USART3_BASE_ADDRESS;
volatile UartPeri_t * UART4 =(UartPeri_t *)UART4_BASE_ADDRESS;
volatile UartPeri_t * UART5 =(UartPeri_t *)UART5_BASE_ADDRESS;

typedef enum
{
	idle,
	busy
}BufferState_t;



typedef struct {
	u8  * data;
	u32  position;
	u32  size;
	BufferState_t state;

}DataBuffer_t;

DataBuffer_t TxBuffer;
DataBuffer_t RxBuffer;

typedef void (*appTxNotify_t) (void);
typedef void (*appRxNotify_t) (void);

static appRxNotify_t  appRxNotify;
static appTxNotify_t  appTxNotify;




/*
 *
 * Description: This API initialize UART
 * Input:  1-USART1
           2-USART2
           3-USART3
           4-UART4
           5-UART5
           u8 Copy_u8UART_Num
 * Output: void
 *
 */
extern void UART_voidInit (void)
{
	/*Clear TC Flag*/
	UART -> SR &= SR_TC_CLR;

	/*Enable usart1*/
	UART -> CR1 |= CR1_UE;


	/* GPIO configure pins */
	GPIO_t USART1_tx;
	GPIO_t USART1_rx;


	USART1_tx.pin=PIN9;
	USART1_tx.mode=MODE_OUTPUT_SPEED_50;
	USART1_tx.configuration=CONFIG_OUTPUT_ALTERNATE_FUNCTION_PUSH_PULL;
	USART1_tx.port=PORTA;

	USART1_rx.pin=PIN10;
	USART1_rx.mode=MODE_INPUT;
	USART1_rx.configuration=CONFIG_INPUT_PULL_UP_DOWN;
	USART1_rx.port=PORTA;

	GPIO_initPin(&USART1_tx);
	GPIO_initPin(&USART1_rx);
	/*clear uart pending*/
	NVIC_u8ClearPending (NVIC_IRQ37);

	/*setup default configurations data length=8 bits
	 *one stop bit
	 *BuadRate = 9600
	 */
	UART -> CR1  |= WORD_LENGTH_8;
	UART -> CR2 &= STOP_BITS_CLR;
	UART -> CR2 |= STOP_BITS_1;
	UART -> BRR  = BUADRATE_9600;

	/* Setup interrupts */

	NVIC_u8EnableIRQ(NVIC_IRQ37);


	/*     Enable transmitter and receive       */
	UART -> CR1 |= CR1_TE | CR1_RE;

	/*Enable transmitter and receive interrupts */
	UART -> CR1 |= CR1_TCIE  | CR1_RXNEIE ;
	/*Clear TC Flag*/
	UART -> SR &= SR_TC_CLR;




}

/*
 *
 * Description: This API send a data through UART
 * Input: u8 Array and the length of array
 * Output: void
 *
 */
extern ERROR_STATUS UART_u8Send(u8 * Buffer , u16 Copy_u16Length)
{
	ERROR_STATUS Local_error = status_Ok;

	if (Buffer && Copy_u16Length >0)
	{
		if (TxBuffer.state == idle)
		{
			TxBuffer.data = Buffer;
			TxBuffer.size = Copy_u16Length;
			TxBuffer.position = 0;
			TxBuffer.state = busy;
			UART -> DR = TxBuffer.data[TxBuffer.position];
			TxBuffer.position++;

		}
	}
	else
	{
		Local_error = status_NOk;
	}

	return (Local_error);
}

/*
 *
 * Description: This API receive a data through UART
 * Input: Array and the length of the array
 * Output: void
 *
 */
extern ERROR_STATUS UART_u8Recieve(u8* Buffer , u16 Copy_u16Length)
{

	ERROR_STATUS Local_error = status_Ok;
	if (Buffer && Copy_u16Length >0)
	{
		if (RxBuffer.state == idle)
		{
			RxBuffer.data = Buffer;
			RxBuffer.size = Copy_u16Length;
			RxBuffer.position = 0;
			RxBuffer.state = busy;
		}
	}
	else
	{
		Local_error = status_NOk;
	}

	return (Local_error);
}

/*
 *
 * Description: This API to Configure parameters of UART
 * Input: BaudRate :  BUADRATE_9600 ..
 *  	  StopBits :  STOP_BITS_1 or STOP_BITS_2
 *	  	  Parity   :  ON or OFF
 *	  	  ControlFlow: ON or OFF
 *
 * Output: void
 *
 */
extern void UART_voidConfigure(u32 Copy_u32BaudRate , u8 Copy_u8StopBits , u8 Copy_u8Parity, u8 Copy_u8FlowControl)
{
	UART -> BRR  = Copy_u32BaudRate;

	UART -> CR2 &= STOP_BITS_CLR;
	UART -> CR2 |= Copy_u8StopBits;

	if (Copy_u8Parity == ON)
	{
		UART -> CR1 |= CR1_PCE;
	}
	else
	{
		UART -> CR1 &= ~CR1_PCE;
	}

	if (Copy_u8FlowControl == ON)
	{
		UART -> CR3 |= CR3_CTSE;
		UART -> CR3 |= CR3_RTSE;
	}
	else
	{
		UART -> CR3 &= ~CR3_CTSE;
		UART -> CR3 &= ~CR3_RTSE;


	}



}

/*
 *
 * Description: This API take the call back function which execute when tranmission is done
 * Input: function name
 * Output: void
 *
 */
extern ERROR_STATUS UART_u8SetTxCbf(Txcbf_t Txcbf)
{
	ERROR_STATUS Local_error = status_Ok;
	if (Txcbf)
	{
		appTxNotify = Txcbf;
	}
	else
	{
		Local_error = status_NOk;
	}
	return (Local_error);
}

/*
 *
 * Description: This API take the call back function which execute when recieving is done
 * Input: Function name
 * Output: void
 *
 */
extern ERROR_STATUS UART_u8SetRxCbf(Rxcbf_t Rxcbf)
{
	ERROR_STATUS Local_error = status_Ok;
	if (Rxcbf)
	{
		appRxNotify = Rxcbf;
	}
	else
	{
		Local_error = status_NOk;
	}
	return (Local_error);


}


void USART1_IRQHandler (void)
{

  /* Clear TC Bit */
	UART -> SR &= SR_TC_CLR;
	if ((UART->SR & SR_TC) && (TxBuffer.data) )
	{
		/* Clear TC Bit */

		UART -> SR &= SR_TC_CLR;

		if (TxBuffer.position != TxBuffer.size)
		{
			UART -> DR = TxBuffer.data[TxBuffer.position];
			TxBuffer.position++;
		}
		else
		{
			TxBuffer.data = NULL;
			TxBuffer.size = 0;
			TxBuffer.position = 0;
			TxBuffer.state = idle;
			appTxNotify();

		}
	}

	if (UART->SR & SR_RXNE)
	{
		/*  Clear RXNE Bit */
		UART -> SR &= SR_RXNE_CLR;
		if (RxBuffer.state == busy )
		{
			RxBuffer.data[RxBuffer.position] = UART -> DR ;
			RxBuffer.position++;

			if (RxBuffer.position == RxBuffer.size)
			{
				RxBuffer.data = NULL;
				RxBuffer.size = 0;
				RxBuffer.position = 0;
				RxBuffer.state = idle;
				appRxNotify();
			}

		}
		else
		{
			return ;
		}


	}
}

