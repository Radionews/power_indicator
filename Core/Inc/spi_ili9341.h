#ifndef __SPI_ILI9341_H
#define __SPI_ILI9341_H
//-------------------------------------------------------------------
#include "stm32f0xx_hal.h"
//-------------------------------------------------------------------
#endif /* __SPI_ILI9341_H */

#define RESET_ACTIVE() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET)
#define RESET_IDLE() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET)
#define CS_ACTIVE() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET)
#define CS_IDLE() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET)
#define DC_COMMAND() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)
#define DC_DATA() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET)

//-------------------------------------------------------------------
#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F
//-------------------------------------------------------------------
#define swap(a,b) {int16_t t=a;a=b;b=t;}

#define BURST_MAX_SIZE 	500

#define WORK_W 3
#define WORK_H 24

static const uint16_t temp_color[12]={
	0x001F,0x381F,0x781F,0xC81F,0xF81F,0xF819,0xF80F,0xF807,0xF800,0xF9E0,0xFBE0,0xFFE0
};

void TFT9341_ini(uint16_t w_size, uint16_t h_size);
//void TFT9341_reset(void);
//void TFT9341_SendCommand(uint8_t cmd);
//void TFT9341_SendData(uint8_t dt);
//static void TFT9341_WriteData(uint8_t* buff, size_t buff_size);
void TFT9341_FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
//https://github.com/martnak
void TFT9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);
void TFT9341_Draw_Number(uint8_t number,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void TFT9341_FillScreen(uint16_t color);
void TFT9341_Clear();
void TFT9341_Draw_U(float U);
void TFT9341_Draw_I(float I);
void TFT9341_FontRender();
