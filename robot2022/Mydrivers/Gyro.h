#ifndef GYRO_H_
#define GYRO_H_

#include "usart.h"
#include "stdio.h"

#define GYRO_UART8_TX_GPIO_PORT  GPIOE      
#define GYRO_UART8_TX_GPIO_PIN   GPIO_PIN_1
#define GYRO_UART8_RX_GPIO_PORT  GPIOE 
#define GYRO_UART8_RX_GPIO_PIN   GPIO_PIN_0

#define GyroUartHandle huart5

typedef struct 
{
	double RollAngle;   //??????
	
	double PitchAngle;  //??????
	
	double YawAngle;    //ƫ????
	
}Gyro_AngleTypeDef;

void GyroInit(void);
double GyroRollAngleGet(void);
double GyroPitchAngleGet(void);
double GyroYawAngleGet(void);
uint8_t GyroOneOfElevenReceiveBufferGet(uint8_t num);

void Short2Char(short sData, uint8_t cData[]);
short Char2Short(uint8_t cData[]);
uint8_t GyroCheckSumJudge(void);
double GyroEulerAnglesProcess(uint8_t cData[]);
void GyroGetAllAngles(void);
void AngleGet(void);

#endif
