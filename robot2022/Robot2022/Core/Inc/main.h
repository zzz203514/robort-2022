/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define Right_Front_encoder_Pin GPIO_PIN_0
#define Right_Front_encoder_GPIO_Port GPIOA
#define Right_Front_encoderA1_Pin GPIO_PIN_1
#define Right_Front_encoderA1_GPIO_Port GPIOA
#define Right_motor_Pin GPIO_PIN_6
#define Right_motor_GPIO_Port GPIOA
#define Left_motor_Pin GPIO_PIN_7
#define Left_motor_GPIO_Port GPIOA
#define Left_Motor_enable_2_Pin GPIO_PIN_9
#define Left_Motor_enable_2_GPIO_Port GPIOE
#define Right_Motor_enable_2_Pin GPIO_PIN_11
#define Right_Motor_enable_2_GPIO_Port GPIOE
#define Left_Rear_encoder_Pin GPIO_PIN_12
#define Left_Rear_encoder_GPIO_Port GPIOD
#define Left_Rear_encoderD13_Pin GPIO_PIN_13
#define Left_Rear_encoderD13_GPIO_Port GPIOD
#define Left_Motor_enable_1_Pin GPIO_PIN_2
#define Left_Motor_enable_1_GPIO_Port GPIOD
#define Right_Motor_enable_1_Pin GPIO_PIN_3
#define Right_Motor_enable_1_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
