/*
 * ili9341_GFX.c
 *
 *  Created on: 17 lip 2020
 *      Author: krycha1764
 */

//#define USE_DMA

#include "ili9341_GFX.h"
#include <stdlib.h>
#include "ili9341_driver.h"
#include <stdbool.h>

void swap_int16_t(int16_t *a, int16_t *b) {
	int16_t t;
	t = *a;
	*a = *b;
	*b = t;
}

void ILI9341_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		uint16_t color) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap_int16_t(&x0, &y0);
		swap_int16_t(&x1, &y1);
	}

	if (x0 > x1) {
		swap_int16_t(&x0, &x1);
		swap_int16_t(&y0, &y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			ILI9341_DrawPixel(y0, x0, color);
		} else {
			ILI9341_DrawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void ILI9341_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	ILI9341_DrawLine(x, y, x, y + h - 1, color);
}

void ILI9341_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	ILI9341_DrawLine(x, y, x + w - 1, y, color);
}

void ILI9341_InvertColors(bool invert) {
	ILI9341_Select();
	ILI9341_WriteCommand(invert ? 0x21 : 0x20);
	ILI9341_Unselect();
}

void ILI9341_FillScreen(uint16_t color) {
	ILI9341_FillRectangle(0, 0, ILI9341_WIDTH, ILI9341_HEIGHT, color);
}

void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		const uint16_t *data) {
	if ((x >= ILI9341_WIDTH) || (y >= ILI9341_HEIGHT))
		return;
	if ((x + w - 1) >= ILI9341_WIDTH)
		return;
	if ((y + h - 1) >= ILI9341_HEIGHT)
		return;
	ILI9341_Select();
	ILI9341_SetAddressWindow(x, y, x + w - 1, y + h - 1);
	ILI9341_WriteData((uint8_t*) data, sizeof(uint16_t) * w * h);
	ILI9341_Unselect();
}

void ILI9341_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t color) {
	if ((x >= ILI9341_WIDTH) || (y >= ILI9341_HEIGHT))
		return;
	if ((x + w - 1) >= ILI9341_WIDTH)
		w = ILI9341_WIDTH - x;
	if ((y + h - 1) >= ILI9341_HEIGHT)
		h = ILI9341_HEIGHT - y;
	ILI9341_Select();
	ILI9341_SetAddressWindow(x, y, x + w - 1, y + h - 1);
	uint8_t data[] = { color >> 8, color & 0xFF };
	HAL_GPIO_WritePin(ILI9341_DC_GPIO_Port, ILI9341_DC_Pin, GPIO_PIN_SET);
	for (y = h; y > 0; y--) {
		for (x = w; x > 0; x--) {
			HAL_SPI_Transmit(&ILI9341_SPI_PORT, data, sizeof(data),
					HAL_MAX_DELAY);

		}
	}

	ILI9341_Unselect();

//	for (int16_t i = x; i < x + w; i++) {
//		for (int16_t j = y; j < y + h; j++) {
//			ILI9341_DrawPixel(i, j, color);
//		}
//	}
}

void ILI9341_HollowCircle(uint16_t X, uint16_t Y, uint16_t Radius,
		uint16_t Colour) {
	int x = Radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (Radius << 1);
	while (x >= y) {
		ILI9341_DrawPixel(X + x, Y + y, Colour);
		ILI9341_DrawPixel(X + y, Y + x, Colour);
		ILI9341_DrawPixel(X - y, Y + x, Colour);
		ILI9341_DrawPixel(X - x, Y + y, Colour);
		ILI9341_DrawPixel(X - x, Y - y, Colour);
		ILI9341_DrawPixel(X - y, Y - x, Colour);
		ILI9341_DrawPixel(X + y, Y - x, Colour);
		ILI9341_DrawPixel(X + x, Y - y, Colour);
		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0) {
			x--;
			dx += 2;
			err += (-Radius << 1) + dx;
		}
	}
}

void ILI9341_FillCircle(uint16_t X, uint16_t Y, uint16_t Radius,
		uint16_t Colour) {
	int x = Radius;
	int y = 0;
	int xChange = 1 - (Radius << 1);
	int yChange = 0;
	int radiusError = 0;
	while (x >= y) {
		for (int i = X - x; i <= X + x; i++) {
			ILI9341_DrawPixel(i, Y + y, Colour);
			ILI9341_DrawPixel(i, Y - y, Colour);
		}
		for (int i = X - y; i <= X + y; i++) {
			ILI9341_DrawPixel(i, Y + x, Colour);
			ILI9341_DrawPixel(i, Y - x, Colour);
		}
		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0) {
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void ILI9341_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint16_t color) {
	ILI9341_DrawLine(x0, y0, x1, y1, color);
	ILI9341_DrawLine(x1, y1, x2, y2, color);
	ILI9341_DrawLine(x2, y2, x0, y0, color);
}

void ILI9341_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint16_t color) {
	int16_t a, b, y, last;
	if (y0 > y1) {
		swap_int16_t(&y0, &y1);
		swap_int16_t(&x0, &x1);
	}
	if (y1 > y2) {
		swap_int16_t(&y2, &y1);
		swap_int16_t(&x2, &x1);
	}
	if (y0 > y1) {
		swap_int16_t(&y0, &y1);
		swap_int16_t(&x0, &x1);
	}
	if (y0 == y2) {
		a = b = x0;
		if (x1 < a)
			a = x1;
		else if (x1 > b)
			b = x1;
		if (x2 < a)
			a = x2;
		else if (x2 > b)
			b = x2;
		ILI9341_DrawFastVLine(a, y0, b - a + 1, color);
		return;
	}

	int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
			dx12 = x2 - x1, dy12 = y2 - y1;
	int32_t sa = 0, sb = 0;
	if (y1 == y2)
		last = y1;
	else
		last = y1 - 1;
	for (y = y0; y <= last; y++) {
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		if (a > b)
			swap_int16_t(&a, &b);
		ILI9341_DrawFastHLine(a, y, b - a + 1, color);
	}
	sa = (int32_t) dx12 * (y - y1);
	sb = (int32_t) dx02 * (y - y0);
	for (; y <= y2; y++) {
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if (a > b)
			swap_int16_t(&a, &b);
		ILI9341_DrawFastHLine(a, y, b - a + 1, color);
	}
}
