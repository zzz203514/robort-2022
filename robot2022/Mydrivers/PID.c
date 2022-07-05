/**
  ******************************************************************************
  * @file    PID.c
  * @author  ׯ�ı�
  * @brief   PID����
  * 
	@verbatim
	
	@endverbatim
  * @{
**/


/* Includes ------------------------------------------------------------------*/
#include "PID.h"

void PIDInit(Pid_TypeDef *PID, double Kp, double Ki, double Kd)
{
	PID->Kp = Kp;
	PID->Ki = Ki;
	PID->Kd = Kd;
  
  PID->previousError = 0;
}

double GetPIDValue(Pid_TypeDef *PID, double error)
{	
	double P = 0.0, I=0.0 , D=0.0;
  double outPut = 0;
  
  P = error;
  I = I + error;
  D = error - PID->previousError;
  
  outPut = (PID->Kp * P) + (PID->Ki * I) + (PID->Kd * D);
  PID->previousError = error;
  
  return outPut;
}
