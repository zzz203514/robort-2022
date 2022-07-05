/**
  ******************************************************************************
  * @file    UserFSM.c
  * @author  ׯ�ı�
  * @brief   ��״̬��
  *
  @verbatim
	��
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "UserFSM.h"

/* Define\Declare ------------------------------------------------------------*/
FSM_t OneToTwo,TwoToThree,TwoToFour,ThreeToFive,ThreeToSix,FourToFive,FourToSix,FiveToSeven,SixToSeven,FiveToEight,SixToEight;         //һ̨����̨


FSM_t *MyFSMs[] = 
{
	&OneToTwo,&TwoToThree,&TwoToFour,&ThreeToFive,&ThreeToSix,
	&FourToFive,&FourToSix,&FiveToSeven,&SixToSeven,&FiveToEight,&SixToEight
};



FSMTable_t OneToTwoTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬
    {     GoToBlock,               NormalLineSpeedPatrol,            JudgeUp,                 UpBlock         },
    {     UpBlock,                 LowSpeedLinePatrol,               JudgeNormal,             OnBlock         },
    {     OnBlock,                 GoBrige,                          JudgeDown,               DownBlock       },
		{     DownBlock,               LowSpeedLinePatrol,               JudgeNormal,             OnGround        },
		{     OnGround,                NormalLineSpeedPatrol,            JudgeUp,                 UpStage         },
		{     UpStage,                 LowSpeedLinePatrol,               JudgeNormal,             OnStage         }
};
FSMTable_t TwoToThreeTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,								  UpBlock			  	},
		{			UpBlock,							 	 LowSpeedLinePatrol,							JudgeDown,								DownBlock		  	},
		{			DownBlock,             	 LowSpeedLinePatrol,							JudgeNormal,							OnGround		    },
		{			OnGround,								 NormalLineSpeedPatrol,						JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage				  }
};
FSMTable_t TwoToFourTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,								  UpBlock			  	},
		{			UpBlock,								 LowSpeedLinePatrol,							JudgeDown,								DownBlock		    },
		{			DownBlock,               LowSpeedLinePatrol,							JudgeNormal,							OnGround				},
		{			OnGround,								 NormalLineSpeedPatrol,						JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage					}
}; 
//�ҵ�һ������֮�󷵻�
FSMTable_t	ThreeToFiveTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,									OnBlock					},
		{			OnBlock,								 GoBrige,													JudgeDown,								OnGround				},
		{			OnGround,								 NormalLineSpeedPatrol,  					JudgeUp,									UpBlock					},
		{			UpBlock,								 LowSpeedLinePatrol,							JudgeDown,								DownBlock				},
		{			DownBlock,               LowSpeedLinePatrol,							JudgeNormal,							OnGround				},
		{			OnGround,								 NormalLineSpeedPatrol,						JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage					}
};
//������Ҫͣ������
FSMTable_t	ThreeToSixTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,									OnBlock					},
		{			OnBlock,								 GoBrige,													JudgeDown,								OnCricle				},
		{			OnCricle,								 CirclePatrol,										JudgeUp,									UpBlock					},
		{			UpBlock,								 LowSpeedLinePatrol,							JudgeDown,								OnCricle				},
		{			OnCricle,                CirclePatrol,										JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage					}
};
FSMTable_t	FourToFiveTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬
	
};
FSMTable_t	FourToSixTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬

};
FSMTable_t FiveToSevenTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬

};
FSMTable_t FiveToEightTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬

};
FSMTable_t SixToSevenTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬

};
FSMTable_t SixToEightTable[] =
{
 //       ��ǰ��״̬               ��ǰ״ִ̬�к���                  ��ת�¼���������          ��һ��״̬

};
//״̬����ʼ״̬���ü���ʼ��
void MyFSMInit()
{
	CurrentFSM = &OneToTwo;              //��ǰִ�е�״̬��(��ʽʹ��ʱ�뼰ʱ����)
	
//         ״̬����             ״̬����ʼ״̬             ��Ӧ״̬��                 ״̬����С
	  FSMInit(&OneToTwo,   			   GoToBlock,        	    OneToTwoTable,                  6     );

}

//״̬������
void MyFSMRun(FSM_t *fsm)
{
	uint8_t curState = fsm->CurState; 
	FSMTable_t *fsmTable = fsm->FsmTable;
	void (*eventAction)(void) = fsmTable[curState].EventAction;
	uint8_t (*eventJumpCondition)(void) = fsmTable[curState].EventJumpCondition;
	uint8_t size = fsm->Size;
}

//�жϺ���
uint8_t JudgeUp()    //�ж�����
{
	if(UpORDown()==1)
		return 1;
	else
		return 0;
}

uint8_t JudgeDown()		//�ж��½�
{
	if(UpORDown()==0)
		return 1;
	else
		return 0;
}

uint8_t JudgeNormal()  //�ж�ƽ��ģʽ
{
	if(UpORDown()==2)
		return 1;
	else 
		return 0;
}






