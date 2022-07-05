/**
  ******************************************************************************
  * @file    Miscellaneous.c
  * @author  俞立，庄文标
  * @brief   不易分类的模块及接口
  *
	@verbatim
	
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "Miscellaneous.h"

/* Define\Declare ------------------------------------------------------------*/
uint8_t buffer[40];

int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&BlueTeethUartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

/**
 ******************************************************************************
 *  @defgroup 数据测试
 *  @brief
 *
**/
//陀螺仪数据测试
void DebugGyro(void)
{
	  //AngleGet();
//	  GyroGetAllAngles();
//	  memset(buffer, 0x00, sizeof(buffer));
		sprintf((char*)buffer, "Angle: %.3lf  %.3lf  %.3lf", GyroRollAngleGet(), GyroPitchAngleGet(), GyroYawAngleGet());
	  printf("%s",buffer);
//	Gui_DrawFont_GBK16(5, 5, WHITE, BLACK, buffer);
}

//灰度传感器测试
void DebugGraySensor(void)
{
	
	uint8_t temp[15];
	int i;
	for(i=0; i<15; i++)
		temp[i] = GraySensorOneOfFifteenReceiveValueGet(i);
//	memset(buffer, 0x00, sizeof(buffer));
	printf("GraySensor: %d  %d  %d  %d  %d  ", temp[0], temp[1], temp[2], temp[3], temp[4]);
	printf( "%d  %d  %d  %d  %d  ", temp[5], temp[6], temp[7], temp[8], temp[9]);
	printf( "%d  %d  %d  %d  %d  ", temp[10], temp[11], temp[12], temp[13], temp[14]);
//	Gui_DrawFont_GBK16(100, 65, WHITE, BLACK, buffer);
}

void DebugK210Data(void)
{
	uint8_t lo1=0,lo2=0,lo3=0,QR,block,TrueOne;//block=0;
	if(QR==1)
		printf("One:%d\r\nTwo:%d\r\nThree:%d\r\n",lo1,lo2,lo3);
	if(block==0)
		printf("block: %d\r\n",block);
	if(TrueOne==1)
		printf("TrueOne:%d\r\n",TrueOne);
	
}


//测距激光传感器测试
//void DebugRangingLaser(void)
//{
//	memset(buffer, 0x00, sizeof(buffer));
//	sprintf((char*)buffer, "RangingLaser: %d  ", RangingLaserDistanceGet());
//	Gui_DrawFont_GBK16(5, 105, WHITE, BLACK, buffer);
//}