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

//判断函数


uint8_t JudgeUp();
uint8_t JudgeDown();
uint8_t JudgeNormal();

void MyFSMInit();    //初始状态配置及初始化
void MyFSMRun(FSM_t *fsm);    //状态机的开启
	
extern uint8_t CurrentFSMNum;
	

#endif