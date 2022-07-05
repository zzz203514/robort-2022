/** See a brief introduction (right-hand button) */
#include "encoder.h"
/* Private include -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int16_t _LeftEncoderFeedback  = 0;
int16_t _RightEncoderFeedback = 0;

//·��ͳ����ر���
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
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);       //���ֵı�����
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);       //���ֵı�����
	
}
//����ֱ��72mm Ԥ���ϳ�������ѹ�Ĺ�ϵ���СһЩ �������70mm


/*
** �������ƣ�Encoder_GetLWheelSpeed()
** �������ã���ȡ������������һ��100ms��ͳ�Ƶ����ٶ�
** �������룺��
** �������������ת�� ��m/sΪ��λ ����0.5m/s

** ע��������ӵ��ٶ���100ms����һ�ε�
** ע��������100ms�ڵ��ظ����û�õ���ͬ�Ľ�� û������
*/
float Encoder_GetLWheelSpeed(void)
{
    float Speed = 0;
		_LeftEncoderFeedback = __HAL_TIM_GET_COUNTER(&htim2);
    Speed = (float)(_LeftEncoderFeedback) / (float)8.0;
    Speed *= 10;
    Speed /= 80;

    Speed *= (float)0.2199; //Ȧת�� * ÿȦת�ľ��� = ��ÿ��

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
** �������ƣ�Encoder_GetRWheelSpeed()
** �������ã���ȡ�ұ����������һ��100ms��ͳ�Ƶ����ٶ�
** �������룺��
** �������������ת�� ��m/sΪ��λ ����0.5m/s

** ע��������ӵ��ٶ���100ms����һ�ε�
** ע��������100ms�ڵ��ظ����û�õ���ͬ�Ľ�� û������
*/
float Encoder_GetRWheelSpeed(void)
{
    float Speed = 0;
		_RightEncoderFeedback=__HAL_TIM_GET_COUNTER(&htim4);
    Speed = (float)(_RightEncoderFeedback) / (float)8.0;
    Speed *= 10;
    Speed /= 80;

    Speed *= (float)0.2199; //Ȧת�� * ÿȦת�ľ��� = ��ÿ��

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
** �������ƣ�Encoder_ResetDistant()
** �������ã����û������ľ���
** �������룺��
** �����������

** ����˵�����ú�������ֹͣ·�̻��� �ú������������·�̻��ֵĽ��
** ����˵������ֹͣ·�̻���Ӧ�õ��������Ǹ�Stop����
*/
void Encoder_ResetDistant(void)
{
    _Encoder_DistantCount = 0;
}



/*
** �������ƣ�Encoder_StartDistantCount()
** �������ã�����һ�������100ms��ʼ����·�̻���
** �������룺��
** �����������

** ����˵����ͳ�Ƶľ��������ֵ�ƽ��·��
*/
void Encoder_StartDistantCount(void)
{
    _Encoder_CountControl = 1;
}

/*
** �������ƣ�Encoder_StopDistantCount()
** �������ã�����ֹͣ·�̻��� ����������Ѿ����ߵ�·��
** �������룺��
** �����������

** ����˵����ͳ�Ƶľ��������ֵ�ƽ��·��
*/
void Encoder_StopDistantCount(void)
{
    _Encoder_CountControl = 0;
}


/*
** �������ƣ�Encoder_GetCurrentDistantCount()
** �������ã���ȡ��ǰ�Ѿ����߹���·�� 100msˢ��һ��
** �������룺��
** ���������float�������� ��λ����

** ����˵����ͳ�Ƶ�·�������ֵ�ƽ��·�� ��������߻����ұߵ�
** ����˵�������Ѱ�ߵİڶ���Ӱ��·�̼��� ʹ������λ��С��·��
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
