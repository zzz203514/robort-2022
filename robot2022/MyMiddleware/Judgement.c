/**
  ******************************************************************************
  * @file    Judgement.c
  * @author  ׯ�ı�
  * @brief   �ж�ģ��
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

int UpORDown(void)//�жϴ������»�������
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


double SumofReceiveValue(void)//��ȡ�ܵ�ģ��ֵ�����ж��Ƿ񵽴�·��
{
   for(uint8_t i = 0;i<15;i++)
			SumOfValue += GraySensorOneOfFifteenReceiveValueGet(i);
//    printf("SumOfValue = %lf\r\n", SumOfValue);
	
	 return SumOfValue;

}