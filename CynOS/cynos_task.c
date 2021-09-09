/*
Copyright ? 2020 ChenYanan.

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
#include "cynos_task.h"

CYNOS_STATUS CynOS_TaskHandleInit(CynOSTaskHandle *taskhandle,CynOSVoidFun init_fun,CynOSPointFun entry,CynOS_U32 tick)
{
	if(!taskhandle) return CYNOS_ERR_MEM;

	memset(taskhandle,0,sizeof(CynOSTaskHandle));
	taskhandle->init = init_fun;
	taskhandle->_task_current_flow = CynOSTask_FLOW_IDLE;
	taskhandle->task_entry = entry;
	taskhandle->task_frq = tick;
	taskhandle->task_flag.avl_flag = 1;
	return CYNOS_OK;
}


CynOS_VOID Cynos_TASK_Jump(CynOSTaskHandle * handle,CynOS_U32 next_step,CynOS_U32 wait_time)
{
	if(!handle) return;

	if(handle->task_flag.init_flag)
	{
		handle->_task_next_flow=next_step;
		if(wait_time==0)
		{
			handle->_task_current_flow=next_step;
		}
		else
		{
			handle->_task_current_flow=CynOSTask_FLOW_DELAY;
		}
		
		handle->delay=wait_time;
		handle->delay_cnt=0;
	}
}

CynOS_U8 Cynos_GetTask_Step(CynOSTaskHandle * handle)
{
	if(handle->task_flag.init_flag)
	{
		return handle->_task_current_flow;
	}
	return CynOSTask_FLOW_IDLE;
}

CynOS_VOID Cynos_TASK_Delay(CynOSTaskHandle * handle)
{
	if(handle->task_flag.init_flag)
	{
		if(handle->delay_cnt>=handle->delay)
		{
			handle->_task_current_flow=handle->_task_next_flow;
			handle->delay_cnt=0;
			handle->delay=0;
		}
	}
}


CynOS_VOID Cynos_TASK_SystickHandle(CynOSTaskHandle * handle,CynOS_U32 tick)
{
	handle->delay_cnt += tick;
	handle->task_time_cnt += tick;
}








