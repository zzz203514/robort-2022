#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS_H_

#include <stdio.h>
#include "usart.h"
#include "Gyro.h"
#include "GraySensor.h"
//#include "DiffuseReflectionLaser.h"
//#include "RangingLaser.h"

//???????Կ?
#define BLUETEETH_UART1_TX_GPIO_PORT  GPIOB      
#define BLUETEETH_UART1_TX_GPIO_PIN   GPIO_PIN_14
#define BLUETEETH_UART1_RX_GPIO_PORT  GPIOB
#define BLUETEETH_UART1_RX_GPIO_PIN   GPIO_PIN_15

#define BlueTeethUartHandle huart1

//LED
#define LED_GPIO_PORT  GPIOC      
#define LED_GPIO_PIN   GPIO_PIN_13 


int fputc(int ch, FILE *f);
//????
void DebugGyro(void);
void DebugGraySensor(void);
void DebugServoMotor(void);
void DebugDiffuseReflectionLaser(void);
void DebugRangingLaser(void);

#endif
