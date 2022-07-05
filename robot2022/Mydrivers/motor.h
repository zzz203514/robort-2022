#ifndef __MOTORDRIVE_H
#define __MOTORDRIVE_H
#define PWM_MAX 32

#include "tim.h"
#include "gpio.h"

typedef enum
{
  LMotor,
  RMotor,
}MotorHandle;

void MotorInit(void);
void SetMotorSpeed(MotorHandle Motor, float PWNDuty);

#endif
