#ifndef LINEPATROLACTION_H_
#define LINEPATROLACTION_H_


#include <math.h>
#include <stdio.h>
#include "PID.h"
#include "GraySensor.h"
#include "motor.h"
#include "Gyro.h"
#include "Miscellaneous.h"

double GraySensorBiasGet(void);
void NormalLineSpeedPatrol(void);
void LinePIDInit(void);
void LowSpeedLinePatrol(void);
double YawangleerroGet();
void GoBrige(void);
void CirclePatrol(void);

#endif