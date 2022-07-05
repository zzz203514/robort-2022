#ifndef USERFSM_H_
#define USERFSM_H_

#include "FSM.h"
#include "LinePatrolAction.h"
#include "Judgement.h"

enum CarState
{ 
	GoToBlock,
	UpBlock,
	OnBlock,
	DownBlock,
	OnGround,
	UpStage,
	OnStage,
	OnCricle,
};

//�жϺ���


uint8_t JudgeUp();
uint8_t JudgeDown();
uint8_t JudgeNormal();

void MyFSMInit();    //��ʼ״̬���ü���ʼ��
void MyFSMRun(FSM_t *fsm);    //״̬���Ŀ���
	
extern uint8_t CurrentFSMNum;
	

#endif