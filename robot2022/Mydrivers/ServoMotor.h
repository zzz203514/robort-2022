#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "tim.h"

#define SERVOMOTOR_TIM3_CH1_GPIO_PORT  GPIOA      
#define SERVOMOTOR_TIM3_CH1_GPIO_PIN   GPIO_PIN_6
#define SERVOMOTOR_TIM3_CH2_GPIO_PORT  GPIOA 
#define SERVOMOTOR_TIM3_CH2_GPIO_PIN   GPIO_PIN_7


//CH1和CH3为手臂舵机，CH2为摇头舵机
#define CLAMP_CHANNEL  TIM_CHANNEL_1
#define ARM_CHANNEL TIM_CHANNEL_2

void ServoMotorInit(void);
void ServoMotorAngleSet(uint32_t channel, uint8_t angle);

#endif