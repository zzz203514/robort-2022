/**
  ******************************************************************************
  * @file    DiffuseReflectionLaser.c
  * @author  ׯ�ı�
  * @brief   �����伤�⴫�����������������ƣ�
  *
  @verbatim
	�߷����ʱ���  LED�� ����͵�ƽ
  �ͷ����ʱ���  LED�� ����ߵ�ƽ

	����          �ڰ�����      �߷����� LED�� �͵�ƽ
		            ����̺��      �ͷ����� LED�� �ߵ�ƽ

	���          �ͷ����ʵ��߷�����      ������ �½���
								�߷����ʵ��ͷ�����      ������ ������
	5V����
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "DiffuseReflectionLaser.h"

/* Define\Declare ------------------------------------------------------------*/
uint8_t MedicineFlag = 0;

/**
 ******************************************************************************
 *  @defgroup �ⲿ����
 *  @brief 
 *
**/
//�����伤���ʼ��
void DiffuseReflectionLaserChangeSetLeft(void)
{
	 if(HAL_GPIO_ReadPin(DRLASER_GPIO_PORT,LEFT_DRLASER_GPIO_PIN) == 0)
		MedicineFlag = 1;
	
	 else MedicineFlag = 0;
	

}

void DiffuseReflectionLaserChangeSetRight(void)
{
		if(HAL_GPIO_ReadPin(DRLASER_GPIO_PORT,RIGHT_DRLASER_GPIO_PIN) == 0)
		 MedicineFlag = 1;
		
	  else MedicineFlag = 0;

}
