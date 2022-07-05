/**
  ******************************************************************************
  * @file    CallBackAction.c
  * @author  ��������־Զ��ׯ�ı�
  * @brief   �ص�����
  *
	@verbatim
	
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "CallBackAction.h"

uint8_t temp[15];
	int i;

//��ʱ���ж�
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  //10ms ״̬��
	if(htim == &htim2)
	{
//		FSMRun(&CarFSM);		
		GraySensorFifteenAnalogValueGet();
		SumofReceiveValue();
		GraySensorConfigLineLight();
		UpORDown();
	}
  //10ms ��������ȡ
//	if(htim == &htim3)
//	{

//		DiffuseReflectionLaserStateJudge();
//		RangingLaserPollingDistanceProcess();
//		MatrixKeyBoardConfirm();
//	}
  //500ms LED�жϹ���״̬�����ƣ�
//	if(htim == &htim4)
//	{
//		DebugMotor();
//		HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_GPIO_PIN);
//	}
}


//�����������������޸ģ�����������
//*****************************************************************
//*****************************************************************
//���ڽ����ж�
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	//�����ǣ����ƣ�  6.1
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
//	//DMA����ģʽ���루�������ã�����ɾ����������������
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
//	//�Ҷȴ����������ƣ�  5.12
	if(huart == &GraySensorUartHandle)
	{
		GraySensorRecieveFlag = 1;
	}
	
// K210���ع�����ɫ������
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
// K210���ض�ά��Ͱװ�����
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

//���ڷ����ж�
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//�Ҷȴ����������ƣ�  5.12
	if(huart == &GraySensorUartHandle)
	{
		GraySensorTransferFlag = 1;
	}
}

//*****************************************************************
//�ⲿ�ж�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//�����伤�⴫�������������ƣ�  5.23
  if(GPIO_Pin == LEFT_DRLASER_GPIO_PIN)
	{
		DiffuseReflectionLaserChangeSetLeft();
	}
	else if(GPIO_Pin == RIGHT_DRLASER_GPIO_PIN)
	{
		DiffuseReflectionLaserChangeSetRight();
	}
	
	//��༤�⴫����
//	if(GPIO_Pin == RANGINGLASER_GPIO1_GPIO_PIN)
//		RangingLaserInterruptDistanceProcess();
//	
//	//������̣��������ƣ�  6.1
//	if(GPIO_Pin == COLUMN1_PIN)
//		KeyState = 1;
//	else if(GPIO_Pin == COLUMN2_PIN)
//		KeyState = 2;
//	else if(GPIO_Pin == COLUMN3_PIN)
//		KeyState = 3;
//	else if(GPIO_Pin == COLUMN4_PIN)
//		KeyState = 4;
}
