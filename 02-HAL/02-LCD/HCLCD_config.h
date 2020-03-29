/*
 * HCLCD_config.h
 *
 *  Created on: 25 Mar 2020
 *      Author: Basma Abdelhakim
 */

#ifndef HCLCD_CONFIG_H_
#define HCLCD_CONFIG_H_

#define CLCD_PORT     PORTA

#define CLCD_RS          PIN0
#define CLCD_RW          PIN1
#define CLCD_E           PIN2

#define CLCD_D0          PIN3
#define CLCD_D1          PIN4
#define CLCD_D2          PIN5
#define CLCD_D3          PIN6
#define CLCD_D4          PIN7
#define CLCD_D5          PIN8
#define CLCD_D6          PIN9
#define CLCD_D7          PIN10

/*Function Set Command Configuration*/
#define CLCD_8_BITS_MODE               1U
#define CLCD_4_BITS_MODE               0U

#define CLCD_1_LINES_DISPLAY           0U
#define CLCD_2_LINES_DISPLAY           1U

#define DOT_CHARACTER_FONT_5_x_7       0U
#define DOT_CHARACTER_FONT_5_x_8       1U

#define CLCD_BITS_MODE         CLCD_8_BITS_MODE
#define CLCD_LINES_DISPLAYED   CLCD_2_LINES_DISPLAY
#define CLCD_CHARACTER_FONT    DOT_CHARACTER_FONT_5_x_7

/*ON_OFF Command Configuration*/
#define DISPLAY_OFF   0U
#define DISPLAY_ON    1U

#define CURSOR_OFF    0U
#define CURSOR_ON     1U

#define BLINK_OFF     0U
#define BLINK_ON      1U

#define CLCLD_DIAPLY_MODE   DISPLAY_ON
#define CLCD_CURSOR_MODE    CURSOR_OFF
#define CLCD_BLINK_MODE     BLINK_OFF
#endif /* HCLCD_CONFIG_H_ */
