/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char tekst[100];
char tekstDBG[100];
uint8_t size = 0;
uint8_t sizeDBG = 0;
uint8_t sizedbg = 0;
uint8_t buttons = 0;
int8_t poziom = 0;
uint16_t licznik10ms = 0;
uint8_t buttonswait;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_SYSTICK_Callback(void) {
	licznik10ms++;
	if(licznik10ms == 10) {
		licznik10ms = 0;
		if(buttonswait) buttonswait--;
		BUTTONS();
		HAL_GPIO_TogglePin(D1_LED_GPIO_Port, D1_LED_Pin);
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  //SysTick_Config(168000000/1000);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM5_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(D1_LED_GPIO_Port, D1_LED_Pin, 1);

  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
  ILI9341_Init();
  ILI9341_FillScreen(ILI9341_BLACK);

  size = sprintf((char*)&tekst, "STARTING...");
  ILI9341_WriteString(0, 0 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_GREEN, ILI9341_BLACK, 11);

  W25qxx_Init();
  size = 0xFF;
  HAL_I2C_Master_Transmit(&hi2c1, 0b01000000,&size , 1, 10);

  size = sprintf((char*)&tekst, "EX_FLASH_INFO:");
  ILI9341_WriteString(0, 1 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_RED, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "UID: %X%X%X%X%X%X%X%X", w25qxx.UniqID[7], w25qxx.UniqID[6], w25qxx.UniqID[5], w25qxx.UniqID[4], w25qxx.UniqID[3], w25qxx.UniqID[2], w25qxx.UniqID[1], w25qxx.UniqID[0]);
  ILI9341_WriteString(0, 2 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "PAGE_SIZE: %u", w25qxx.PageSize);
  ILI9341_WriteString(0, 3 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "PAGE_COUNT: %lu",w25qxx.PageCount);
  ILI9341_WriteString(0, 4 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "SECTOR_SIZE: %lu", w25qxx.SectorSize);
  ILI9341_WriteString(0, 5 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "SECTOR_COUNT: %lu", w25qxx.SectorCount);
  ILI9341_WriteString(0, 6 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "BLOCK_SIZE: %lu", w25qxx.BlockSize);
  ILI9341_WriteString(0, 7 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "BLOCK_COUNT: %lu", w25qxx.BlockCount);
  ILI9341_WriteString(0, 8 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "CAPACITY: %luKB", w25qxx.CapacityInKiloByte);
  ILI9341_WriteString(0, 9 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  HAL_Delay(200);
  ILI9341_FillScreen(ILI9341_BLACK);

  size = sprintf((char*)&tekst, "GENERATOR");
  ILI9341_WriteString(0 * 8, 1 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
  size = sprintf((char*)&tekst, "OSCYLOSKOP");
  ILI9341_WriteString(0 * 8, 4 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
  size = sprintf((char*)&tekst, "TEST");
  ILI9341_WriteString(0 * 8, 9 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
  size = sprintf((char*)&tekst, "RESET");
  ILI9341_WriteString(0 * 8, 12 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);

  size = sprintf((char*)&tekst, "FFT");
  ILI9341_WriteString(30 * 8, 1 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);
  size = sprintf((char*)&tekst, "ZEROWANIE");
  ILI9341_WriteString(24 * 8, 4 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_WHITE, ILI9341_BLACK, size);


  size = sprintf((char*)&tekst, "[BRAK]");
  ILI9341_WriteString(10 * 8, 4 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_RED, ILI9341_BLACK, size);
  ILI9341_WriteString(33 * 8, 1 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_RED, ILI9341_BLACK, size);
  ILI9341_WriteString(33 * 8, 4 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_RED, ILI9341_BLACK, size);

  while(!buttons) {
	  //HAL_I2C_Master_Receive(&hi2c1, 0b01000000, &buttons, 1, 10);
	  //buttons = ~buttons;
  }
  switch(buttons) {
  case (0b10000000) : //generator
		GENERATOR();
		break;
  case (0b01000000) : //oscyloskop
		NVIC_SystemReset();
		break;
  case (0b00100000) : //test
  		TEST();
  		break;
  case (0b00010000) : //reset
  		NVIC_SystemReset();
  		break;
  case (0b00001000) : //FFT
		NVIC_SystemReset();
  		break;
  case (0b00000100) : //zerowanko ADC
		NVIC_SystemReset();
  		break;
  case (0b00000010) : //
		NVIC_SystemReset();
  		break;
  case (0b00000001) : //
		NVIC_SystemReset();
  		break;
  default: //kilka przycisków na raz
	  NVIC_SystemReset();
	  break;
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  ILI9341_FillScreen(ILI9341_BLACK);
  size = sprintf((char*)&tekst, "FAIL");
  ILI9341_WriteString(0, 0 * 18, (char*)&tekst, Font_DOS8x16, ILI9341_RED, ILI9341_BLACK, size);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
