/**
  ******************************************************************************
  * @file    ServoMotor.c
  * @author  ����
  * @brief   �ŷ��������
  *
  @verbatim
	ҡͷ���5V��Դ��ҡ�۶��7.2-8V��Դ
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "ServoMotor.h"

/**
 ******************************************************************************
 *  @defgroup �ⲿ����
 *  @brief
 *
**/
//���������ʼ��
void ServoMotorInit(void)
{
	HAL_TIM_PWM_Start(&htim3, CLAMP_CHANNEL);
	HAL_TIM_PWM_Start(&htim3, ARM_CHANNEL);
//	ServoMotorAngleSet(LEFT_ARM_SERVO_CHANNEL, 90);
//	ServoMotorAngleSet(RIGHT_ARM_SERVO_CHANNEL, 90);
}

//����Ƕ����� ��Χ��0~180��
void ServoMotorAngleSet(uint32_t channel, uint8_t angle)
{
	__HAL_TIM_SetCompare(&htim3, channel, 5+angle/9);
}