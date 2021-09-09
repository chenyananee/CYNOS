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


#include "cynos_kernel.h"

/*
	CynOS_KernelObj_Init
*/
CYNOS_STATUS CynOS_KernelObj_Init(CynOS_ObjHandle *obj,CynOS_U8 max_task,CynOSVoidFun init_fun)
{
	if(init_fun) init_fun();

	memset(obj,0,sizeof(CynOS_ObjHandle) + sizeof(CynOSTaskHandle) * max_task);
	obj->tasknum = max_task;
	
	obj->obj_flag.init_flag = 1;
	obj->kernelstatus = CYNOS_KERNEL_RUN;
	return CYNOS_OK;
}


/*
	CynOS_Kernel_Task_Create
*/
CYNOS_STATUS CynOS_Kernel_Task_Create(CynOS_ObjHandle *obj,
									  CynOSVoidFun init_fun,
									  CynOSPointFun entry,
									  CynOS_U32 tick)
{
	if(!obj) return CYNOS_ERR_MEM;

	for(CynOS_U8 i = 0; i < obj->tasknum; i++)
	{
		if(!obj->task[i].task_flag.avl_flag)
		{
			return CynOS_TaskHandleInit(&obj->task[i],init_fun,entry,tick);
		}
	}
	return CYNOS_ERR;
}

/*
	CynOS_KernelObj_Tick
*/
CynOS_VOID CynOS_KernelObj_Tick(CynOS_ObjHandle *obj,CynOS_U32 tick)
{
	if(obj->obj_flag.init_flag)
	{
		for(CynOS_U8 i = 0; i < obj->tasknum; i++)
		{
			if(obj->task[i].task_flag.avl_flag)
			{
				if(obj->task[i].task_flag.init_flag)
				{
					Cynos_TASK_SystickHandle(&obj->task[i],tick);
				}
			}
		}
	}
}

/*
	CynOS_KernelObj_Run
*/
CynOS_VOID CynOS_KernelObj_Run(CynOS_ObjHandle *obj)
{
	switch(obj->kernelstatus)
	{
		case CYNOS_KERNEL_RUN:
			for(CynOS_U8 i = 0; i < obj->tasknum; i++)
			{
				if(obj->task[i].task_flag.avl_flag)
				{
					if(!obj->task[i].task_flag.init_flag)
					{
						obj->task[i].init();
						obj->task[i].task_flag.init_flag = 1;
					}
					else
					{
						if(obj->task[i].task_time_cnt >= obj->task[i].task_frq)
						{
							obj->task[i].task_time_cnt = 0;
							obj->task[i].task_entry(&obj->task[i].id);
						}	
					}
				}
			}
		break;

		case CYNOS_KERNEL_STOP:
		break;

		case CYNOS_KERNEL_RESET:
			for(CynOS_U8 i = 0; i < obj->tasknum; i++)
			{
				if(obj->task[i].task_flag.avl_flag)
				{
					obj->task[i].task_flag.init_flag = 0;
				}
			}
			obj->kernelstatus = CYNOS_KERNEL_RUN;
		break;

		default:
			obj->kernelstatus = CYNOS_KERNEL_RESET;
		break;
	}
}
/*
	CynOS_Start
*/
CynOS_VOID CynOS_Start(CynOS_ObjHandle *obj,CynOS_U32 run_cnt)
{
	if(run_cnt == KERNEL_RUN_FOREVER)
	{
		while(1)
		{
			CynOS_KernelObj_Run(obj);
		}
	}
	else
	{
		while(run_cnt--)
		{
			CynOS_KernelObj_Run(obj);
		}
	}
}
/*
	set the kernel obj's status to RUN, stop or reset
*/
CynOS_VOID CynOS_KernelObj_Set_Status(CynOS_ObjHandle *obj,CynOS_U32 status)
{
	obj->kernelstatus = status;
}



