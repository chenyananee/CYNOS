/*
Copyright 2020 chenyanan

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
#include "cynos_cfg.h"
#include "cynos_kernel.h"
#include "cynos_task.h"


/*状态机跳转
arg 1: 任务状态句柄
arg 2: 即将跳转的流程
arg 3: 跳转等待时间
*/
void Cynos_TASK_Jump(CynOSTask_Sta * cynostask_sta,CynOSTask_FLOW next_step,CynOS_U32 wait_time)
{
	if(cynostask_sta->_init_flag)
	{
		cynostask_sta->_task_next_flow=next_step;
		/*立即跳转*/
		if(wait_time==0)
		{
			cynostask_sta->_task_flow=next_step;
		}
		else
		{
			cynostask_sta->_task_flow=CynOSTask_FLOW_DELAY;
		}
		
		cynostask_sta->_wait_time=wait_time;
		cynostask_sta->_time_cnt=0;
	}
}
CynOS_U8 Cynos_GetTask_Step(CynOSTask_Sta * cynostask_sta)
{
	if(cynostask_sta->_init_flag)
	{
		return cynostask_sta->_task_flow;
	}
	return CynOSTask_FLOW_IDLE;
}
void Cynos_Task_Init(CynOSTask_Sta * cynostask_sta)
{
	memset(cynostask_sta,0,sizeof(CynOSTask_Sta));
	cynostask_sta->_init_flag=0X55;
	cynostask_sta->_task_flow=CynOSTask_FLOW_IDLE;
	cynostask_sta->_task_next_flow=CynOSTask_FLOW_IDLE;
}
/*
	延时自动跳转函数
	需加入到延时状态内实现任务自动跳转
*/
void Cynos_TASK_Delay(CynOSTask_Sta * cynostask_sta)
{
	if(cynostask_sta->_init_flag)
	{
		if(cynostask_sta->_time_cnt>=cynostask_sta->_wait_time)
		{
			cynostask_sta->_task_flow=cynostask_sta->_task_next_flow;
			cynostask_sta->_wait_time=0;
			cynostask_sta->_time_cnt=0;
		}
	}
}

/*
	任务时间片
	需加入到每个任务注册的tick钩函数中
*/
void Cynos_TASK_SystickHandle(CynOSTask_Sta * cynostask_sta,CynOS_U32 time)
{
	if(cynostask_sta->_init_flag)
	{
		cynostask_sta->_time_cnt+=time;
	}
}





/*
============================任务状态机示例==============================
*/


/*
	状态机运行状态句柄
*/
CynOSTask_Sta CynOSTask_Sys_Sta={0};


/*
	任务内时间片钩函数（非内核任务时间片）
*/
void Cynos_TASK_HooK(CynOS_U32 time)
{
	Cynos_TASK_SystickHandle(&CynOSTask_Sys_Sta,time);
}

void Cynos_TASKInit(void)
{
	Cynos_Task_Init(&CynOSTask_Sys_Sta);
}
/*
	任务
*/
void Cynos_TASK_Sys(void * arg)
{
	switch(CynOSTask_Sys_Sta._task_flow)
	{
		case CynOSTask_FLOW_IDLE:
			Cynos_TASK_Jump(&CynOSTask_Sys_Sta,CynOSTask_FLOW_STEP_1,1000);
			break;
		case CynOSTask_FLOW_STEP_1:
			Cynos_TASK_Jump(&CynOSTask_Sys_Sta,CynOSTask_FLOW_IDLE,1000);
			break;
		case CynOSTask_FLOW_DELAY:
			Cynos_TASK_Delay(&CynOSTask_Sys_Sta);
			break;
		default:
			Cynos_TASK_Jump(&CynOSTask_Sys_Sta,CynOSTask_FLOW_IDLE,0);
			break;
	}
}


/**************************************************************************************
*
*						    初始化用户任务
*						    
*
**************************************************************************************/
void Cynos_UserTask_Init()
{
	CynosTask_Creat(Cynos_TASK_HooK,Cynos_TASKInit,Cynos_TASK_Sys,1000);
/*
=======================================================================================
	                         创建用户任务
=======================================================================================
*/
	
}
	










