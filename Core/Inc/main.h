/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define SIG_MULTIPLEXER_Pin GPIO_PIN_2
#define SIG_MULTIPLEXER_GPIO_Port GPIOE
#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define S3_MULTIPLEXER_Pin GPIO_PIN_4
#define S3_MULTIPLEXER_GPIO_Port GPIOE
#define S2_MULTIPLEXER_Pin GPIO_PIN_5
#define S2_MULTIPLEXER_GPIO_Port GPIOE
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define IO_IN4_Pin GPIO_PIN_1
#define IO_IN4_GPIO_Port GPIOC
#define IO_IN5_Pin GPIO_PIN_2
#define IO_IN5_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define S0_MULTIPLEXER_Pin GPIO_PIN_3
#define S0_MULTIPLEXER_GPIO_Port GPIOA
#define I2S3_WS_Pin GPIO_PIN_4
#define I2S3_WS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define IO_IN6_Pin GPIO_PIN_5
#define IO_IN6_GPIO_Port GPIOC
#define IO_IN1_Pin GPIO_PIN_0
#define IO_IN1_GPIO_Port GPIOB
#define IO_IN2_Pin GPIO_PIN_1
#define IO_IN2_GPIO_Port GPIOB
#define IO_IN3_Pin GPIO_PIN_2
#define IO_IN3_GPIO_Port GPIOB
#define S1_MULTIPLEXER_Pin GPIO_PIN_7
#define S1_MULTIPLEXER_GPIO_Port GPIOE
#define LCD_RS_Pin GPIO_PIN_8
#define LCD_RS_GPIO_Port GPIOE
#define LCD_ENABLE_Pin GPIO_PIN_9
#define LCD_ENABLE_GPIO_Port GPIOE
#define LCD_D4_Pin GPIO_PIN_10
#define LCD_D4_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_11
#define LCD_D5_GPIO_Port GPIOE
#define LCD_D6_Pin GPIO_PIN_12
#define LCD_D6_GPIO_Port GPIOE
#define LCD_D7_Pin GPIO_PIN_13
#define LCD_D7_GPIO_Port GPIOE
#define IO_OUT9_Pin GPIO_PIN_14
#define IO_OUT9_GPIO_Port GPIOE
#define IO_OUT10_Pin GPIO_PIN_15
#define IO_OUT10_GPIO_Port GPIOE
#define DRIVE_LEN_Pin GPIO_PIN_11
#define DRIVE_LEN_GPIO_Port GPIOB
#define IO_OUT5_Pin GPIO_PIN_12
#define IO_OUT5_GPIO_Port GPIOB
#define IO_OUT6_Pin GPIO_PIN_13
#define IO_OUT6_GPIO_Port GPIOB
#define IO_OUT7_Pin GPIO_PIN_14
#define IO_OUT7_GPIO_Port GPIOB
#define IO_OUT8_Pin GPIO_PIN_15
#define IO_OUT8_GPIO_Port GPIOB
#define IO_OUT1_Pin GPIO_PIN_8
#define IO_OUT1_GPIO_Port GPIOD
#define IO_OUT2_Pin GPIO_PIN_9
#define IO_OUT2_GPIO_Port GPIOD
#define IO_OUT3_Pin GPIO_PIN_10
#define IO_OUT3_GPIO_Port GPIOD
#define IO_OUT4_Pin GPIO_PIN_11
#define IO_OUT4_GPIO_Port GPIOD
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define IO_IN7_Pin GPIO_PIN_6
#define IO_IN7_GPIO_Port GPIOC
#define I2S3_MCK_Pin GPIO_PIN_7
#define I2S3_MCK_GPIO_Port GPIOC
#define IO_IN8_Pin GPIO_PIN_8
#define IO_IN8_GPIO_Port GPIOC
#define IO_IN9_Pin GPIO_PIN_9
#define IO_IN9_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define I2S3_SCK_Pin GPIO_PIN_10
#define I2S3_SCK_GPIO_Port GPIOC
#define IO_IN10_Pin GPIO_PIN_11
#define IO_IN10_GPIO_Port GPIOC
#define I2S3_SD_Pin GPIO_PIN_12
#define I2S3_SD_GPIO_Port GPIOC
#define STEER_DO1_Pin GPIO_PIN_2
#define STEER_DO1_GPIO_Port GPIOD
#define STEER_DO2_Pin GPIO_PIN_3
#define STEER_DO2_GPIO_Port GPIOD
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define STEER_DO4_Pin GPIO_PIN_6
#define STEER_DO4_GPIO_Port GPIOD
#define STEER_DO5_Pin GPIO_PIN_7
#define STEER_DO5_GPIO_Port GPIOD
#define ENCODER_A_Pin GPIO_PIN_4
#define ENCODER_A_GPIO_Port GPIOB
#define ENCODER_B_Pin GPIO_PIN_5
#define ENCODER_B_GPIO_Port GPIOB
#define Audio_SCL_Pin GPIO_PIN_6
#define Audio_SCL_GPIO_Port GPIOB
#define DRIVE_REN_Pin GPIO_PIN_7
#define DRIVE_REN_GPIO_Port GPIOB
#define STEER_DO3_Pin GPIO_PIN_8
#define STEER_DO3_GPIO_Port GPIOB
#define Audio_SDA_Pin GPIO_PIN_9
#define Audio_SDA_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
