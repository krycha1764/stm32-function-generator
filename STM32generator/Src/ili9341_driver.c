/*
 * ili9341_driver.c
 *
 *  Created on: 17 lip 2020
 *      Author: krycha1764
 */

#include <ili9341_driver.h>
#include "stm32f4xx_hal.h"
#include <stdlib.h>

void ILI9341_Select() {
	HAL_GPIO_WritePin(ILI9341_CS_GPIO_Port, ILI9341_CS_Pin, GPIO_PIN_RESET);
}

void ILI9341_Unselect() {
	HAL_GPIO_WritePin(ILI9341_CS_GPIO_Port, ILI9341_CS_Pin, GPIO_PIN_SET);
}

void ILI9341_Reset() {
	HAL_GPIO_WritePin(ILI9341_RES_GPIO_Port, ILI9341_RES_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(ILI9341_RES_GPIO_Port, ILI9341_RES_Pin, GPIO_PIN_SET);
}

void ILI9341_WriteCommand(uint8_t cmd) {
	HAL_GPIO_WritePin(ILI9341_DC_GPIO_Port, ILI9341_DC_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&ILI9341_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}

void ILI9341_WriteData(uint8_t *buff, size_t buff_size) {
	HAL_GPIO_WritePin(ILI9341_DC_GPIO_Port, ILI9341_DC_Pin, GPIO_PIN_SET);
	while (buff_size > 0) {
		uint16_t chunk_size = buff_size > 32768 ? 32768 : buff_size;
		HAL_SPI_Transmit(&ILI9341_SPI_PORT, buff, chunk_size, HAL_MAX_DELAY);
		buff += chunk_size;
		buff_size -= chunk_size;
	}
}

void ILI9341_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1,
		uint16_t y1) {
	ILI9341_WriteCommand(0x2A);
	{
		uint8_t data[] = { (x0 >> 8) & 0xFF, x0 & 0xFF, (x1 >> 8) & 0xFF, x1
				& 0xFF };
		ILI9341_WriteData(data, sizeof(data));
	}

	ILI9341_WriteCommand(0x2B);
	{
		uint8_t data[] = { (y0 >> 8) & 0xFF, y0 & 0xFF, (y1 >> 8) & 0xFF, y1
				& 0xFF };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0x2C);
}

void ILI9341_Init() {
	ILI9341_Select();
	ILI9341_Reset();
	ILI9341_WriteCommand(0x01);
	HAL_Delay(1000);
	ILI9341_WriteCommand(0xCB);
	{
		uint8_t data[] = { 0x39, 0x2C, 0x00, 0x34, 0x02 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xCF);
	{
		uint8_t data[] = { 0x00, 0xC1, 0x30 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xE8);
	{
		uint8_t data[] = { 0x85, 0x00, 0x78 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xEA);
	{
		uint8_t data[] = { 0x00, 0x00 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xED);
	{
		uint8_t data[] = { 0x64, 0x03, 0x12, 0x81 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xF7);
	{
		uint8_t data[] = { 0x20 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xC0);
	{
		uint8_t data[] = { 0x23 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xC1);
	{
		uint8_t data[] = { 0x10 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xC5);
	{
		uint8_t data[] = { 0x3E, 0x28 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xC7);
	{
		uint8_t data[] = { 0x86 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0x36);
	{
		uint8_t data[] = { 0x48 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0x3A);
	{
		uint8_t data[] = { 0x55 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xB1);
	{
		uint8_t data[] = { 0x00, 0x18 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xB6);
	{
		uint8_t data[] = { 0x08, 0x82, 0x27 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xF2);
	{
		uint8_t data[] = { 0x00 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0x26);
	{
		uint8_t data[] = { 0x01 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xE0);
	{
		uint8_t data[] = { 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37,
				0x07, 0x10, 0x03, 0x0E, 0x09, 0x00 };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0xE1);
	{
		uint8_t data[] = { 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48,
				0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_WriteCommand(0x11);
	HAL_Delay(120);
	ILI9341_WriteCommand(0x29);
	ILI9341_WriteCommand(0x36);
	{
		uint8_t data[] = { ILI9341_ROTATION };
		ILI9341_WriteData(data, sizeof(data));
	}
	ILI9341_Unselect();
}

void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
	if ((x >= ILI9341_WIDTH) || (y >= ILI9341_HEIGHT))
		return;
	ILI9341_Select();
	ILI9341_SetAddressWindow(x, y, x + 1, y + 1);
	uint8_t data[] = { color >> 8, color & 0xFF };
	ILI9341_WriteData(data, sizeof(data));
	ILI9341_Unselect();
}

void ILI9341_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font,
		uint16_t color, uint16_t bgcolor) {
	uint32_t i, b, j;
	ILI9341_SetAddressWindow(x, y, x + font.width - 1, y + font.height - 1);
	for (i = 0; i < font.height; i++) {
		b = font.data[(ch - 32) * font.height + i];
		for (j = 0; j < font.width; j++) {
			if ((b << (j + 8)) & 0x8000) {
				uint8_t data[] = { color >> 8, color & 0xFF };
				ILI9341_WriteData(data, sizeof(data));
			} else {
				uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
				ILI9341_WriteData(data, sizeof(data));
			}
		}
	}
}

void ILI9341_WriteString(uint16_t x, uint16_t y, char *str, FontDef font,
		uint16_t color, uint16_t bgcolor, uint8_t lenght) {
	ILI9341_Select();
	for(uint8_t i = 0;i < lenght; i++) {
		if (x + font.width >= ILI9341_WIDTH) {
			x = 0;
			y += font.height;
			if (y + font.height >= ILI9341_HEIGHT) {
				break;
			}
			if (*str == ' ') {
				str++;
				continue;
			}
		}
		ILI9341_WriteChar(x, y, *str, font, color, bgcolor);
		x += font.width;
		str++;
	}
	ILI9341_Unselect();
}
