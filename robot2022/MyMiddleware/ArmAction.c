/**
  ******************************************************************************
  * @file    ArmAction.c
  * @author  庄文标
  * @brief   机械臂抓取动作
  *
  @verbatim
	摇头舵机5V电源，摇臂舵机7.2-8V电源
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "ArmAction.h"

/**
 ******************************************************************************
 *  @defgroup 外部调用
 *  @brief
 *
**/

void ArmGrab()
{
	__HAL_TIM_SetCompare(&htim3, ARM_CHANNEL, 82);//抓取占空比设置	
	__HAL_TIM_SetCompare(&htim3, CLAMP_CHANNEL, 92);//夹取占空比设置
}

void ArmPut()
{
	__HAL_TIM_SetCompare(&htim3, CLAMP_CHANNEL, 125);//放开占空比设置		
	__HAL_TIM_SetCompare(&htim3, ARM_CHANNEL, 171);//放置占空比设置
}
