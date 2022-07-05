/**
  ******************************************************************************
  * @file    motor.c
  * @author  庄文标
  * @brief   电机驱动
  * 
	@verbatim
	
	@endverbatim
  * @{
**/


/* Includes ------------------------------------------------------------------*/
#include "motor.h"

void MotorInit()
{
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

}

void SetMotorSpeed(MotorHandle Motor, float PWMDuty)
{
   int isnForward = 0;       
    double tmp = 0;
    double PWMCount = 0;
    if(PWMDuty<0){
        tmp = -PWMDuty;
        isnForward = 1;
    }
    else{
      tmp = PWMDuty;
      isnForward = 0;
    }

    PWMCount = PWM_MAX * (tmp / 100);
   switch(Motor)
 {
    case LMotor:
        if(isnForward==0)
        {
           HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4,GPIO_PIN_SET);
        }
        else if(isnForward==1)
        {
           HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4,GPIO_PIN_RESET);
        }
        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (uint16_t)PWMCount);
        break;
    case RMotor:
        if(isnForward==0)
        {
           HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_SET);
        }
        else if(isnForward==1)
        {
           HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5,GPIO_PIN_RESET);
        }
        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, (uint16_t)PWMCount);
        break;
  }

}
