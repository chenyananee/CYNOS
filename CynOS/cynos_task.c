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
#include "app.h"

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

/**************************************************************************************
*
*						    初始化用户任务
*						    
*
**************************************************************************************/
void Cynos_UserTask_Init()
{
	CynosTask_Creat(lcd_systick,lcdInit,lcdTASK,10);
	CynosTask_Creat(sample_systick,sampleInit,sampleTASK,10);
	CynosTask_Creat(comm_systick,commInit,commTASK,10);
	CynosTask_Creat(lpw_systick,lpwInit,lpwTASK,10);
}
	






