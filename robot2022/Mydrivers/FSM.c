/**
  ******************************************************************************
  * @file    FSM.c
  * @author  俞立,邹睿
  * @brief   状态机
  *
  @verbatim
	无
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "FSM.h"


/* Define\Declare ------------------------------------------------------------*/
FSM_t *CurrentFSM;  //当前正在执行的状态机指针
uint8_t CurrentFSMNum;
//FSM_t *MyFSMs[] = {
////	&ReadyToGo,
////	&FUCK,
////	&GoToRoom1,
////	&GoToRoom2,
////	&GoOtherRooms,
////	&GoToRoom3,
////	&GoToRoom4,
////	&GoToThirdCross,
////	&GoToLeftFourthCross,
////	&GoToRightFourthCros,
//};
/**
 ******************************************************************************
 *  @defgroup 外部调用
 *  @brief
 *
**/
//状态机初始化
void FSMInit(FSM_t *fsm, uint8_t state, FSMTable_t *fsmtable ,uint8_t SizeofFSM)
{
	fsm->CurState = state;
  fsm->FsmTable = fsmtable;
//	fsm->Size = sizeof(*fsmtable) / sizeof(FSMTable_t);     //不知为何不能得出正确值
	fsm->Size = SizeofFSM;              //手动输入大小（可优化为自主计算）
}
	
//状态机运行（自动条件跳转）
void FSMRun(FSM_t *fsm)
{
	uint8_t curState = fsm->CurState;                             //状态机当前状态
	FSMTable_t *fsmTable = fsm->FsmTable;                         //状态机状态表
	void (*eventAction)(void) = fsmTable[curState].EventAction;   //状态机当前状态执行函数
	uint8_t (*eventJumpCondition)(void) = fsmTable[curState].EventJumpCondition;  //状态机跳转事件条件函数
	uint8_t size = fsm->Size;                                     //状态表状态数
	
	if(eventJumpCondition())                                      //符合条件就跳转至下一状态
	{
		fsm->CurState = fsmTable[curState].NextState;
		eventAction = fsmTable[fsm->CurState].EventAction;

		if(curState == size-1){                                     //符合条件就跳转至下一状态机
			CurrentFSMNum++;
			CurrentFSM = MyFSMs[CurrentFSMNum];                       
			return;
		}
	}
	eventAction();
}

//状态机间跳转  返回1或0
uint8_t FSMTransfer(FSM_t *fsmA, FSM_t *fsmB, EventJumpCondition_t eventJumpCondition)
{
	uint8_t curStateA = fsmA->CurState;
	uint8_t curStateB = fsmB->CurState;
	uint8_t sizeA = fsmA->Size;
	
	if(curStateA == sizeA-1 && eventJumpCondition())
		return 1;
	else
		return 0;
}

//状态机当前状态获取
uint8_t FSMStateGet(FSM_t *fsm)
{
	return fsm->CurState;
}

