/**
  ******************************************************************************
  * @file    LinePatrolAction.c
  * @author  ׯ�ı�
  * @brief   Ѳ�߶���
  * 
	@verbatim
	
	@endverbatim
  * @{
**/


/* Includes ------------------------------------------------------------------*/
#include "LinePatrolAction.h"


/* Define\Declare ------------------------------------------------------------*/
//pid�Ķ���
Pid_TypeDef NormalLinepid;
Pid_TypeDef BringeSpeedLinepid;
Pid_TypeDef LowSpeedLinepid;
Pid_TypeDef CircleLinepid;


double BasicSpeed = 20;
#define NormalYawAngle -28
//pid�ĳ�ʼ�� 36000 36 һ��ʮ��֮�� 33000 60
void LinePIDInit(void)
{
	PIDInit(&BringeSpeedLinepid, 0.1, 0, 0);
  PIDInit(&NormalLinepid, 42500 ,0, 0);
	PIDInit(&LowSpeedLinepid, 0 , 0, 0);
	PIDInit(&CircleLinepid, 0 , 0, 0);
}


//�����ٶ�Ѳ��
void NormalLineSpeedPatrol(void)
{
	SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&NormalLinepid,GraySensorBiasGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&NormalLinepid,GraySensorBiasGet()) );
	double lSpeed = BasicSpeed + GetPIDValue(&NormalLinepid,GraySensorBiasGet());
	double rSpeed = BasicSpeed - GetPIDValue(&NormalLinepid,GraySensorBiasGet());
	printf("lspeed = %lf\r\n",lSpeed);
		printf("rspeed = %lf\r\n",rSpeed);
}


//����Ѳ��
void LowSpeedLinePatrol(void)
{
	SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
}


//Բ����Ѳ��
void CirclePatrol(void)
{
  SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
}



//����Ѳ��
void GoBrige(void)
{
//	double a = GetPIDValue(&BringeSpeedLinepid,YawangleerroGet());
//	printf("%lf\r\n",a);
	SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&BringeSpeedLinepid,YawangleerroGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&BringeSpeedLinepid,YawangleerroGet()) );
}





//�Ƕ�����ȡ
double YawangleerroGet(void)
{
	double AngleBias;
	
	AngleBias = GyroYawAngleGet();
	
	return AngleBias;
}



//��ȡ�Ҷ�����������ظ�pid���м���
double GraySensorBiasGet(void)
{
	uint8_t i;
	uint16_t temp1, temp2;
	double Bias;
//	GraySensorFifteenLineValueGet();
	
	for (i = 0; i < 7; i++)
			temp1 += GraySensorOneOfFifteenReceiveValueGet(i) + GraySensorOneOfFifteenReceiveValueGet(7) / 2;  //�㷨�д��Ľ�
	for (i = 8; i < 15; i++)
			temp2 += GraySensorOneOfFifteenReceiveValueGet(i) + GraySensorOneOfFifteenReceiveValueGet(7) / 2;
	
	Bias = (sqrt(temp1) - sqrt(temp2)) / (temp1 + temp2);
	
	printf("%lf\r\n", Bias);  //������ 
	
	return Bias;
}
