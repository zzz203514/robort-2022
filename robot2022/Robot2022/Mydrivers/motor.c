/** See a brief introduction (right-hand button) */
#include "motor.h"
/* Private include -----------------------------------------------------------*/
#include "stm32h7xx.h"
#include "systick.h"
#include "tim.h"
#include "gpio.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int32_t _motorSpeed[2] = {0/*Left*/, 0/*Right*/};
const static int32_t _autoReload =42000 - 1;
static MotorMode_t _motorMode = MOTOR_STOP;
static int _motorUpgradeTag = 0;

/* Timer use - Test use */
//static uint32_t _timeTick = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Motor initialization
  * @param  None
  * @retval None
  */
void MotorPWM_Init(void)
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1); 
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2); 
}

/**
  * @brief
  * @param  None
  * @retval None
  */
int SetMotorDutyRatio(double leftDutyRatio, double rightDutyRatio)
{
    if(rightDutyRatio > 1 || leftDutyRatio > 1 ||
            leftDutyRatio < -1 || rightDutyRatio < -1) {
        return _motorMode;
    }

    return SetMotorPulse((int32_t)(leftDutyRatio * _autoReload),
                         (int32_t)(rightDutyRatio * _autoReload));
}

/**
  * @brief
  * @param  None
  * @retval None
  */
int SetMotorPulse(int32_t leftPulse, int32_t rightPulse)
{
    if(rightPulse >  _autoReload) rightPulse = _autoReload;
    else if (rightPulse <  0) rightPulse = 0;

    if(leftPulse >  _autoReload) leftPulse = _autoReload;
    else if (leftPulse <  0) leftPulse = 0;

    _motorSpeed[1] = rightPulse;
    _motorSpeed[0] =  leftPulse;
		
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (uint32_t)(_motorSpeed[1]));
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, (uint32_t)(_motorSpeed[0]));
	
    return _motorUpgradeTag;
}

/**
  * @brief
  * @param  None
  * @retval None
  */
void SetMotorState(MotorMode_t motorMode)
{
    if(_motorMode != motorMode)
    {
        _motorMode = motorMode;
        _motorUpgradeTag = 1;
    }
}

/**
  * @brief
  * @param  None
  * @retval None
  */

MotorMode_t UpgradeMotorState(void)
{
    if (_motorUpgradeTag != 0)
    {
        _motorUpgradeTag = 0;
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2 | GPIO_PIN_3,0);               
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9 | GPIO_PIN_11,0);
			
        SysTickDelay(100);

        switch (_motorMode) {
        case MOTOR_STOP:
            break;
        case MOTOR_FRONT: {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,1);
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,1);
        }
        break;
        case MOTOR_TURN_LEFT: {
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11 | GPIO_PIN_9,1);
        }
        break;
        case MOTOR_TURN_RIGHT: {
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3 | GPIO_PIN_2,1);
        }
        break;
        case MOTOR_BACK: {
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9 | GPIO_PIN_11,1);
        }
        break;
        default:
            break;
        }
    }

    return _motorMode;
}

/**
  * @brief
  * @param  None
  * @retval None
  */
MotorMode_t UpdateMotorState(MotorMode_t motorMode)
{
    if(motorMode != _motorMode ) {
        _motorUpgradeTag = 0;
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2 | GPIO_PIN_3,0);               
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9 | GPIO_PIN_11,0);
        //SysTickDelay(100);

        switch (motorMode) {
        case MOTOR_STOP:
            break;
        case MOTOR_FRONT: {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,1);
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,1);
        }
        break;
        case MOTOR_TURN_LEFT: {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11 | GPIO_PIN_9,1);
        }
        break;
        case MOTOR_TURN_RIGHT: {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3 | GPIO_PIN_2,1);
        }
        break;
        case MOTOR_BACK: {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9 | GPIO_PIN_11,1);
        }
        break;
        default:
            break;
        }

        _motorMode = motorMode;
    }

    return _motorMode;
}

/**
  * @brief  GetSpeed  '0' is Left
                      '1' is Right
  * @param  None
  * @retval None
  */
//int32_t GetMotorSpeed(int8_t leftOrRight)
//{
//  return _motorSpeed[leftOrRight & 0x01];
//}

/* Test functions ------------------------------------------------------------*/
/**
  * @brief
  * @param  None
  * @retval None
  */
//void SetMotorForwardTime(uint32_t sec)
//{
//  _timeTick = sec;
//  UpdateMotorState(MOTOR_FRONT);
//}

/**
  * @brief  Reference Only -> (F12) SysTick_Handler();
  * @param  None
  * @retval None
  */
//void _forwardTime_Interrupt()
//{
//  ;    if(_timeTick >  1)
//  {
//    _timeTick--;
//  }
//  else if(_timeTick == 1)
//  {
//    _timeTick--;
//    if(_motorMode != MOTOR_STOP){
//      _motorUpgradeTag = 1;
//      _motorMode = MOTOR_STOP;
//    }
//  }
//}



/* Add in 2019.3.4 18.14 By WLYS */

/* 4.14 由于编码器部分的重构 此函数暂停使用 */

/* 函数名称：SetWheelSpeed() */
/* 函数作用：根据编码器反馈调节两侧轮子的速度                                      */
/* 函数输入：两侧轮子的速度百分比 以float格式 (左边百分比，右边百分比)             */
/* 函数输出：void                                                                  */
/* 调节范围：0 ~ 4r/s 对应 0% ~ 100%                                               */
/* 输入样例： SetWheelSpeed(0.50,0.50);  此举将设置两侧轮速为2.0r/s                */

/* 注意事项：此函数必须在状态机中不停轮询才有用 如状态机中该函数停止轮询           */
/* 					 则电机会保持最后一次调用该函数时的状态                                */

/* 使用建议：由于采用的获取编码器反馈函数是以阻塞模式运行的如速度过慢获取编码器反馈*/
/*           将花费相当长的时间(大于500ms) 在低速时本函数的效能会降低 具体表现为   */
/*           调节速度变慢 反馈时间延长 命令响应速度降低 无法在规定时间内轮询状态机 */

/* 建议速度：调节速度建议在 1.5r/s 以上(假设20ms进行一次轮询) */

//void SetWheelSpeed(float LTarGetSpeed, float RTarGetSpeed)
//{
//	float LRealSpeed;
//	float RRealSpeed;
//	static float LPWM = 0.00;
//	static float RPWM = 0.00;
//
//	LTarGetSpeed *= (float)4;
//	RTarGetSpeed *= (float)4;
//
//	LRealSpeed = GetLRSpeed(1);
//	RRealSpeed = GetRFSpeed(1);
//
//	//Left MOTOR
//	if(((LTarGetSpeed - LRealSpeed)) > (float)0.0) // RealSpeed lower than TargetSpeed, need to speed up.
//	{
//
//		if(((LTarGetSpeed - LRealSpeed)) > (float)0.5)
//		{
//			LPWM += (float)0.035;
//		}
//
//		if(((LTarGetSpeed - LRealSpeed)) > (float)0.4)
//		{
//			LPWM += (float)0.015;
//		}

//		if(((LTarGetSpeed - LRealSpeed)) > (float)0.3)
//		{
//			LPWM += (float)0.01;
//		}

//		if(((LTarGetSpeed - LRealSpeed)) > (float)0.2)
//		{
//			LPWM += (float)0.005;
//		}

//		if(((LTarGetSpeed - LRealSpeed)) > (float)0.1)
//		{
//			LPWM += (float)0.001;
//		}
//
//
//		if(LPWM > (float)0.5)
//		{
//			LPWM = (float)0.5;
//		}
//		SetMotorDutyRatio((double)LPWM,(double)RPWM);
//
//
//	}
//	else // RealSpeed higher than TargetSpeed, nedd to slow down.
//	{
//
//		if((LRealSpeed - LTarGetSpeed) > (float)0.5)
//		{
//			LPWM -= (float)0.035;
//		}

//		if((LRealSpeed - LTarGetSpeed) > (float)0.4)
//		{
//			LPWM -= (float)0.015;
//		}

//		if((LRealSpeed - LTarGetSpeed) > (float)0.3)
//		{
//			LPWM -= (float)0.01;
//		}

//		if((LRealSpeed - LTarGetSpeed) > (float)0.2)
//		{
//			LPWM -= (float)0.005;
//		}

//		if((LRealSpeed - LTarGetSpeed) > (float)0.1)
//		{
//			LPWM -= (float)0.001;
//		}

//
//		if(LPWM < (float)0.0)
//		{
//			LPWM = (float)0.0;
//		}
//		SetMotorDutyRatio((double)LPWM,(double)RPWM);
//
//	}

//
//
//
//
//	//Right MOTOR
//	if(((RTarGetSpeed - RRealSpeed)) > (float)0.0) // RealSpeed lower than TargetSpeed, need to speed up.
//	{
//
//		if(((RTarGetSpeed - RRealSpeed)) > (float)0.5)
//		{
//			RPWM += (float)0.035;
//		}
//
//		if(((RTarGetSpeed - RRealSpeed)) > (float)0.4)
//		{
//			RPWM += (float)0.015;
//		}

//		if(((RTarGetSpeed - RRealSpeed)) > (float)0.3)
//		{
//			RPWM += (float)0.01;
//		}

//		if(((RTarGetSpeed - RRealSpeed)) > (float)0.2)
//		{
//			RPWM += (float)0.005;
//		}

//		if(((RTarGetSpeed - RRealSpeed)) > (float)0.1)
//		{
//			RPWM += (float)0.001;
//		}


//		if(RPWM > (float)0.5)
//		{
//			RPWM = (float)0.5;
//		}
//		SetMotorDutyRatio((double)LPWM,(double)RPWM);
//
//	}
//	else // RealSpeed higher than TargetSpeed, nedd to slow down.
//	{
//
//		if((RRealSpeed - RTarGetSpeed) > (float)0.5)
//		{
//			RPWM -= (float)0.035;
//		}

//		if((RRealSpeed - RTarGetSpeed) > (float)0.4)
//		{
//			RPWM -= (float)0.015;
//		}

//		if((RRealSpeed - RTarGetSpeed) > (float)0.3)
//		{
//			RPWM -= (float)0.01;
//		}

//		if((RRealSpeed - RTarGetSpeed) > (float)0.2)
//		{
//			RPWM -= (float)0.005;
//		}

//		if((RRealSpeed - RTarGetSpeed) > (float)0.1)
//		{
//			RPWM -= (float)0.001;
//		}

//
//		if(RPWM < (float)0.0)
//		{
//			RPWM = (float)0.0;
//		}
//		SetMotorDutyRatio((double)LPWM,(double)RPWM);
//	}

//}

