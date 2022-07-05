/**
  ******************************************************************************
  * @file    TurnAction.c
  * @author  俞立
  * @brief   转向动作
  *
	@verbatim
	
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "TurnAroundAction.h"

/* Define\Declare ------------------------------------------------------------*/
Pid_TypeDef Pid_Turn;
double TurnSpeed = 0;
#define MOTOR_TurnLeft_StableTime 100
#define MOTOR_TurnRight_StableTime 100
#define MOTOR_TurnRight_WaitTime 100
/**
 ******************************************************************************
 *  @defgroup 外部调用
 *  @brief 
 *
**/

void TurnBack()
{
	float CurrentAngle = 0;
	float TurnAngle = 175;
	
	 HAL_Delay(MOTOR_TurnLeft_StableTime);
	  SetMotorSpeed(LMotor,55);
    SetMotorSpeed(RMotor,-55);
		
		while(GyroYawAngleGet()<-160 || GyroYawAngleGet()>-140)
		{
		}
    SetMotorSpeed(LMotor,0);
		SetMotorSpeed(RMotor,0);
}




void TurnLeft(double Angle)
{
  float CurrentAngle = 0;
	float TurnAngle = 0;
	
	HAL_Delay(MOTOR_TurnLeft_StableTime);
	
	CurrentAngle = GyroYawAngleGet();
	
	if(Angle > CurrentAngle)
	{
		TurnAngle = Angle + CurrentAngle;
    SetMotorSpeed(LMotor,15);
		SetMotorSpeed(RMotor,25);
		
		while(fabs(CurrentAngle + GyroYawAngleGet())!=175)
		{
		}
    SetMotorSpeed(LMotor,0);
		SetMotorSpeed(RMotor,0);
		
		
	}
	else if(Angle < CurrentAngle)
	{
		
		TurnAngle = Angle + CurrentAngle;
		
		if(TurnAngle > 360)
		{
			TurnAngle -= 360;
			
	    HAL_Delay(MOTOR_TurnLeft_StableTime);
      SetMotorSpeed(LMotor,15);
		  SetMotorSpeed(RMotor,25);
			
			while(GyroYawAngleGet() < 157)
			{
			}
			HAL_Delay(70);
			
			while(fabs(TurnAngle - GyroYawAngleGet()) > 15)
			{
			}
      SetMotorSpeed(LMotor,0);
		  SetMotorSpeed(RMotor,0);
			
		}
		else
		{
    SetMotorSpeed(LMotor,15);
		SetMotorSpeed(RMotor,25);
			
			while(fabs(TurnAngle - GyroYawAngleGet()) > 15)
			{
			}
    SetMotorSpeed(LMotor,0);
		SetMotorSpeed(RMotor,0);		
			
		}
	}
	
//	HAL_Delay(MOTOR_TurnLeft_StableTime);
	
	//微调
	
//	while(fabs(TurnAngle - GyroYawAngleGet()) > 1)
//	{
//		if(TurnAngle > GyroYawAngleGet())
//		{
//    SetMotorSpeed(LMotor,15);
//		SetMotorSpeed(RMotor,25);
//		}
//		
//		if(GyroYawAngleGet() > TurnAngle)
//		{
//    SetMotorSpeed(LMotor,15);
//		SetMotorSpeed(RMotor,25);
//		}
//	}
//	
//	
//    SetMotorSpeed(LMotor,0);
//		SetMotorSpeed(RMotor,0);

}


void Motor_TurnRightBlockingMode(float Angle)
{
  float CurrentAngle = 0;
  float TurnAngle = 0;
	
	HAL_Delay(MOTOR_TurnRight_StableTime);

  CurrentAngle = GyroYawAngleGet();

  if(Angle > CurrentAngle)
    {
      TurnAngle = (float)180.0 - (float)(Angle - CurrentAngle);
      SetMotorSpeed(LMotor,25);
		  SetMotorSpeed(RMotor,15);

      while(GyroYawAngleGet() > (float)2)
        {
        }
      HAL_Delay(150);

      while(fabs(GyroYawAngleGet() - TurnAngle) > 15)
        {
        }
    }
  else if(Angle <= CurrentAngle)
    {
      TurnAngle = CurrentAngle - Angle;
      SetMotorSpeed(LMotor,25);
		  SetMotorSpeed(RMotor,15);
      while(fabs(GyroYawAngleGet() - TurnAngle) > 15)
        {
        }
    }


      SetMotorSpeed(LMotor,0);
		  SetMotorSpeed(RMotor,0);
	
  HAL_Delay(MOTOR_TurnRight_WaitTime);
		
	
	//微调
//  while(fabs((double)(TurnAngle - GyroYawAngleGet())) > 2)
//    {
//      if(TurnAngle - GyroYawAngleGet() > (float)2)
//        {
//      SetMotorSpeed(LMotor,25);
//		  SetMotorSpeed(RMotor,15);
//        }
//      else if(GyroYawAngleGet() - TurnAngle > (float)2)
//        {
//      SetMotorSpeed(LMotor,25);
//		  SetMotorSpeed(RMotor,15);
//        }
//    }

//      SetMotorSpeed(LMotor,0);
//		  SetMotorSpeed(RMotor,0);
}

//转向动作 （将机器人转至某一角度）
//void TurnPidInit()
//{
//	PIDInit(&Pid_Turn, 0.01, 0, 0);
//}


//void TurnAngle(double angle)
//{
//    double LSpeed = 0;
//    double RSpeed = 0;	
//    double currentAngle = GyroYawAngleGet();
//    if(currentAngle < 0)
//    {
//            currentAngle = 360 + currentAngle;//当前角以向前为0，向左增加度数
//    }
//    if((currentAngle>=0)&&(currentAngle<=180)&&(angle>=0)&&(angle<=180))
//    {
//        if((angle-currentAngle)>0)//左转 
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//        else //右转
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//    }
//    else if((currentAngle>=0)&&(currentAngle<=180)&&(angle>180)&&(angle<360))
//    {
//        if((angle-currentAngle)>180)//右转
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//        else //左转
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//    }
//     else if((currentAngle>180)&&(currentAngle<360)&&(angle>=0)&&(angle<=180))
//    {
//        if((angle-currentAngle)>180)//左转
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//        else //右转
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//    }
//    else if((currentAngle>180)&&(currentAngle<360)&&(angle>180)&&(angle<360))
//    {
//        if((angle-currentAngle)>0)//左转
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//        else //右转
//        {
//            LSpeed = TurnSpeed + GetPIDValue(&Pid_Turn, currentAngle); 
//            RSpeed = TurnSpeed - GetPIDValue(&Pid_Turn, currentAngle);
//            SetMotorSpeed(LMotor, LSpeed);
//      	    SetMotorSpeed(RMotor, RSpeed);
//        }
//    }
//		printf("currentangle=%lf\r\n",currentAngle);
//		printf("LSpeed=%lf\r\n",LSpeed);
//		printf("RSpeed=%lf\r\n",RSpeed);
//}








