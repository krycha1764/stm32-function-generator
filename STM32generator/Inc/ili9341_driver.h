/*
 * ili9341_driver.h
 *
 *  Created on: 17 lip 2020
 *      Author: krycha1764
 */

#ifndef __ILI9341_DRIVER_H__
#define __ILI9341_DRIVER_H__

#include "fonts.h"
#include "main.h"
#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define USE_DMA

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

#define ILI9341_SPI_PORT hspi2
extern SPI_HandleTypeDef ILI9341_SPI_PORT;

#ifdef USE_DMA
#define SPI_DMA hdma_spi2_tx
extern DMA_HandleTypeDef SPI_DMA;
#endif

#define ILI9341_RES_Pin       TFT_RST_Pin
#define ILI9341_RES_GPIO_Port TFT_RST_GPIO_Port
#define ILI9341_CS_Pin        TFT_CS_Pin
#define ILI9341_CS_GPIO_Port  TFT_CS_GPIO_Port
#define ILI9341_DC_Pin        TFT_DC_Pin
#define ILI9341_DC_GPIO_Port  TFT_DC_GPIO_Port

// default orientation
//#define ILI9341_WIDTH  240
//#define ILI9341_HEIGHT 320
//#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR)

// rotate right

#define ILI9341_WIDTH  320
#define ILI9341_HEIGHT 240
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)


// rotate left

//#define ILI9341_WIDTH  320
//#define ILI9341_HEIGHT 240
//#define ILI9341_ROTATION (ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)


// upside down

//#define ILI9341_WIDTH  240
//#define ILI9341_HEIGHT 320
//#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR)

// Color definitions
#define	ILI9341_BLACK   0x0000
#define	ILI9341_BLUE    0x001F
#define	ILI9341_RED     0xF800
#define	ILI9341_GREEN   0x07E0
#define ILI9341_CYAN    0x07FF
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW  0xFFE0
#define ILI9341_WHITE   0xFFFF
#define ILI9341_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

void ILI9341_Unselect();
void ILI9341_Init(void);
void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_WriteString(uint16_t x, uint16_t y, char* str, FontDef font, uint16_t color, uint16_t bgcolor, uint8_t lenght);
void ILI9341_Select();
void ILI9341_Reset();
void ILI9341_WriteCommand(uint8_t cmd);
void ILI9341_WriteData(uint8_t* buff, size_t buff_size);
void ILI9341_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

#ifdef USE_DMA
void ILI9341_WriteDataDMA(uint8_t* buff, uint16_t buff_size);
void ILI9341_WriteStringDMA(uint16_t x, uint16_t y, char* str, FontDef font, uint16_t color, uint16_t bgcolor, uint8_t lenght);
void ILI9341_DrawImageDMA(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
#endif

#endif // __ILI9341_H__
