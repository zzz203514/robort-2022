/**
  ******************************************************************************
  * @file    FSM.c
  * @author  ����,���
  * @brief   ״̬��
  *
  @verbatim
	��
	@endverbatim
  * @{
**/

/* Includes ------------------------------------------------------------------*/
#include "FSM.h"


/* Define\Declare ------------------------------------------------------------*/
FSM_t *CurrentFSM;  //��ǰ����ִ�е�״̬��ָ��
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
 *  @defgroup �ⲿ����
 *  @brief
 *
**/
//״̬����ʼ��
void FSMInit(FSM_t *fsm, uint8_t state, FSMTable_t *fsmtable ,uint8_t SizeofFSM)
{
	fsm->CurState = state;
  fsm->FsmTable = fsmtable;
//	fsm->Size = sizeof(*fsmtable) / sizeof(FSMTable_t);     //��֪Ϊ�β��ܵó���ȷֵ
	fsm->Size = SizeofFSM;              //�ֶ������С�����Ż�Ϊ�������㣩
}
	
//״̬�����У��Զ�������ת��
void FSMRun(FSM_t *fsm)
{
	uint8_t curState = fsm->CurState;                             //״̬����ǰ״̬
	FSMTable_t *fsmTable = fsm->FsmTable;                         //״̬��״̬��
	void (*eventAction)(void) = fsmTable[curState].EventAction;   //״̬����ǰ״ִ̬�к���
	uint8_t (*eventJumpCondition)(void) = fsmTable[curState].EventJumpCondition;  //״̬����ת�¼���������
	uint8_t size = fsm->Size;                                     //״̬��״̬��
	
	if(eventJumpCondition())                                      //������������ת����һ״̬
	{
		fsm->CurState = fsmTable[curState].NextState;
		eventAction = fsmTable[fsm->CurState].EventAction;

		if(curState == size-1){                                     //������������ת����һ״̬��
			CurrentFSMNum++;
			CurrentFSM = MyFSMs[CurrentFSMNum];                       
			return;
		}
	}
	eventAction();
}

//״̬������ת  ����1��0
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

//״̬����ǰ״̬��ȡ
uint8_t FSMStateGet(FSM_t *fsm)
{
	return fsm->CurState;
}

