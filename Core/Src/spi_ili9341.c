#include "spi_ili9341.h"
#include "font.h"
#include <math.h>
//-------------------------------------------------------------------

extern SPI_HandleTypeDef hspi1;

//-------------------------------------------------------------------
uint16_t TFT9341_WIDTH;
uint16_t TFT9341_HEIGHT;
//-------------------------------------------------------------------
void TFT9341_reset(void)
{
	RESET_ACTIVE();
	HAL_Delay(5);
	RESET_IDLE();
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
void TFT9341_ini(uint16_t w_size, uint16_t h_size)
{
	uint8_t data[15];
	CS_ACTIVE();
	TFT9341_reset();
	//Software Reset
	TFT9341_SendCommand(0x01);
	HAL_Delay(1000);

	TFT9341_SendCommand(0xCB);
	//Power Control A
	data[0] = 0x39;
	data[1] = 0x2C;
	data[2] = 0x00;
	data[3] = 0x34;
	data[4] = 0x02;
	TFT9341_WriteData(data, 5);

	TFT9341_SendCommand(0xCF);
	//Power Control B
	data[0] = 0x00;
	data[1] = 0xC1;
	data[2] = 0x30;
	TFT9341_WriteData(data, 3);

	TFT9341_SendCommand(0xE8);
	//Driver timing control A
	data[0] = 0x85;
	data[1] = 0x00;
	data[2] = 0x78;
	TFT9341_WriteData(data, 3);

	TFT9341_SendCommand(0xEA);
	//Driver timing control B
	data[0] = 0x00;
	data[1] = 0x00;
	TFT9341_WriteData(data, 2);

	TFT9341_SendCommand(0xED);
	//Power on Sequence control
	data[0] = 0x64;
	data[1] = 0x03;
	data[2] = 0x12;
	data[3] = 0x81;
	TFT9341_WriteData(data, 4);

	TFT9341_SendCommand(0xF7);
	//Pump ratio control
	data[0] = 0x20;
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0xC0);
	//Power Control,VRH[5:0]
	data[0] = 0x23;//0x10;
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0xC1);
	//Power Control,SAP[2:0];BT[3:0]
	data[0] = 0x10;
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0xC5);
	//VCOM Control 1
	data[0] = 0x3E;
	data[1] = 0x28;
	TFT9341_WriteData(data, 2);

	TFT9341_SendCommand(0xC7);
	//VCOM Control 2
	data[0] = 0x86;
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0x36);
	//Memory Acsess Control
	data[0] = 0x48;
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0x3A);
	//Pixel Format Set
	data[0] = 0x55;//16bit
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0xB1);
	//Frame Rratio Control, Standard RGB Color
	data[0] = 0x00;
	data[1] = 0x18;
	TFT9341_WriteData(data, 2);

	TFT9341_SendCommand(0xB6);
	//Display Function Control
	data[0] = 0x08;
	data[1] = 0x82;
	data[2] = 0x27;//320 строк
	TFT9341_WriteData(data, 3);

	TFT9341_SendCommand(0xF2);
	//Enable 3G (пока не знаю что это за режим)
	data[0] = 0x00;//не включаем
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0x26);
	//Gamma set
	data[0] = 0x01;//Gamma Curve (G2.2) (Кривая цветовой гаммы)
	TFT9341_WriteData(data, 1);

	TFT9341_SendCommand(0xE0);
	//Positive Gamma  Correction
	data[0] = 0x0F;
	data[1] = 0x31;
	data[2] = 0x2B;
	data[3] = 0x0C;
	data[4] = 0x0E;
	data[5] = 0x08;
	data[6] = 0x4E;
	data[7] = 0xF1;
	data[8] = 0x37;
	data[9] = 0x07;
	data[10] = 0x10;
	data[11] = 0x03;
	data[12] = 0x0E;
	data[13] = 0x09;
	data[14] = 0x00;
	TFT9341_WriteData(data, 15);

	TFT9341_SendCommand(0xE1);
	//Negative Gamma  Correction
	data[0] = 0x00;
	data[1] = 0x0E;
	data[2] = 0x14;
	data[3] = 0x03;
	data[4] = 0x11;
	data[5] = 0x07;
	data[6] = 0x31;
	data[7] = 0xC1;
	data[8] = 0x48;
	data[9] = 0x08;
	data[10] = 0x0F;
	data[11] = 0x0C;
	data[12] = 0x31;
	data[13] = 0x36;
	data[14] = 0x0F;
	TFT9341_WriteData(data, 15);

	TFT9341_SendCommand(0x11);//Выйдем из спящего режима
	HAL_Delay(150);

	TFT9341_SendCommand(0x29);
	//TFT9341_SendCommand(0x2c);
	//Display ON
	//data[0] = TFT9341_ROTATION;
	//TFT9341_SendCommand(0x29);
	//TFT9341_WriteData(data, 1);

	TFT9341_WIDTH = w_size;
	TFT9341_HEIGHT = h_size;
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
void TFT9341_SendCommand(uint8_t cm)
{
  DC_COMMAND();
  HAL_SPI_Transmit (&hspi1, &cm, 1, 5000);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void TFT9341_SendData(uint8_t dt)
{
	DC_DATA();
	HAL_SPI_Transmit (&hspi1, &dt, 1, 5000);
}
//-------------------------------------------------------------------
void TFT9341_WriteData(uint8_t* buff, size_t buff_size)
{
	DC_DATA();
	while(buff_size > 0) {
		uint16_t chunk_size = buff_size > 32768 ? 32768 : buff_size;
		HAL_SPI_Transmit(&hspi1, buff, chunk_size, HAL_MAX_DELAY);
		buff += chunk_size;
		buff_size -= chunk_size;
	}
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------

static void TFT9341_SetAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
  // column address set
  TFT9341_SendCommand(0x2A); // CASET
  {
    uint8_t data[] = { (x0 >> 8) & 0xFF, x0 & 0xFF, (x1 >> 8) & 0xFF, x1 & 0xFF };
    TFT9341_WriteData(data, sizeof(data));
  }

  // row address set
  TFT9341_SendCommand(0x2B); // RASET
  {
    uint8_t data[] = { (y0 >> 8) & 0xFF, y0 & 0xFF, (y1 >> 8) & 0xFF, y1 & 0xFF };
    TFT9341_WriteData(data, sizeof(data));
  }

  // write to RAM
  TFT9341_SendCommand(0x2C); // RAMWR
}//-------------------------------------------------------------------
void TFT9341_FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
  if((x1 >= TFT9341_WIDTH) || (y1 >= TFT9341_HEIGHT) || (x2 >= TFT9341_WIDTH) || (y2 >= TFT9341_HEIGHT)) return;
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);
  TFT9341_SetAddrWindow(x1, y1, x2, y2);
  TFT9341_Draw_Colour_Burst(color,(x2-x1+1)*(y2-y1+1));
}

void TFT9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size)
{
	//SENDS COLOUR
	uint32_t Buffer_Size = 0;
	if((Size*2) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}

	DC_DATA();

	unsigned char chifted = Colour>>8;
	unsigned char burst_buffer[Buffer_Size];
	for(uint32_t j = 0; j < Buffer_Size; j+=2)
		{
			burst_buffer[j] = 	chifted;
			burst_buffer[j+1] = Colour;
		}

	uint32_t Sending_Size = Size*2;
	uint32_t Sending_in_Block = Sending_Size/Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size%Buffer_Size;

	if(Sending_in_Block != 0)
	{
		for(uint32_t j = 0; j < (Sending_in_Block); j++)
		{
			HAL_SPI_Transmit(&hspi1, (unsigned char *)burst_buffer, Buffer_Size, HAL_MAX_DELAY);
		}
	}

	//REMAINDER!
	HAL_SPI_Transmit(&hspi1, (unsigned char *)burst_buffer, Remainder_from_block, HAL_MAX_DELAY);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
void TFT9341_FillScreen(uint16_t color)
{
	TFT9341_FillRect(0, 0, TFT9341_WIDTH-1, TFT9341_HEIGHT-1, color);
}

void TFT9341_Draw_Number(uint8_t number,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	TFT9341_SetAddrWindow(x1, y1, x2, y2);
	DC_DATA();

	uint32_t counter = 0;

	unsigned char Temp_small_buffer[BURST_MAX_SIZE];

	for(uint32_t i = 0; i < 12816/BURST_MAX_SIZE; i++)
	{
		for(uint32_t k = 0; k<BURST_MAX_SIZE; k=k+2)
		{
			if((image_data_Font[number][counter/8]>>(7-(counter%8)))&0x01 == 1)
			{
				Temp_small_buffer[k] = 0x00;
				Temp_small_buffer[k+1] = 0x00;
			}
			else
			{
				Temp_small_buffer[k] = (color>>8)&0xff;
				Temp_small_buffer[k+1] = color&0xff;
			}
			counter++;
		}
		HAL_SPI_Transmit(&hspi1, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
	}

	unsigned char Temp_small_buffer_2[316];

	for(uint32_t k = 0; k<316; k=k+2)
	{
		if((image_data_Font[number][counter/8]>>(7-(counter%8)))&0x01 == 1)
		{
			Temp_small_buffer_2[k] = 0x00;
			Temp_small_buffer_2[k+1] = 0x00;
		}
		else
		{
			Temp_small_buffer_2[k] = (color>>8)&0xff;
			Temp_small_buffer_2[k+1] = color&0xff;
		}
		counter++;
	}
	HAL_SPI_Transmit(&hspi1, (unsigned char*)Temp_small_buffer_2, 316, 10);

}

void TFT9341_Draw_Temp_Line(uint8_t number)
{

	if(number>12)
		number = 12;
	for(uint8_t i=0;i<12;i++)
	{
		if(i<number)
			TFT9341_FillRect(i*20, 160, 19+i*20, 180, temp_color[i]);
		else
			TFT9341_FillRect(i*20, 160, 19+i*20, 180, BLACK);
	}
}
//-------------------------------------------------------------------
void TFT9341_Clear()
{
	TFT9341_FillScreen(BLACK);
	uint8_t data_0[] = { 0xFF, 0xFF };
	uint8_t data_1[] = { 0x00, 0x00 };

	//вывод надписи "напряжение,в"
	TFT9341_SetAddrWindow(WORK_W+45, WORK_H, (45+152+WORK_W-1), (20+WORK_H-1));
	DC_DATA();
	for(uint32_t i = 0; i < 380; i++)
	{
		for(uint32_t j = 0; j < 8; j++)
		{
			if((image_data_U[i]>>(7-j))&0x01 == 1)
				HAL_SPI_Transmit(&hspi1, data_1, 2, HAL_MAX_DELAY);
			else
				HAL_SPI_Transmit(&hspi1, data_0, 2, HAL_MAX_DELAY);
		}
	}

	//вывод надписи "сила тока, А"
	TFT9341_SetAddrWindow(WORK_W+58, 300, (58+120+WORK_W-1), (319));
	DC_DATA();
	for(uint32_t i = 0; i < 300; i++)
	{
		for(uint32_t j = 0; j < 8; j++)
		{
			if((image_data_I[i]>>(7-j))&0x01 == 1)
				HAL_SPI_Transmit(&hspi1, data_1, 2, HAL_MAX_DELAY);
			else
				HAL_SPI_Transmit(&hspi1, data_0, 2, HAL_MAX_DELAY);
		}
	}

	TFT9341_Draw_Number(0,14, 60, 85, 148,WHITE);
	TFT9341_Draw_Number(0,91, 60, 162, 148,WHITE);
	TFT9341_Draw_Number(0,168, 60, 239, 148,WHITE);

	TFT9341_Draw_Number(0,14, 192, 85, 280,YELLOW);
	TFT9341_Draw_Number(0,91, 192, 162, 280,YELLOW);
	TFT9341_Draw_Number(0,168, 192, 239, 280,YELLOW);

	TFT9341_FillRect(0, 159, 239, 181, WHITE);
	TFT9341_Draw_Temp_Line(12);

}

void TFT9341_Draw_Point_U(uint8_t n)
{
	if(n==1)
	{
		TFT9341_FillRect(76, 144, 84, 154, WHITE);
		TFT9341_FillRect(153, 144, 161, 154, BLACK);
	}
	else
	{
		TFT9341_FillRect(153, 144, 161, 154, WHITE);
		TFT9341_FillRect(76, 144, 84, 154, BLACK);
	}
}

void TFT9341_Draw_Point_I(uint8_t n)
{
	if(n==1)
	{
		TFT9341_FillRect(153, 278, 161, 288, BLACK);
		TFT9341_FillRect(76, 278, 83, 288, WHITE);
	}
	else
	{
		TFT9341_FillRect(76, 278, 83, 288, BLACK);
		TFT9341_FillRect(153, 278, 161, 288, WHITE);
	}
}
//-------------------------------------------------------------------
void TFT9341_Draw_U(float U)
{
	uint16_t  Temp = roundf(U * 100.0);

	if(Temp<999)
	{
		TFT9341_Draw_Number(Temp/100,14, 60, 85, 148,WHITE);
		TFT9341_Draw_Number((Temp%100)/10,91, 60, 162, 148,WHITE);
		TFT9341_Draw_Number((Temp%100)%10,168, 60, 239, 148,WHITE);
		TFT9341_Draw_Point_U(1);
	}
	else
	{
		Temp = roundf(Temp/10);
		TFT9341_Draw_Number(Temp/100,14, 60, 85, 148,WHITE);
		TFT9341_Draw_Number((Temp%100)/10,91, 60, 162, 148,WHITE);
		TFT9341_Draw_Number((Temp%100)%10,168, 60, 239, 148,WHITE);
		TFT9341_Draw_Point_U(0);
	}
}

void TFT9341_Draw_I(float I)
{
	uint16_t Temp=0;

	if(I<10.0)
	{
		Temp = roundf(I * 100.0);
		TFT9341_Draw_Number(Temp/100,14, 192, 85, 280,YELLOW);
		TFT9341_Draw_Number((Temp%100)/10,91, 192, 162, 280,YELLOW);
		TFT9341_Draw_Number((Temp%100)%10,168, 192, 239, 280,YELLOW);
		TFT9341_Draw_Point_I(1);
	}
	else
	{
		Temp = roundf(I * 10.0);
		TFT9341_Draw_Number(Temp/100,14, 192, 85, 280,YELLOW);
		TFT9341_Draw_Number((Temp%100)/10,91, 192, 162, 280,YELLOW);
		TFT9341_Draw_Number((Temp%100)%10,168, 192, 239, 280,YELLOW);
		TFT9341_Draw_Point_I(0);
	}
}


