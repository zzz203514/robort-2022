#ifndef __PID_H
#define __PID_H



typedef struct 
{
	double Kp;                      //比例系数
	double Ki;                      //积分系数
	double Kd;                      //微分系数
  
  double previousError;
}Pid_TypeDef;

void PIDInit(Pid_TypeDef *PID, double Kp, double Ki, double Kd);
double GetPIDValue(Pid_TypeDef *PID, double error);

#endif