#ifndef USERMAIN_H_
#define USERMAIN_H_

#include "Miscellaneous.h"
#include "CallBackAction.h"
#include "LinePatrolAction.h"
#include "Gyro.h"
#include "GraySensor.h"
#include "DiffuseReflectionLaser.h"
#include "FSM.h"
#include "UserFSM.h"
#include "PID.h"
#include "TurnAroundAction.h"
#include "motor.h"
#include "ServoMotor.h"
#include "K210.h"

//extern FSM_t CarFSM;
//extern FSMTable_t CarTable[];


void UserInit(void);
void UserLoop(void);

#endif