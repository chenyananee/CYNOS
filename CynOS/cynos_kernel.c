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
#include "cynos_time.h"

CynOS_Run_Status gcynos_sta;
CynOS_UserTask_Info_Handle gUserTask[CYNOS_USER_TASK_MAX];

CynOS_U8 CynosTask_Create(void(*time_hook)(CynOS_U32 time),void(*Constructor)(void),void(*Destructor)(void),void(*task)(void * arg),CynOS_U32 tasktick)
{
	CynOS_U8 index=0;
	if(gcynos_sta.init_sta==0x55)
	{
		for(index=0;index<CYNOS_USER_TASK_MAX;index++)
		{
			if(gUserTask[index].task==0)
			{
				gUserTask[index].task_event=CynOS_TASK_EVENT_NULL;
				gUserTask[index].task_sta=CynOS_TASK_EVENT_RUN;
				gUserTask[index].task_id=index;
				gUserTask[index].task=task;
				gUserTask[index].taskConstructor=Constructor;
				gUserTask[index].taskDestructor=Destructor;
				gUserTask[index].time_hook=time_hook;
				gUserTask[index].task_tick=tasktick;
				if(gUserTask[index].time_hook)
				{
					CynOS_Tim_Base_Login(gUserTask[index].time_hook);
				}
				return index;
			}
		}
	}
	return 0xff;
}

CynOS_U8 CynosTask_Delete(CynOS_U8 task_id)
{
	if((gUserTask[task_id].task)&&(gUserTask[task_id].task_id==task_id))
	{
		CynOS_Tim_Base_Logout(gUserTask[task_id].time_hook);
		if(gUserTask[task_id].taskDestructor)
		{
			gUserTask[task_id].taskDestructor();
		}
		gUserTask[task_id].task_event=CynOS_TASK_EVENT_NULL;
		gUserTask[task_id].task_sta=CynOS_TASK_EVENT_NULL;
		gUserTask[task_id].task_id=0;
		gUserTask[task_id].task=0;
		gUserTask[task_id].taskConstructor=0;
		gUserTask[task_id].taskDestructor=0;
		gUserTask[task_id].time_hook=0;
		gUserTask[task_id].task_tick=0;
		return CYNOS_OK;
	}
	return CYNOS_ERR;
}

void CynOs_Systick(CynOS_U32 cnt)
{
    CynOS_U8 iii=0;
	for(iii=0;iii<CYNOS_USER_TASK_MAX;iii++)
	{
		if(gUserTask[iii].task)
		{
			gUserTask[iii].task_tick_cnt+=cnt;
		}
	}
}


void CynOS_Init(void)
{
	memset(gUserTask,0,sizeof(CynOS_UserTask_Info_Handle));
	memset(&gcynos_sta,0,sizeof(CynOS_Run_Status));
	gcynos_sta.init_sta=0x55;
	CynOS_Tim_Base_Login(CynOs_Systick); 
}

void CynOS_PENDING(CynOS_U8 taskid)
{
	if(taskid<CYNOS_USER_TASK_MAX)
	{
		gUserTask[taskid].task_event|=CynOS_TASK_EVENT_PEND;
	}
}

void CynOS_RESUM(CynOS_U8 taskid)
{
	if(taskid<CYNOS_USER_TASK_MAX)
	{
		gUserTask[taskid].task_event|=CynOS_TASK_EVENT_RESUM;
	}
}


void CynOS_Login_Hook(CynOS_U8 taskid,CynOS_TASK_STA task_type,void(*eventhook)(void))
{
	if(taskid<CYNOS_USER_TASK_MAX)
	{
		switch(task_type)
		{
			case CynOS_TASK_EVENT_TIME:
#if CYNOS_TASK_TIME_HOOK_EN
			    gUserTask[taskid].task_event_time_hook=eventhook;
#endif
				break;
			case CynOS_TASK_EVENT_PEND:
#if CYNOS_TASK_PEND_HOOK_EN
                gUserTask[taskid].task_event_pend_hook=eventhook;
#endif
				break;
			case CynOS_TASK_EVENT_RESUM:
#if CYNOS_TASK_RESUM_HOOK_EN
                gUserTask[taskid].task_event_resume_hook=eventhook;
#endif

				break;
			default:
				break;
		}
	}
}


CynOS_U8 CynOS_Get_KernelVersion(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_VERSION,strlen(CYNOS_KERNEL_VERSION));
	return strlen(CYNOS_KERNEL_VERSION);
}

CynOS_U8 CynOS_Get_KernelDate(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_DATE,strlen(CYNOS_KERNEL_DATE));
	return strlen(CYNOS_KERNEL_DATE);
}

CynOS_U8 CynOS_Get_KernelBuildDate(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_BUILD_DATE,strlen(CYNOS_KERNEL_BUILD_DATE));
	return strlen(CYNOS_KERNEL_BUILD_DATE);
}

CynOS_U8 CynOS_Get_KernelBuildTime(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_BUILD_TIME,strlen(CYNOS_KERNEL_BUILD_TIME));
	return strlen(CYNOS_KERNEL_BUILD_TIME);
}

CYNOS_STATUS CynOS_Get_Task_Info(CynOS_U32 task_id,CynOS_UserTask_Info_Handle * task_info)
{
	CynOS_U32 index;
	if(gcynos_sta.init_sta==0x55)
	{
		for(index=0;index<CYNOS_USER_TASK_MAX;index++)
		{
			if(gUserTask[index].task_id==task_id)
			{
				*task_info=gUserTask[index];
				return CYNOS_OK;
			}
		}
	}
	return CYNOS_ERR;
}

CynOS_U32 CynOS_Get_Task_ID(void)
{
	return gcynos_sta.task_id;
}

void CynOsStart(void)
{
	CynOS_U8 iii=0;
	#if CYNOS_DEBUG_KERNEL_EN
	CYNOS_DEBUG_KERNEL_PRINT("\r\n");
	CYNOS_DEBUG_KERNEL_PRINT(CYNOS_KERNEL_DESC);
	CYNOS_DEBUG_KERNEL_PRINT("\r\n");
	CYNOS_DEBUG_KERNEL_PRINT("kernel will start\r\n");
	CYNOS_DEBUG_KERNEL_PRINT(CYNOS_KERNEL_VERSION);
	CYNOS_DEBUG_KERNEL_PRINT("\r\n");
	CYNOS_DEBUG_KERNEL_PRINT(CYNOS_KERNEL_DATE);
	CYNOS_DEBUG_KERNEL_PRINT("\r\n");
	#endif
	for(iii=0;iii<CYNOS_USER_TASK_MAX;iii++)
	{
		if(gUserTask[iii].taskConstructor)
		{
			#if CYNOS_DEBUG_KERNEL_EN
			CYNOS_DEBUG_KERNEL_PRINT("task[%02d] will ihit...\r\n",iii);
			#endif
			gUserTask[iii].taskConstructor();
		}
	}
	#if CYNOS_DEBUG_KERNEL_EN
	CYNOS_DEBUG_KERNEL_PRINT("Scheduling\r\n");
	#endif
	while(1)
	{
		for(iii=0;iii<CYNOS_USER_TASK_MAX;iii++)
		{
			if(gUserTask[iii].task)
			{
				if(gUserTask[iii].task_event&CynOS_TASK_EVENT_PEND)
				{
					#if CYNOS_DEBUG_KERNEL_EN
					CYNOS_DEBUG_KERNEL_PRINT("task[%02d] is suspended\r\n",gUserTask[iii].task_id);
					#endif
					gUserTask[iii].task_event&=(~CynOS_TASK_EVENT_PEND);
					gUserTask[iii].task_sta=CynOS_TASK_EVENT_PEND;
					#if CYNOS_TASK_PEND_HOOK_EN
					{
						#if CYNOS_DEBUG_KERNEL_EN
						CYNOS_DEBUG_KERNEL_PRINT("task[%02d] event_pend_hook\r\n",gUserTask[iii].task_id);
						#endif
						if(gUserTask[iii].task_event_pend_hook)
						{
							gUserTask[iii].task_event_pend_hook();
						}
					}
					#endif
				}
				else if(gUserTask[iii].task_event&CynOS_TASK_EVENT_RESUM)
				{
					#if CYNOS_DEBUG_KERNEL_EN
					CYNOS_DEBUG_KERNEL_PRINT("task[%02d] is resumed\r\n",gUserTask[iii].task_id);
					#endif
					gUserTask[iii].task_event&=(~CynOS_TASK_EVENT_RESUM);
					gUserTask[iii].task_sta=CynOS_TASK_EVENT_RUN;
					#if CYNOS_TASK_RESUM_HOOK_EN
					{
						#if CYNOS_DEBUG_KERNEL_EN
						CYNOS_DEBUG_KERNEL_PRINT("task[%02d] event_resume_hook\r\n",gUserTask[iii].task_id);
						#endif
						if(gUserTask[iii].task_event_resume_hook)
						{
							gUserTask[iii].task_event_resume_hook();
						}
					}
					#endif
				}
				
				if(gUserTask[iii].task_sta==CynOS_TASK_EVENT_RUN)
				{
					gcynos_sta.task_id=gUserTask[iii].task_id;
					#if CYNOS_TASK_SYSTICK_EN
					if(gUserTask[iii].task_tick_cnt>=gUserTask[iii].task_tick)
					{
						gUserTask[iii].task_tick_cnt=0;
						#if CYNOS_TASK_TIME_HOOK_EN
						
						if(gUserTask[iii].task_event_time_hook)
						{
							gUserTask[iii].task_event_time_hook();
						}
						#endif
						gUserTask[iii].task(gUserTask[iii].arg);
					}
					#else
					gUserTask[iii].task(gUserTask[iii].prm);
					#endif
				}
			}
		}
	}
}






