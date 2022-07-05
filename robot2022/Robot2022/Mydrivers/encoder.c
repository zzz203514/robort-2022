/** See a brief introduction (right-hand button) */
#include "encoder.h"
/* Private include -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int16_t _LeftEncoderFeedback  = 0;
int16_t _RightEncoderFeedback = 0;

//路程统计相关变量
uint8_t _Encoder_CountControl = 0;
float _Encoder_DistantCount = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initialization of Timer-Input Capture
  * @param  None
  * @retval None
  */
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);       //右轮的编码器
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);       //左轮的编码器
	
}
//轮子直径72mm 预计上场由于受压的关系会变小一些 这里采用70mm


/*
** 函数名称：Encoder_GetLWheelSpeed()
** 函数作用：获取左边轮子在最近一个100ms内统计到的速度
** 函数输入：无
** 函数输出：轮子转速 以m/s为单位 例如0.5m/s

** 注意事项：轮子的速度是100ms更新一次的
** 注意事项：因此100ms内的重复调用会得到相同的结果 没有意义
*/
float Encoder_GetLWheelSpeed(void)
{
    float Speed = 0;
		_LeftEncoderFeedback = __HAL_TIM_GET_COUNTER(&htim2);
    Speed = (float)(_LeftEncoderFeedback) / (float)8.0;
    Speed *= 10;
    Speed /= 80;

    Speed *= (float)0.2199; //圈转速 * 每圈转的距离 = 米每秒

#ifdef Robot_1
    return Speed;
#endif

#ifdef Robot_2
    return Speed;
#endif

#ifdef Robot_3

#endif


}


/*
** 函数名称：Encoder_GetRWheelSpeed()
** 函数作用：获取右边轮子在最近一个100ms内统计到的速度
** 函数输入：无
** 函数输出：轮子转速 以m/s为单位 例如0.5m/s

** 注意事项：轮子的速度是100ms更新一次的
** 注意事项：因此100ms内的重复调用会得到相同的结果 没有意义
*/
float Encoder_GetRWheelSpeed(void)
{
    float Speed = 0;
		_RightEncoderFeedback=__HAL_TIM_GET_COUNTER(&htim4);
    Speed = (float)(_RightEncoderFeedback) / (float)8.0;
    Speed *= 10;
    Speed /= 80;

    Speed *= (float)0.2199; //圈转速 * 每圈转的距离 = 米每秒

#ifdef Robot_1
    return - Speed;
#endif

#ifdef Robot_2
    return Speed;
#endif

#ifdef Robot_3

#endif

}


/*
** 函数名称：Encoder_ResetDistant()
** 函数作用：重置积分来的距离
** 函数输入：无
** 函数输出：无

** 函数说明：该函数不会停止路程积分 该函数仅仅是清空路程积分的结果
** 函数说明：想停止路程积分应该调用下面那个Stop函数
*/
void Encoder_ResetDistant(void)
{
    _Encoder_DistantCount = 0;
}



/*
** 函数名称：Encoder_StartDistantCount()
** 函数作用：从下一个最近的100ms开始进行路程积分
** 函数输入：无
** 函数输出：无

** 函数说明：统计的距离是两轮的平均路程
*/
void Encoder_StartDistantCount(void)
{
    _Encoder_CountControl = 1;
}

/*
** 函数名称：Encoder_StopDistantCount()
** 函数作用：立即停止路程积分 但不会清空已经行走的路程
** 函数输入：无
** 函数输出：无

** 函数说明：统计的距离是两轮的平均路程
*/
void Encoder_StopDistantCount(void)
{
    _Encoder_CountControl = 0;
}


/*
** 函数名称：Encoder_GetCurrentDistantCount()
** 函数作用：获取当前已经行走过的路程 100ms刷新一次
** 函数输入：无
** 函数输出：float类型数据 单位是米

** 函数说明：统计的路程是两轮的平均路程 而不是左边或者右边的
** 函数说明：因此寻线的摆动会影响路程计算 使得最终位移小于路程
*/
float Encoder_GetCurrentDistantCount(void)
{
    return _Encoder_DistantCount;
}
void BeginCount(void)
{
    Encoder_ResetDistant();
    Encoder_StartDistantCount();
}
void StopCount(void)
{
    Encoder_StopDistantCount();
}
