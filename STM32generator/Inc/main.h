/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <inttypes.h>
#include "ili9341_driver.h"
#include "ili9341_GFX.h"
#include "w25qxx.h"
#include "tasks.h"
#include "loaders.h"
#include "AD9833.h"
#include "grafiki.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENC_1_Pin GPIO_PIN_0
#define ENC_1_GPIO_Port GPIOA
#define ENC_2_Pin GPIO_PIN_1
#define ENC_2_GPIO_Port GPIOA
#define K1_BUTTON_Pin GPIO_PIN_6
#define K1_BUTTON_GPIO_Port GPIOA
#define K1_BUTTON_EXTI_IRQn EXTI9_5_IRQn
#define AD9833_FNC_Pin GPIO_PIN_5
#define AD9833_FNC_GPIO_Port GPIOC
#define AD9833_DAT_Pin GPIO_PIN_0
#define AD9833_DAT_GPIO_Port GPIOB
#define AD9833_CLK_Pin GPIO_PIN_1
#define AD9833_CLK_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define TFT_CS_Pin GPIO_PIN_12
#define TFT_CS_GPIO_Port GPIOB
#define TFT_SPI2_SCK_Pin GPIO_PIN_13
#define TFT_SPI2_SCK_GPIO_Port GPIOB
#define TFT_SPI2_MISO_Pin GPIO_PIN_14
#define TFT_SPI2_MISO_GPIO_Port GPIOB
#define TFT_SPI2_MOSI_Pin GPIO_PIN_15
#define TFT_SPI2_MOSI_GPIO_Port GPIOB
#define TFT_DC_Pin GPIO_PIN_6
#define TFT_DC_GPIO_Port GPIOC
#define TFT_RST_Pin GPIO_PIN_7
#define TFT_RST_GPIO_Port GPIOC
#define D1_LED_Pin GPIO_PIN_8
#define D1_LED_GPIO_Port GPIOA
#define MEM_FLASH_CS_Pin GPIO_PIN_15
#define MEM_FLASH_CS_GPIO_Port GPIOA
#define TFTT_SPI3_SCK_Pin GPIO_PIN_10
#define TFTT_SPI3_SCK_GPIO_Port GPIOC
#define TFTT_SPI3_MISO_Pin GPIO_PIN_11
#define TFTT_SPI3_MISO_GPIO_Port GPIOC
#define TFTT_SPI3_MOSI_Pin GPIO_PIN_12
#define TFTT_SPI3_MOSI_GPIO_Port GPIOC
#define TFTT_CS_Pin GPIO_PIN_2
#define TFTT_CS_GPIO_Port GPIOD
#define MEM_SPI1_SCK_Pin GPIO_PIN_3
#define MEM_SPI1_SCK_GPIO_Port GPIOB
#define MEM_SPI1_MISO_Pin GPIO_PIN_4
#define MEM_SPI1_MISO_GPIO_Port GPIOB
#define MEM_SPI1_MOSI_Pin GPIO_PIN_5
#define MEM_SPI1_MOSI_GPIO_Port GPIOB
#define TFTT_IRQ_Pin GPIO_PIN_7
#define TFTT_IRQ_GPIO_Port GPIOB
#define TFTT_IRQ_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
