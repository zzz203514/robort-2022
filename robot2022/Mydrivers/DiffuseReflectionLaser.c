/**
  ******************************************************************************
  * @file    DiffuseReflectionLaser.c
  * @author  庄文标
  * @brief   漫反射激光传感器驱动（基本完善）
  *
  @verbatim
	高反射率表面  LED亮 输出低电平
  低反射率表面  LED灭 输出高电平

	例如          在白线上      高反射率 LED亮 低电平
		            在绿毯上      低反射率 LED灭 高电平

	因此          低反射率到高反射率      负跳变 下降沿
								高反射率到低反射率      正跳变 上升沿
	5V供电
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "DiffuseReflectionLaser.h"

/* Define\Declare ------------------------------------------------------------*/
uint8_t MedicineFlag = 0;

/**
 ******************************************************************************
 *  @defgroup 外部调用
 *  @brief 
 *
**/
//漫反射激光初始化
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
