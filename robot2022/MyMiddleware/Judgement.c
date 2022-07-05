/**
  ******************************************************************************
  * @file    Judgement.c
  * @author  庄文标
  * @brief   判断模块
  * 
	@verbatim
	
	@endverbatim
  * @{
**/
/* Includes ------------------------------------------------------------------*/
#include "Judgement.h"


/* Define\Declare ------------------------------------------------------------*/
#define NormalPitchangle 8
int Flag = 1;
double SumOfValue = 0;

int UpORDown(void)//判断处于上坡还是下坡
{
	int  UpORDown;
	if(GyroPitchAngleGet() - NormalPitchangle>10)
	{
		UpORDown = 1;
	}
	else if(GyroPitchAngleGet() - NormalPitchangle<-10)
	{
		UpORDown = 0;
	}
	else if((GyroPitchAngleGet() - NormalPitchangle<5) && (GyroPitchAngleGet() - NormalPitchangle>-5) )
	{
		UpORDown = 2;
	}
	
	return UpORDown;
}


double SumofReceiveValue(void)//获取总的模拟值用来判断是否到达路口
{
   for(uint8_t i = 0;i<15;i++)
			SumOfValue += GraySensorOneOfFifteenReceiveValueGet(i);
//    printf("SumOfValue = %lf\r\n", SumOfValue);
	
	 return SumOfValue;

}