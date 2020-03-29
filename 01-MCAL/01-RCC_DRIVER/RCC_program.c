/*************************************************************************************************
 * RCC_program.c
 *         Author: Basma Abdelhakim
 ************************************************************************************************/

#include "STD_TYPES.h"
#include "RCC_interface.h"


#define RCC_BASE_ADREES      0x40021000
#define RCC  ((volatile  RCC_t *)RCC_BASE_ADREES)
typedef struct{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CSR;
}RCC_t;

/***********************************Global variables********************************************/
u32 PLL_CLOCK_SRC = 0;
u32 PLL_MULT_FACTOR = 0;
u32 SYSTEM_cLK=0;
/**********************************************************************************************/


/******************************************Functions*******************************************/

ERROR_STATUS RCC_CLK_Control(u32 clock, u8 status) {
	ERROR_STATUS returnValue = status_NOk;
	switch (status) {
	case ON:
		RCC->CR |= clock;
		returnValue = status_Ok;
		break;
	case OFF:
		RCC->CR &= ~clock;
		returnValue = status_Ok;
	}
	return returnValue;
}

/**********************************************************************************************/
ERROR_STATUS RCC_CLK_Select(u32 clock) {
	ERROR_STATUS returnValue = status_NOk;
	SYSTEM_cLK=clock;
	RCC->CFGR = ((RCC->CFGR & SW_clear) | clock);
	/*read SWS status to return SystemClock selected*/
	switch (clock) {
	case SW_HSI:
		if ((RCC->CFGR & SW_HSI) == SW_HSI) {
			returnValue = status_Ok;
		}
		break;
	case SW_HSE:
		if ((RCC->CFGR & SWS_HSE) == SWS_HSE) {
			returnValue = status_Ok;
		}

		break;
	case SW_PLL:
		if ((RCC->CFGR & SWS_PLL) == SWS_PLL) {
			returnValue = status_Ok;
		}
		break;
	default:
		break;

	}

	return returnValue;
}

/**********************************************************************************************/

ERROR_STATUS RCC_CLK_config(u32 clock, u32 clockSource, u32 clockConfig) {
	ERROR_STATUS returnValue = status_NOk;
	switch (clock) {
	case PLL_clk:
		RCC->CFGR |= clockSource;
		PLL_CLOCK_SRC = clockSource;
		PLL_MULT_FACTOR = clockConfig;
		RCC->CFGR = ((RCC->CFGR & PLLMUL_clear) | clockConfig);
		if ((RCC->CFGR & clockConfig) == clockConfig) {
			returnValue = status_Ok;
		}
		break;
	case HSE_clk:
		RCC->CR |= HSEBYP;
		if ((RCC->CR & clockConfig) == clockConfig) {
			returnValue = status_Ok;
		}
	}

	return returnValue;
}
/**********************************************************************************************/

ERROR_STATUS RCC_EnablePrephiralClock(u8 Bus, u8 periphiral) {
	ERROR_STATUS returnValue = status_NOk;
	switch (Bus) {
	case (AHBENR_BUS):
		RCC->AHBENR |= periphiral;
		if (RCC->AHBENR & periphiral) {
			returnValue = status_Ok;
		}
		break;
	case (APB1ENR_BUS):
		RCC->APB1ENR |= periphiral;
		if (RCC->APB1ENR & periphiral) {
			returnValue = status_Ok;
		}
		break;
	case (APB2ENR_BUS):
		RCC->APB2ENR |= periphiral;
		if ( RCC->APB2ENR & periphiral) {
			returnValue = status_Ok;
		}
		break;
	}
	return returnValue;
}
/**********************************************************************************************/

ERROR_STATUS RCC_GetSystemClock(u32 * SystemClock) {
	ERROR_STATUS returnValue = status_NOk;
	switch (SYSTEM_cLK) {
	case SW_HSI:
		if ((RCC->CFGR & SW_HSI) == SW_HSI) {
			*SystemClock = HSI_MHZ;
			returnValue = status_Ok;
		}
		break;
	case SW_HSE:
		if ((RCC->CFGR & SWS_HSE) == SWS_HSE) {
			*SystemClock = HSE_MHZ;
			returnValue = status_Ok;
		}
		break;
	case SW_PLL:
		if ((RCC->CFGR & SWS_PLL) == SWS_PLL) {
			if (PLL_CLOCK_SRC == PLL_SRC_HSI_2)    PLL_CLOCK_SRC = 4U;
			else if(PLL_CLOCK_SRC == PLL_SRC_HSE)  PLL_CLOCK_SRC = 8U;

			if (PLL_MULT_FACTOR==PLL_x_2)        PLL_MULT_FACTOR = 2U;
			else if (PLL_MULT_FACTOR==PLL_x_3)   PLL_MULT_FACTOR = 3U;
			else if (PLL_MULT_FACTOR==PLL_x_4)   PLL_MULT_FACTOR = 4U;
			else if (PLL_MULT_FACTOR==PLL_x_5)   PLL_MULT_FACTOR = 5U;
			else if (PLL_MULT_FACTOR==PLL_x_6)   PLL_MULT_FACTOR = 6U;
			else if (PLL_MULT_FACTOR==PLL_x_7)   PLL_MULT_FACTOR = 7U;
			else if (PLL_MULT_FACTOR==PLL_x_8)   PLL_MULT_FACTOR = 8U;
			else if (PLL_MULT_FACTOR==PLL_x_9)   PLL_MULT_FACTOR = 9U;
			else if (PLL_MULT_FACTOR==PLL_x_10)  PLL_MULT_FACTOR = 10U;
			else if (PLL_MULT_FACTOR==PLL_x_11)  PLL_MULT_FACTOR = 11U;
			else if (PLL_MULT_FACTOR==PLL_x_12)  PLL_MULT_FACTOR = 12U;
			else if (PLL_MULT_FACTOR==PLL_x_13)  PLL_MULT_FACTOR = 13U;
			else if (PLL_MULT_FACTOR==PLL_x_14)  PLL_MULT_FACTOR = 14U;
			else if (PLL_MULT_FACTOR==PLL_x_15)  PLL_MULT_FACTOR = 15U;
			else if (PLL_MULT_FACTOR==PLL_x_16)  PLL_MULT_FACTOR = 16U;

			*SystemClock = PLL_CLOCK_SRC * PLL_MULT_FACTOR;
			returnValue = status_Ok;
		}
			break;
		}

	return returnValue;
}

/**********************************************************************************************/
