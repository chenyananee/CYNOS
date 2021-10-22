/*
Copyright © 2020 ChenYanan.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "cynos_fsm.h"


/**
 * @description: 
 * @param {CynOSFsm_Handle} *fsm
 * @return {*}
 */
CynOS_VOID Cynos_FsmSC_Jump(CynOS_VOID *scFsm,CynOS_U8 next_step,CynOS_U32 wait_time)
{
	CynOSFSM_SC_Handle *fsm = (CynOSFSM_SC_Handle *)scFsm;

	if(!fsm) return;

	fsm->_task_next_flow=next_step;
	if(wait_time==0)
	{
		fsm->_task_current_flow=fsm->_task_next_flow;
	}
	else
	{
		fsm->_task_current_flow=CynOSTask_FLOW_DELAY;
	}
	
	fsm->delay=wait_time;
	fsm->delay_cnt=0;
}

/**
 * @description: 
 * @param {CynOSFsm_Handle} *fsm
 * @return {*}
 */
CynOS_VOID Cynos_FsmSC_TimeHook(CynOS_VOID *scFsm,CynOS_U32 tick)
{
	CynOSFSM_SC_Handle *fsm = (CynOSFSM_SC_Handle *)scFsm;

	if(!fsm) return;

	fsm->delay_cnt += tick;
}

/**
 * @description: 
 * @param {CynOSFsm_Handle} *fsm
 * @return {*}
 */
CynOS_U8 Cynos_FsmSC_GetStep(CynOS_VOID *scFsm)
{
	CynOSFSM_SC_Handle *fsm = (CynOSFSM_SC_Handle *)scFsm;

	if(!fsm) return CYNOS_ERR_MEM;

	return fsm->_task_current_flow;
}
/**
 * @description: 
 * @param {CynOSFsm_Handle} *fsm
 * @return {*}
 */
CynOS_VOID Cynos_FsmSC_Wait(CynOS_VOID *scFsm)
{
	CynOSFSM_SC_Handle *fsm = (CynOSFSM_SC_Handle *)scFsm;

	if(!fsm) return;

	if(fsm->delay_cnt>=fsm->delay)
	{
		fsm->_task_current_flow=fsm->_task_next_flow;
		fsm->delay_cnt=0;
		fsm->delay=0;
	}
}

/**
 * @description: 
 * @param {CynOSFsm_Handle} *fsm: fsm handle
 * @param {int} newstatus:the status that we want to go
 * @return {*}
 */
CynOS_VOID Cynos_Fsm_Jump(CynOSFsm_Handle *fsm,int newstatus)
{
	fsm->info.next = newstatus;
	fsm->func[fsm->info.current].exit(fsm);
	fsm->info.last = fsm->info.current;
	fsm->info.current = fsm->info.next;
	fsm->func[fsm->info.current].entry(fsm);
}
/**
 * @description: 
 * @param {CynOSFsm_Handle} *fsm
 * @return {*}
 */
CynOS_VOID Cynos_Fsm_Goback(CynOSFsm_Handle *fsm)
{
	Cynos_Fsm_Jump(fsm,fsm->info.last);
}

/**
 * 
//=================fsm demo for use(not for switch/case fsm, it's so easy to use)=============

int evt = 0;

void sta1(void *handle) {evt = 1;}
void sta2(void *handle) {evt = 2;}
void sta3(void *handle) {evt = 3;}

typedef enum {

	em_sta1 = 0,
	em_sta2,
	em_sta3,
}sta;

CYNOS_FSM_INIT_BEGIN(Motor)
CYNOS_FSM_INFO_INIT(em_sta1,em_sta1,em_sta1)
CYNOS_FSM_FUNC_INIT(
CYNOS_FSM_FUNC_MAP(sta1,sta1,sta1,sta1)
CYNOS_FSM_FUNC_MAP(sta2,sta2,sta2,sta2)
CYNOS_FSM_FUNC_MAP(sta3,sta3,sta3,sta3)
)
CYNOS_FSM_INIT_END


int main(void)
{
	while(1)
	{
		if(!evt)
		{
			Cynos_Fsm_Jump(&CYNOS_FSM_NAME(Motor),em_sta1);
		}
		else if(2 == evt)
		{
			Cynos_Fsm_Jump(&CYNOS_FSM_NAME(Motor),em_sta2);
		}
		else
		{
			Cynos_Fsm_Jump(&CYNOS_FSM_NAME(Motor),em_sta3);
		}
	}
}


**/