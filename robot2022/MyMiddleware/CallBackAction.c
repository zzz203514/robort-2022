/**
  ******************************************************************************
  * @file    CallBackAction.c
  * @author  俞立，何志远，庄文标
  * @brief   回调函数
  *
	@verbatim
	
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "CallBackAction.h"

uint8_t temp[15];
	int i;

//定时器中断
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  //10ms 状态机
	if(htim == &htim2)
	{
//		FSMRun(&CarFSM);		
		GraySensorFifteenAnalogValueGet();
		SumofReceiveValue();
		GraySensorConfigLineLight();
		UpORDown();
	}
  //10ms 传感器读取
//	if(htim == &htim3)
//	{

//		DiffuseReflectionLaserStateJudge();
//		RangingLaserPollingDistanceProcess();
//		MatrixKeyBoardConfirm();
//	}
  //500ms LED判断工作状态（完善）
//	if(htim == &htim4)
//	{
//		DebugMotor();
//		HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_GPIO_PIN);
//	}
}


//此行以下请勿随意修改！！！！！！
//*****************************************************************
//*****************************************************************
//串口接收中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	//陀螺仪（完善）  6.1
	if(huart == &GyroUartHandle)
	{
////		if(!GyroCheckSumJudge() && !CarFSM.CurState)
////		{
////			HAL_NVIC_SystemReset();
////		}			
////		else
////		{
////			GyroGetAllAngles();
////		}
//		
//	//DMA正常模式代码（保留备用，请勿删除！！！！！！）
		if(GyroReceiveNum == 0)
		{
			if(GyroReceiveBuffer[0] != 0x55)
				GyroReceiveNum = 0;
			else
				GyroReceiveNum = 1;
			if(HAL_UART_Receive_DMA(&GyroUartHandle, &GyroReceiveBuffer[GyroReceiveNum], 1) != HAL_OK)
				Error_Handler();
		}
		else if(GyroReceiveNum == 1)
		{
			if(GyroReceiveBuffer[1] != 0x53)
			{
				GyroReceiveNum = 0;
				if(HAL_UART_Receive_DMA(&GyroUartHandle, &GyroReceiveBuffer[GyroReceiveNum], 1) != HAL_OK)
					Error_Handler();
			}
			else
			{
				GyroReceiveNum = 2;
				if(HAL_UART_Receive_DMA(&GyroUartHandle, &GyroReceiveBuffer[GyroReceiveNum], 9) != HAL_OK)
					Error_Handler();
			}
		}
		else if(GyroReceiveNum == 2)
    {
			if(GyroCheckSumJudge())
				GyroGetAllAngles();
			GyroReceiveNum = 0;
			if(HAL_UART_Receive_DMA(&GyroUartHandle, &GyroReceiveBuffer[GyroReceiveNum], 1) != HAL_OK)
					Error_Handler();
    }
		else
		{
			GyroReceiveNum = 0;
			if(HAL_UART_Receive_DMA(&GyroUartHandle, &GyroReceiveBuffer[GyroReceiveNum], 1) != HAL_OK)
					Error_Handler();
		}
	}
//	//灰度传感器（完善）  5.12
	if(huart == &GraySensorUartHandle)
	{
		GraySensorRecieveFlag = 1;
	}
	
// K210返回关于颜色的数据
	if(huart->Instance==UART8)
  {
		uint8_t tem1[5];
		for(int i=0;i<5;i++)
		{
			tem1[i]=uart8_rxbuff[i];
			//printf("%d,%d\r\n",i,tem1[i]);       
		}
			K210_Color_Data(tem1);
  }	
// K210返回二维码和白板数据
	if(huart->Instance==UART5)
	{
		uint8_t tem2[5];
		for(int i=0;i<5;i++)
		{
			tem2[i]=usart2_rxbuff[i];
			//printf("%d,%d\r\n",i,tem2[i]); 
				//printf("1\r\n");
		}
			K210_Qrcode_Data(tem2);		
}
}

//串口发送中断
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//灰度传感器（完善）  5.12
	if(huart == &GraySensorUartHandle)
	{
		GraySensorTransferFlag = 1;
	}
}

//*****************************************************************
//外部中断
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//漫反射激光传感器（基本完善）  5.23
  if(GPIO_Pin == LEFT_DRLASER_GPIO_PIN)
	{
		DiffuseReflectionLaserChangeSetLeft();
	}
	else if(GPIO_Pin == RIGHT_DRLASER_GPIO_PIN)
	{
		DiffuseReflectionLaserChangeSetRight();
	}
	
	//测距激光传感器
//	if(GPIO_Pin == RANGINGLASER_GPIO1_GPIO_PIN)
//		RangingLaserInterruptDistanceProcess();
//	
//	//矩阵键盘（基本完善）  6.1
//	if(GPIO_Pin == COLUMN1_PIN)
//		KeyState = 1;
//	else if(GPIO_Pin == COLUMN2_PIN)
//		KeyState = 2;
//	else if(GPIO_Pin == COLUMN3_PIN)
//		KeyState = 3;
//	else if(GPIO_Pin == COLUMN4_PIN)
//		KeyState = 4;
}
