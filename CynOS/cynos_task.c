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

void Cynos_TASK_Jump(CynOSTask_Sta * cynostask_sta,CynOSTask_FLOW next_step,CynOS_U32 wait_time)
{
	if(cynostask_sta->_init_flag)
	{
		cynostask_sta->_task_next_flow=next_step;
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

CynOS_U8 CynosTaskIsInit(CynOSTask_Sta * cynostask_sta)
{
	if(cynostask_sta->_init_flag==0X55)
		return 1;
	return 0;
}

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
	CynosTask_Creat(lpw_systick,lpwInit,lpwTASK,10);
	CynosTask_Creat(lcd_systick,lcdInit,lcdTASK,10);
	CynosTask_Creat(sample_systick,sampleInit,sampleTASK,10);
	CynosTask_Creat(comm_systick,commInit,commTASK,10);
}
	






