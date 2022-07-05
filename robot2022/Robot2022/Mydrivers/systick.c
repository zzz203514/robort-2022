/** See a brief introduction (right-hand button) */
#include "systick.h"
/* Private include -----------------------------------------------------------*/
#include "stm32f4xx.h"
#include "magic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile uint32_t _timingDelay;
static volatile uint32_t _GoLineTime;
static volatile uint32_t _CTime = 10;
/* Public variables ---------------------------------------------------------*/
uint8_t _UpdateTick = 0;

/* Private function prototypes -----------------------------------------------*/
/*static*/ inline void _DelayOneMs_Interrupt(void);
void _StateMachineTick_Interrupt(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Choice source of the SysTick clock.
  * @param  None
  * @retval None
  */
void SysTick_Init(void)
{
    /* SystemCoreClock = 1s -> 1s / 1000 = 1ms */
    SysTick_Config(SystemCoreClock / 1000);
    NVIC_SetPriority(SysTick_IRQn, 0x0);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void SysTickDelay(uint32_t nTime)
{
    _timingDelay = nTime;

    while (_timingDelay != 0)
        ;
}

/**
  * @brief  Decrements the TimingDelay variable. (F12) SysTick_Handler();
  * @param  None
  * @retval None
  */
void _DelayOneMs_Interrupt(void)
{
    if (_timingDelay != 0)
    {
        _timingDelay--;
    }
}

void _StateMachineTick_Interrupt(void)
{
    static uint16_t counter = 0;

    counter++;

    if (counter > (State_MachineTickTime - 1))
    {
        counter = 0;
        _UpdateTick = 1;
    }
}
void _GoLineDelay_Interrupt(void)
{
    if (_GoLineTime != 0)
    {
        _GoLineTime--;
    }
}
void _GoLineDelay(uint16_t MsTime)
{
    _GoLineTime = MsTime;
    while (_GoLineTime != 0)
    {
        _GoLineMSpeed();
        //_FindPointGo();
    };
    if (_GoLineTime == 0)
    {
        //UpdateMotorState(MOTOR_STOP);
    }
}

/*
** �������ƣ�_UpdateEncoderFeedback()
** �������ã����� ��ʻ·�̷�������
** �������룺��
** �����������

** ע������˺�����Ӧ��������� ��Ӧ����systick���жϷ���������
** ע������ú���ʵ����100ms��ƽ���ٶȵļ��� �Լ�����ļ���

** ƽ���ٶȼ��㣺��������ǰת ��CNTÿһ������ +4 �������� -4 �ñ�����int���͵�
** Ȼ�����ǵĵ��ÿȦ����4������(����ֵ ��һ��׼ ���ǽ���ǶԵ�) ���CNT / 4�����ľ�����ʵ
** �������� Ȼ���ü������� / 4 / 80(������ٱ�)����100ms������ת���ĽǶ� ���*10 �õ�R/s

** ����Ļ��ּ��㣺���������Ѿ��ܻ�ȡ����ٶ� �����+�ұ��ٶ�/2�ɵ�ƽ���ٶ�
** ���� = �ٶ� * ʱ�� ����R/s֪��  R/s * 0.1 =������100ms��ת�˶���Ȧ Ȼ���� * ÿȦ���ӳ���
** �õ���һ��100ms�������˶�Զ �����+=���ۼ�������ܰɾ�����ֳ���
*/
void _UpdateEncoderFeedback(void)
{
    static uint8_t counter = 0;

    if (counter < 99)
    {
        counter++;
    }
    else
    {
        _LeftEncoderFeedback = TIM2->CNT;
        _RightEncoderFeedback = TIM5->CNT;

        //����ͳ��
        if (_Encoder_CountControl == 1)
        {
            _Encoder_DistantCount += ((Encoder_GetLWheelSpeed() + Encoder_GetRWheelSpeed()) / (float)2.0) * (float)0.1;
        }

        TIM2->CNT = 0;
        TIM5->CNT = 0;
        counter = 0;
    }
}

/*
** �������ƣ�_Laser_AntiJitterFeedback()
** �������ã��������߼��⴫������������ ������������
** �������룺��
** �����������

** ע��������ڲ����˸������� ���Ըú�����Ȳ����������Ƶ�״̬��ȡ������һЩ �����5ms
** ע������㲻Ӧ�õ��øú��� �ú���Ӧ��systick�жϷ��������Լ�ִ��

** �㷨ʵ�֣��ֱ�� �� �Ҽ��⴫�������Ŷ�10�� ���������5�ε͵�ƽ��Ϊ�ڰ����� ��������̺��
** �������systick���жϷ��������� 1ms���һ��
*/
void _Laser_AntiJitterFeedback(void)
{
    //����int����ȷ����ʹ������Ҳ�лָ��Ŀ���
	static int8_t LeftCountTimes = 0;
	static int8_t RightCountTimes = 0;

    //���������ߵ͵�ƽ(������)
    if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_13) == 0)
    {
        //С��10������һ�������ϵļ��� �������Ӹ�ֵ
        if (LeftCountTimes < 10)
        {
            LeftCountTimes++;
        }
    }
    else //���ǵ;��Ǹ� ��߶����ߵ�ƽ(��̺����)
    {
        if (LeftCountTimes > 0)
        {
            //����0������һ�β�������(���߽���������)�ļ��� ������0�Ͳ�����
            LeftCountTimes--;
        }
    }

    //��������ұߵ͵�ƽ(������)
    if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11) == 0)
    {
        //С��10������һ�������ϵļ��� �������Ӹ�ֵ
        if (RightCountTimes < 10)
        {
            RightCountTimes++;
        }
    }
    else //���ǵ;��Ǹ� �ұ߶����ߵ�ƽ(��̺����)
    {
        if (RightCountTimes > 0)
        {
            //����0������һ�β�������(���߽���������)�ļ��� ������0�Ͳ�����
            RightCountTimes--;
        }
    }

    /* ��ɲ��� ��ʼ�����������������ϻ��ǲ������� */

    //���
    //ͳ�Ƶ� > 4��������(Ҳ����5��) ��Ϊ��ȴ������
    if (LeftCountTimes > 4)
    {
        //������LED�� LOW
        _LLaserAntiJitterState = LOW;
    }
    else
    {
        //�������� HIGH
        _LLaserAntiJitterState = HIGH;
    }

    //�ұ�
    //ͳ�Ƶ� > 4��������(Ҳ����5��) ��Ϊ��ȴ������
    if (RightCountTimes > 4)
    {
        //������LED�� LOW
        _RLaserAntiJitterState = LOW;
    }
    else
    {
        //��������LED�� HIGH
        _RLaserAntiJitterState = HIGH;
    }
}

//void _FindPointL()
//{
//	if(_CTime==0)
//	{
//		_CTime=10;
//		ClearLLaserChangePendingBit();
//		if(GetLeftLaserState()==Changed)
//		{
//			UpdateMotorState(MOTOR_STOP);
//		}
//	}
//}
//void _FindPointR()
//{
//	if(_CTime==0)
//	{
//		_CTime=10;
//		ClearRLaserChangePendingBit();
//		if(GetRightLaserState()==Changed)
//		{
//			UpdateMotorState(MOTOR_STOP);
//		}
//	}
//}
//void _FindPoint_Interrupt()
//{
//	while(_CTime!=0)
//	{
//		_CTime--;
//	}
//
//}
