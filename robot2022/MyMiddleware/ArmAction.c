/**
  ******************************************************************************
  * @file    ArmAction.c
  * @author  ׯ�ı�
  * @brief   ��е��ץȡ����
  *
  @verbatim
	ҡͷ���5V��Դ��ҡ�۶��7.2-8V��Դ
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "ArmAction.h"

/**
 ******************************************************************************
 *  @defgroup �ⲿ����
 *  @brief
 *
**/

void ArmGrab()
{
	__HAL_TIM_SetCompare(&htim3, ARM_CHANNEL, 82);//ץȡռ�ձ�����	
	__HAL_TIM_SetCompare(&htim3, CLAMP_CHANNEL, 92);//��ȡռ�ձ�����
}

void ArmPut()
{
	__HAL_TIM_SetCompare(&htim3, CLAMP_CHANNEL, 125);//�ſ�ռ�ձ�����		
	__HAL_TIM_SetCompare(&htim3, ARM_CHANNEL, 171);//����ռ�ձ�����
}
