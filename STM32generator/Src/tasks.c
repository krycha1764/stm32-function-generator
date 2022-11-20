/*
 * tasks.c
 *
 *  Created on: 12 lis 2021
 *      Author: mikolaj
 */

#include "tasks.h"


extern uint8_t buttons; //zmienna ze stanami przyciskow
extern int8_t poziom; //zmienna ze stanem enkodera
extern char tekst[100]; //tablica czarow
extern uint8_t size; //rozmiar tablicy czarow


void BUTTONS(void) { //ta funkcja ogarnia przyciski, pokretla i inne takie

	HAL_I2C_Master_Receive(&hi2c1, 0b01000000, &buttons, 1, 10); //odczyt przycisków z klawiatury
	buttons = ~buttons;

	if (buttons == 0xff)NVIC_SystemReset(); //wywolanie RESET gdy wszystkie przyciski

	static uint16_t LastTimerCounter = 0;     //generalnie obsluga enkodera
	int TimerDif = htim5.Instance->CNT - LastTimerCounter;
	if (TimerDif >= 4 || TimerDif <= -4) {
		TimerDif /= 4;
		poziom += (int8_t) TimerDif;
		LastTimerCounter = htim5.Instance->CNT;
	}
}

void WAVEFORM(uint8_t waveform) {
	switch(waveform) {
	case(0):
		size = sprintf((char*)&tekst, "SINUS   ");
		break;
	case(1):
		size = sprintf((char*)&tekst, "SQRUARE ");
		break;
	case(2):
		size = sprintf((char*)&tekst, "TRIANGLE");
		break;
	default:
		size = sprintf((char*)&tekst, "ERROR   ");
		break;
	}
	ILI9341_WriteStringDMA(0 * 8, 5 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
	AD9833_SetWave(waveform);
}
