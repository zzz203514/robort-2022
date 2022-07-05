/**
  ******************************************************************************
  * @file    LinePatrolAction.c
  * @author  庄文标
  * @brief   巡线动作
  * 
	@verbatim
	
	@endverbatim
  * @{
**/


/* Includes ------------------------------------------------------------------*/
#include "LinePatrolAction.h"


/* Define\Declare ------------------------------------------------------------*/
//pid的定义
Pid_TypeDef NormalLinepid;
Pid_TypeDef BringeSpeedLinepid;
Pid_TypeDef LowSpeedLinepid;
Pid_TypeDef CircleLinepid;


double BasicSpeed = 20;
#define NormalYawAngle -28
//pid的初始化 36000 36 一万到十万之间 33000 60
void LinePIDInit(void)
{
	PIDInit(&BringeSpeedLinepid, 0.1, 0, 0);
  PIDInit(&NormalLinepid, 42500 ,0, 0);
	PIDInit(&LowSpeedLinepid, 0 , 0, 0);
	PIDInit(&CircleLinepid, 0 , 0, 0);
}


//正常速度巡线
void NormalLineSpeedPatrol(void)
{
	SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&NormalLinepid,GraySensorBiasGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&NormalLinepid,GraySensorBiasGet()) );
	double lSpeed = BasicSpeed + GetPIDValue(&NormalLinepid,GraySensorBiasGet());
	double rSpeed = BasicSpeed - GetPIDValue(&NormalLinepid,GraySensorBiasGet());
	printf("lspeed = %lf\r\n",lSpeed);
		printf("rspeed = %lf\r\n",rSpeed);
}


//低速巡线
void LowSpeedLinePatrol(void)
{
	SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
}


//圆环的巡线
void CirclePatrol(void)
{
  SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&LowSpeedLinepid,GraySensorBiasGet()) );
}



//过桥巡线
void GoBrige(void)
{
//	double a = GetPIDValue(&BringeSpeedLinepid,YawangleerroGet());
//	printf("%lf\r\n",a);
	SetMotorSpeed(LMotor, BasicSpeed + GetPIDValue(&BringeSpeedLinepid,YawangleerroGet()) );
	SetMotorSpeed(RMotor, BasicSpeed - GetPIDValue(&BringeSpeedLinepid,YawangleerroGet()) );
}





//角度误差获取
double YawangleerroGet(void)
{
	double AngleBias;
	
	AngleBias = GyroYawAngleGet();
	
	return AngleBias;
}



//获取灰度误差用来返回给pid进行计算
double GraySensorBiasGet(void)
{
	uint8_t i;
	uint16_t temp1, temp2;
	double Bias;
//	GraySensorFifteenLineValueGet();
	
	for (i = 0; i < 7; i++)
			temp1 += GraySensorOneOfFifteenReceiveValueGet(i) + GraySensorOneOfFifteenReceiveValueGet(7) / 2;  //算法有待改进
	for (i = 8; i < 15; i++)
			temp2 += GraySensorOneOfFifteenReceiveValueGet(i) + GraySensorOneOfFifteenReceiveValueGet(7) / 2;
	
	Bias = (sqrt(temp1) - sqrt(temp2)) / (temp1 + temp2);
	
	printf("%lf\r\n", Bias);  //测试用 
	
	return Bias;
}
