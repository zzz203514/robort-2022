/**
  ******************************************************************************
  * @file    UserFSM.c
  * @author  庄文标
  * @brief   主状态机
  *
  @verbatim
	无
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "UserFSM.h"

/* Define\Declare ------------------------------------------------------------*/
FSM_t OneToTwo,TwoToThree,TwoToFour,ThreeToFive,ThreeToSix,FourToFive,FourToSix,FiveToSeven,SixToSeven,FiveToEight,SixToEight;         //一台到二台


FSM_t *MyFSMs[] = 
{
	&OneToTwo,&TwoToThree,&TwoToFour,&ThreeToFive,&ThreeToSix,
	&FourToFive,&FourToSix,&FiveToSeven,&SixToSeven,&FiveToEight,&SixToEight
};



FSMTable_t OneToTwoTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态
    {     GoToBlock,               NormalLineSpeedPatrol,            JudgeUp,                 UpBlock         },
    {     UpBlock,                 LowSpeedLinePatrol,               JudgeNormal,             OnBlock         },
    {     OnBlock,                 GoBrige,                          JudgeDown,               DownBlock       },
		{     DownBlock,               LowSpeedLinePatrol,               JudgeNormal,             OnGround        },
		{     OnGround,                NormalLineSpeedPatrol,            JudgeUp,                 UpStage         },
		{     UpStage,                 LowSpeedLinePatrol,               JudgeNormal,             OnStage         }
};
FSMTable_t TwoToThreeTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,								  UpBlock			  	},
		{			UpBlock,							 	 LowSpeedLinePatrol,							JudgeDown,								DownBlock		  	},
		{			DownBlock,             	 LowSpeedLinePatrol,							JudgeNormal,							OnGround		    },
		{			OnGround,								 NormalLineSpeedPatrol,						JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage				  }
};
FSMTable_t TwoToFourTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,								  UpBlock			  	},
		{			UpBlock,								 LowSpeedLinePatrol,							JudgeDown,								DownBlock		    },
		{			DownBlock,               LowSpeedLinePatrol,							JudgeNormal,							OnGround				},
		{			OnGround,								 NormalLineSpeedPatrol,						JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage					}
}; 
//找到一个宝物之后返回
FSMTable_t	ThreeToFiveTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,									OnBlock					},
		{			OnBlock,								 GoBrige,													JudgeDown,								OnGround				},
		{			OnGround,								 NormalLineSpeedPatrol,  					JudgeUp,									UpBlock					},
		{			UpBlock,								 LowSpeedLinePatrol,							JudgeDown,								DownBlock				},
		{			DownBlock,               LowSpeedLinePatrol,							JudgeNormal,							OnGround				},
		{			OnGround,								 NormalLineSpeedPatrol,						JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage					}
};
//可能需要停留几秒
FSMTable_t	ThreeToSixTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态
		{			GoToBlock,							 NormalLineSpeedPatrol,						JudgeUp,									OnBlock					},
		{			OnBlock,								 GoBrige,													JudgeDown,								OnCricle				},
		{			OnCricle,								 CirclePatrol,										JudgeUp,									UpBlock					},
		{			UpBlock,								 LowSpeedLinePatrol,							JudgeDown,								OnCricle				},
		{			OnCricle,                CirclePatrol,										JudgeUp,									UpStage					},
		{			UpStage,								 LowSpeedLinePatrol,							JudgeNormal,							OnStage					}
};
FSMTable_t	FourToFiveTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态
	
};
FSMTable_t	FourToSixTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态

};
FSMTable_t FiveToSevenTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态

};
FSMTable_t FiveToEightTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态

};
FSMTable_t SixToSevenTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态

};
FSMTable_t SixToEightTable[] =
{
 //       当前的状态               当前状态执行函数                  跳转事件条件函数          下一个状态

};
//状态机初始状态配置及初始化
void MyFSMInit()
{
	CurrentFSM = &OneToTwo;              //当前执行的状态机(正式使用时请及时更改)
	
//         状态机名             状态机初始状态             对应状态表                 状态机大小
	  FSMInit(&OneToTwo,   			   GoToBlock,        	    OneToTwoTable,                  6     );

}

//状态机运行
void MyFSMRun(FSM_t *fsm)
{
	uint8_t curState = fsm->CurState; 
	FSMTable_t *fsmTable = fsm->FsmTable;
	void (*eventAction)(void) = fsmTable[curState].EventAction;
	uint8_t (*eventJumpCondition)(void) = fsmTable[curState].EventJumpCondition;
	uint8_t size = fsm->Size;
}

//判断函数
uint8_t JudgeUp()    //判断上升
{
	if(UpORDown()==1)
		return 1;
	else
		return 0;
}

uint8_t JudgeDown()		//判断下降
{
	if(UpORDown()==0)
		return 1;
	else
		return 0;
}

uint8_t JudgeNormal()  //判断平常模式
{
	if(UpORDown()==2)
		return 1;
	else 
		return 0;
}






