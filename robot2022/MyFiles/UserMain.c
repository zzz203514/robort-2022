/**
  ******************************************************************************
  * @file    UserMain.c
  * @author  ��������־Զ�������ڣ�ׯ�ı�
  * @brief   ������
  *
	@verbatim
	ע�⣬�������״̬�������г��ֳ����ͷ��ʼ�ܣ���������DMAǱ���жϸ�λ�����⣬
	���YL��ϵ
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "UserMain.h"
#include "main.h"

//�������ʼ��
void UserInit(void)  
{
//	//�����ǳ�ʼ���������ڵ�һ��
	    GyroInit();		
//	
//	//�Ҷȴ�������ʼ��
	    GraySensorInit();
	
//	//���ģ���ʼ��
	    MotorInit();
	
//	//�����ʼ��
	  ServoMotorInit();
	
//	//������̳�ʼ��
//	MatrixKeyBoardInit();
	
//  //K210��ʼ��
		K210Init();
	
	//����PID��ʼ��
//   TurnPidInit();
	 LinePIDInit();
	
//	//״̬����ʼ��
//	FSMInit(&CarFSM, A, CarTable);

	//��ʱ������
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim2);
}

//������ѭ��
void UserLoop(void)  
{
	//���ԣ���Ļ��Ӧͦ�ٶ۵Ĳο��ã�
//	DebugGyro();
//	
//	DebugGraySensor();
//	
//	DebugServoMotor();
//	
//	DebugDiffuseReflectionLaser();
//
//	DebugRangingLaser();
//
//	DebugK210Data();
}

