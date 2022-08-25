/*
 * ili9341_GFX.h
 *
 *  Created on: 17 lip 2020
 *      Author: mikolaj
 */

#ifndef ILI9341_GFX_H_
#define ILI9341_GFX_H_

#include "stm32f4xx_hal.h"
#ifndef USE_DMA
#include "ili9341_driver.h"
#else

#endif
#include <stdbool.h>

void swap_int16_t(int16_t* a, int16_t* b);
void ILI9341_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void ILI9341_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void ILI9341_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void ILI9341_InvertColors(bool invert);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ILI9341_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_HollowCircle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ILI9341_FillCircle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ILI9341_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);
void ILI9341_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

#endif /* ILI9341_GFX_H_ */
