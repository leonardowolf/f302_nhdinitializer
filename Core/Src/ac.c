/*
 * ac.c
 *
 *  Created on: Jun 24, 2022
 *      Author: munin
 */


#include <ac.h>
#include "stdlib.h"
#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stdbool.h"
#include "main.h"
#include "logo_defs.h"
#include "u8g2.h"

#include "viafont.h"

#define OPTIMAL_BL 999
#define display_w 256
#define display_h 64

extern SPI_HandleTypeDef hspi1;
//extern TIM_HandleTypeDef htim2;
u8g2_t u8g2;

void disp_splash(void) {
	u8g2_DrawXBM(&u8g2, ((display_w / 2) - (vc_width / 2)),
			((display_h / 2) - (vc_height / 2)), vc_width, vc_height, &vc_logo_bits);
	u8g2_SendBuffer(&u8g2);
}

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
U8X8_UNUSED void *arg_ptr) {
	switch (msg) {
	case U8X8_MSG_GPIO_AND_DELAY_INIT:
		HAL_Delay(1);
		break;
	case U8X8_MSG_DELAY_MILLI:
		HAL_Delay(arg_int);
		break;
	case U8X8_MSG_GPIO_DC:
		HAL_GPIO_WritePin(SPI1_DC_GPIO_Port, SPI1_DC_Pin, arg_int);
		break;
	case U8X8_MSG_GPIO_RESET:
		HAL_GPIO_WritePin(SPI1_RES_GPIO_Port, SPI1_RES_Pin, arg_int);
		break;
	}
	return 1;
}

uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
		void *arg_ptr) {
	switch (msg) {
	case U8X8_MSG_BYTE_SEND:
		HAL_SPI_Transmit(&hspi1, (uint8_t*) arg_ptr, arg_int, 10000);
		break;
	case U8X8_MSG_BYTE_INIT:
		break;
	case U8X8_MSG_BYTE_SET_DC:
		u8x8_gpio_SetDC(u8x8, arg_int);
		break;
	case U8X8_MSG_BYTE_START_TRANSFER:
		break;
	case U8X8_MSG_BYTE_END_TRANSFER:
		break;
	default:
		return 0;
	}
	return 1;
}
void start_app(void){

	u8g2_Setup_ssd1322_nhd_256x64_f(&u8g2, U8G2_R2, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);

	u8g2_InitDisplay(&u8g2);
	u8g2_InitDisplay(&u8g2);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_SetPowerSave(&u8g2, 0);
	//set_contrast(OPTIMAL_CONTRAST);

	u8g2_SetBitmapMode(&u8g2,0);


	u8g2_SetDrawColor(&u8g2, 1);
	u8g2_SetFontMode(&u8g2, 0);
	u8g2_SetFontPosTop(&u8g2);

	/*	U8g2 Font names
		<prefix> '_' <name> '_' <purpose> <char set>
		<purpose>	Description
		t	Transparent font, Do not use a background color.
		h	All glyphs have common height.
		m	All glyphs have common height and width (monospace).
		8	All glyphs fit into a 8x8 pixel box.
		<char set>	Description
		f	The font includes up to 256 glyphs.
		r	Only glyphs on the range of the ASCII codes 32 to 127 are included in the font.
		u	Only glyphs on the range of the ASCII codes 32 to 95 (uppercase chars) are included in the font.
		n	Only numbers and extra glyphs for writing date and time strings are included in the font.
		...	Other custom character list.*/

//		u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
//	    u8g2_DrawStr(&u8g2, 0, 15, "Hello World!");
//	    u8g2_DrawCircle(&u8g2, 64, 40, 10, U8G2_DRAW_ALL);
//	    u8g2_SendBuffer(&u8g2);
		disp_splash();


}

