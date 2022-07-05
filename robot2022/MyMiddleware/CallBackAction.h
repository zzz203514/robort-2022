#ifndef CALLBACKACTION_H_
#define CALLBACKACTION_H_

#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "motor.h"
#include "Miscellaneous.h"
#include "Gyro.h"
#include "GraySensor.h"
#include "DiffuseReflectionLaser.h"
#include "Judgement.h"
#include  "K210.h"
//#include "RangingLaser.h"
//#include "MatrixKeyBoard.h"
//#include "FSM.h"
//#include "UserFSM.h"

//״̬����ز���
//extern FSM_t CarFSM;
//extern FSMTable_t CarTable[];

//��������ز���
extern uint8_t GyroReceiveNum;
extern uint8_t GyroReceiveBuffer[11];

//�Ҷȴ�������ز���
extern uint8_t GraySensorReceiveBuffer[18];
extern uint8_t GraySensorTransferFlag, GraySensorRecieveFlag;

////�����伤�⴫������ز���
//extern DiffuseReflectionLaser_Change_State Left_DFLaser_Change_State;
//extern DiffuseReflectionLaser_Change_State Right_DFLaser_Change_State;

////���������ز���
//extern uint8_t KeyState;

//K210��ز���
extern uint8_t usart2_rxbuff[5];
extern uint8_t uart8_rxbuff[5];
extern uint8_t lo1,lo2,lo3,QR,TrueOne,block; //���Ƚ��г�ʼ��,��ʼ����Ϊ0
#endif