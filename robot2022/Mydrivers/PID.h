#ifndef __PID_H
#define __PID_H



typedef struct 
{
	double Kp;                      //����ϵ��
	double Ki;                      //����ϵ��
	double Kd;                      //΢��ϵ��
  
  double previousError;
}Pid_TypeDef;

void PIDInit(Pid_TypeDef *PID, double Kp, double Ki, double Kd);
double GetPIDValue(Pid_TypeDef *PID, double error);

#endif