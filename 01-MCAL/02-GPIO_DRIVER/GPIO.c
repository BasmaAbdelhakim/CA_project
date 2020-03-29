/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 17 Feb 2020                            */
/* Layer: MCAL                                  */
/* Component: GPIO                              */
/* File Name: GPIO.c                            */
/************************************************/

#include "STD_TYPES.h"

#include "GPIO.h"

#define MODE_CONFIG_CLEAR 0x0000000F
#define MODE_CONFIG_SIZE 4

typedef struct {
  uint32_t CRL;
  uint32_t CRH;
  uint32_t IDR;
  uint32_t ODR;
  uint32_t BSRR;
  uint32_t BRR;
  uint32_t LCKR;
  
} GPIO;


/* 
  Description: This function shall initiate GPIO pin, by setting its number, port, mode and configuration
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
  
  Output: status_t

 */
extern status_t GPIO_initPin(GPIO_t * peri)
{
  status_t currentStatus = status_Ok;
  uint32_t temp;
  uint32_t modeConfiguration;
  uint32_t updatedPin;
  uint32_t pinLoopPosition,realPosition,currentPosition;
  
  GPIO * PORT = (GPIO *) peri->port;
  
  /* Setting CRL pins configurations */
  for (pinLoopPosition = 0x00; pinLoopPosition < 0x08; pinLoopPosition++)
  {
    realPosition = (0x01) << pinLoopPosition;
    currentPosition = realPosition & peri->pin;
    /* Extracting the pin number */
    if (currentPosition == realPosition)
    {
      temp = PORT->CRL & ~(MODE_CONFIG_CLEAR << ( pinLoopPosition * MODE_CONFIG_SIZE));
      modeConfiguration = peri->mode | peri->configuration;
      temp |= modeConfiguration << (pinLoopPosition * MODE_CONFIG_SIZE);
      PORT->CRL = temp; 
    }
  }
  
  /* Setting CRH pins configurations */
  for (pinLoopPosition = 0x08; pinLoopPosition < 0x10; pinLoopPosition++)
  {
    realPosition = (0x01) << pinLoopPosition;
    currentPosition = realPosition & peri->pin;
    /* Extracting the pin number */
    if (currentPosition == realPosition)
    {
      updatedPin = pinLoopPosition - 0x08;
      temp = PORT->CRH & ~(MODE_CONFIG_CLEAR << ( updatedPin * MODE_CONFIG_SIZE));
      modeConfiguration = peri->mode | peri->configuration;
      temp |= modeConfiguration << (updatedPin * MODE_CONFIG_SIZE);
      PORT->CRH = temp; 
    }
  }
 
  return currentStatus;
}

/* 
  Description: This function shall write value on pin 
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> The value to be written on pin, options are:
           1) pinSet
           2) pinReset
  
  Output: status_t

 */
extern status_t GPIO_writePin(GPIO_t * peri, uint32_t value)
{
  
  status_t currentStatus = status_Ok;
  
  GPIO * PORT = (GPIO *) peri->port;
  
  if (value == pinSet)
  {
    PORT->BSRR = peri->pin;
  }
  else if (value == pinReset)
  {
    PORT->BRR = peri->pin;
  }
  else
  {
    currentStatus =  status_Nok;
  }
  return currentStatus;
}

/* This function takes a reference to GPIO_t type peripheral and returns its value */
/* 
  Description: This function shall read value of a pin 
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> pointer to hold value of a pin, return options are:
           1) pinSet
           2) pinReset
  
  Output: status_t

 */
extern status_t GPIO_readPin(GPIO_t * peri, uint32_t *value)
{
  status_t status = status_Ok;
  
  GPIO * PORT = (GPIO *) peri->port;
  
  * value = PORT->IDR & peri->pin;
    
  return status;
}

