/*
 * loaders.c
 *
 *  Created on: 13 lis 2021
 *      Author: mikolaj
 */

#include "loaders.h"

extern char tekst[100];
extern uint8_t size;
extern int8_t poziom;
extern uint8_t buttons;
extern uint8_t buttonswait;

const char bit_str[16][5] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};


void TEST(void) {
	ILI9341_FillScreen(ILI9341_BLACK);
	size = sprintf((char*)&tekst, "TRYB TESTOWY");
	ILI9341_WriteString(0, 0 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_RED, ILI9341_BLACK, size);

	ILI9341_DrawImage(0, 100, 10, 10, (const uint16_t*)&prawo10x10);
	ILI9341_DrawImage(10, 100, 10, 10, (const uint16_t*)&lewo10x10);
	ILI9341_DrawImage(20, 100, 10, 10, (const uint16_t*)&gora10x10);
	ILI9341_DrawImage(30, 100, 10, 10, (const uint16_t*)&dol10x10);

	ILI9341_DrawImage(0, 110, 20, 20, (const uint16_t*) &prawo20x20);
	ILI9341_DrawImage(20, 110, 20, 20, (const uint16_t*) &lewo20x20);
	ILI9341_DrawImage(40, 110, 20, 20, (const uint16_t*) &gora20x20);
	ILI9341_DrawImage(60, 110, 20, 20, (const uint16_t*) &dol20x20);

	while(1) {

		//BUTTONS();
		size = sprintf((char*)&tekst, "ENC: %i ", poziom);
		ILI9341_WriteString(0, 1 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
		size = sprintf((char*)&tekst,"KLAW: 0b%s%s",(char*)&bit_str + (5*(buttons>>4)),(char*)&bit_str + (5*(buttons & 0x0F)) );
		ILI9341_WriteString(0, 2 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

			HAL_Delay(50);
		}
}

void GENERATOR(void) {
	uint8_t waveform = 0;
	uint32_t frequency = 1000;
	uint32_t pfrequency = 1000;
	int8_t position = 0;
	int8_t pposition = 1;

	AD9833_Init(SIN, 1000, 0);

	ILI9341_FillScreen(ILI9341_BLACK);
	ILI9341_DrawImage(0, 0, 20, 20, (const uint16_t*)&lewo20x20);
	ILI9341_DrawImage(300, 0, 20, 20, (const uint16_t*)&prawo20x20);
	size = sprintf((char*)&tekst, "--------------POSITION-------------");
	ILI9341_WriteString(20, 2, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
	size = sprintf((char*)&tekst, "WAVEFORM:");
	ILI9341_WriteString(0 * 8, 4 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
	size = sprintf((char*)&tekst, "FREQUENCY:");
	ILI9341_WriteString(14 * 8, 4 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_GREEN, ILI9341_BLACK, size);
	size = sprintf((char*)&tekst, "RESET");
	ILI9341_WriteString(0 * 8, 12 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

	WAVEFORM(waveform);

	while(1) {
		if(!buttonswait && buttons == 0b01000000) {
			waveform++;
			if(waveform > 2) waveform = 0;
			WAVEFORM(waveform);
			buttonswait = 20;
		}
		if(!buttonswait && buttons == 0b10000000) {
			position++;
			if(position > 7) position = 7;
			buttonswait = 20;
		}
		if(!buttonswait && buttons == 0b00001000) {
			position--;
			if(position < 0) position = 0;
			buttonswait = 20;
		}
		if(!buttonswait && buttons == 0b00010000) NVIC_SystemReset();
		if(pposition != position) {
			ILI9341_FillRectangle((14*8)+((7-pposition)*8), (6*18)-2, 8, 2, ILI9341_BLACK);
			ILI9341_FillRectangle((14*8)+((7-position)*8), (6*18)-2, 8, 2, ILI9341_GREEN);
			pposition = position;
		}

		frequency += poziom*pow(10,position);
		poziom = 0;
		if(frequency > 12500000) frequency = 12500000;
		size = sprintf((char*)&tekst, "%08luHz", frequency);
		ILI9341_WriteString(14 * 8, 5 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_GREEN, ILI9341_BLACK, size);
		if(pfrequency != frequency) {
			AD9833_SetWaveData(frequency, 0);
			pfrequency = frequency;
		}
	}
}
