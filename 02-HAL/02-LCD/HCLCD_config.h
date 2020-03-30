/*
 * HCLCD_config.h
 *
 *  Created on: 25 Mar 2020
 *      Author: Basma Abdelhakim
 */

#ifndef HCLCD_CONFIG_H_
#define HCLCD_CONFIG_H_

#define CLCD_RS_PORT     PORTA
#define CLCD_RS          PIN0

#define CLCD_RW_PORT     PORTA
#define CLCD_RW          PIN1

#define CLCD_E_PORT     PORTA
#define CLCD_E           PIN2

#define CLCD_D0_PORT     PORTA
#define CLCD_D0          PIN3

#define CLCD_D1_PORT     PORTA
#define CLCD_D1          PIN4

#define CLCD_D2_PORT     PORTA
#define CLCD_D2          PIN5

#define CLCD_D3_PORT     PORTA
#define CLCD_D3          PIN6

#define CLCD_D4_PORT     PORTA
#define CLCD_D4          PIN7

#define CLCD_D5_PORT     PORTA
#define CLCD_D5          PIN8

#define CLCD_D6_PORT     PORTA
#define CLCD_D6          PIN9

#define CLCD_D7_PORT     PORTA
#define CLCD_D7          PIN10

/*Function Set Command Configuration*/
#define CLCD_8_BITS_MODE               0x01
#define CLCD_4_BITS_MODE               0x00

#define CLCD_1_LINES_DISPLAY           0x00
#define CLCD_2_LINES_DISPLAY           0x08

#define DOT_CHARACTER_FONT_5_x_7       0x00
#define DOT_CHARACTER_FONT_5_x_8       0x04

#define CLCD_BITS_MODE         CLCD_8_BITS_MODE
#define CLCD_LINES_DISPLAYED   CLCD_2_LINES_DISPLAY
#define CLCD_CHARACTER_FONT    DOT_CHARACTER_FONT_5_x_7

/*ON_OFF Command Configuration*/
#define DISPLAY_OFF   0x00
#define DISPLAY_ON    0x04

#define CURSOR_OFF    0x00
#define CURSOR_ON     0x02

#define BLINK_OFF     0x00
#define BLINK_ON      0x01

#define CLCLD_DIAPLY_MODE   DISPLAY_ON
#define CLCD_CURSOR_MODE    CURSOR_OFF
#define CLCD_BLINK_MODE     BLINK_OFF
#endif /* HCLCD_CONFIG_H_ */
