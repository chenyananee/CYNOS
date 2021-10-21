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

#include "cynos_time.h"

CREATE_TIME_OBJ(CYN_TIM,CYNOS_TIME_SIZE)

void CynOS_TimeHandle_Init(CynOS_TimeHandle *handle,CynOS_U8 timenum)
{
	memset(handle,0,sizeof(CynOS_TimeHandle) + sizeof(CynOSTime) * timenum);
	handle->timeNum = timenum;
	handle->init = 0x55;
}

/*
	Init the time
*/
void CynOS_Time_Init(void)
{
	CynOS_TimeHandle_Init(CYNOS_TME(CYN_TIM),CYNOS_TIME_SIZE);
}

/*
	Start the time by id
*/
CYNOS_STATUS CynOS_Time_Start(CynOS_U8 id)
{
	for(CynOS_U8 i = 0; i < CYNOS_TME(CYN_TIM)->timeNum; i++)
	{
		if(CYNOS_TME(CYN_TIM)->time[i].time_flag.avl_flag)
		{
			if(CYNOS_TME(CYN_TIM)->time[i].id == id)
			{
				CYNOS_TME(CYN_TIM)->time[i].time_flag.status_flag = CYNOS_TIME_RUN;
			}
		}
	}

	return CYNOS_OK;
}
/*
	Stop the time by id
*/
CYNOS_STATUS CynOS_Time_Stop(CynOS_U8 id)
{
	for(CynOS_U8 i = 0; i < CYNOS_TME(CYN_TIM)->timeNum; i++)
	{
		if(CYNOS_TME(CYN_TIM)->time[i].time_flag.avl_flag)
		{
			if(CYNOS_TME(CYN_TIM)->time[i].id == id)
			{
				CYNOS_TME(CYN_TIM)->time[i].time_flag.status_flag = !CYNOS_TIME_RUN;
			}
		}
	}

	return CYNOS_OK;
}

/*
	create the time by id
*/
CYNOS_STATUS CynOS_Time_Login(CynOS_U8 id,CynOS_U32 tick,CynOSPointFun cb)
{
	CynOS_U8 free_index=CynOS_U8_MAX,index=CynOS_U8_MAX;

	for(CynOS_U8 i = 0; i < CYNOS_TME(CYN_TIM)->timeNum; i++)
	{
		if(!CYNOS_TME(CYN_TIM)->time[i].time_flag.avl_flag)
		{
			if(free_index == 0xff)
			{
				free_index = i;
			}
		}
		if(CYNOS_TME(CYN_TIM)->time[i].id == id)
		{
			index = i;
			break;
		}
	}

	if(index == CynOS_U8_MAX)
	{
		if(free_index != CynOS_U8_MAX)
		{
			memset(&CYNOS_TME(CYN_TIM)->time[free_index],0,sizeof(CynOSTime));
			CYNOS_TME(CYN_TIM)->time[free_index].time_flag.avl_flag = 1;
			CYNOS_TME(CYN_TIM)->time[free_index].cb_entry = cb;
			CYNOS_TME(CYN_TIM)->time[free_index].frq = tick;
			CYNOS_TME(CYN_TIM)->time[free_index].id = id;
			CYNOS_TME(CYN_TIM)->time[free_index].time_flag.status_flag = CYNOS_TIME_RUN;
			return CYNOS_OK;
		}
		return CYNOS_ERR;
	}
}
/*
	DELETE the time by id
*/
CYNOS_STATUS CynOS_Time_Logout(CynOS_U8 id)
{
	for(CynOS_U8 i = 0; i < CYNOS_TME(CYN_TIM)->timeNum; i++)
	{
		if(CYNOS_TME(CYN_TIM)->time[i].time_flag.avl_flag)
		{
			if(CYNOS_TME(CYN_TIM)->time[i].id == id)
			{
				CYNOS_TME(CYN_TIM)->time[i].time_flag.avl_flag = 0;
			}
		}
	}

	return CYNOS_OK;
}

/*
	must be run in time interrupt
*/
void CynOS_Time_TickInterrupt(CynOS_U32 timebase)
{
	if(CYNOS_TME(CYN_TIM)->init)
	{
		for(CynOS_U8 i=0;i<CYNOS_TME(CYN_TIM)->timeNum;i++)
		{
			if(CYNOS_TME(CYN_TIM)->time[i].time_flag.avl_flag)
			{
				if(CYNOS_TME(CYN_TIM)->time[i].time_flag.status_flag == CYNOS_TIME_RUN)
				{
					CYNOS_TME(CYN_TIM)->time[i].time_cnt += timebase;
					if(CYNOS_TME(CYN_TIM)->time[i].time_cnt >= CYNOS_TME(CYN_TIM)->time[i].frq)
					{
						CYNOS_TME(CYN_TIM)->time[i].time_cnt = 0;
						if(CYNOS_TME(CYN_TIM)->time[i].cb_entry)
						{
							CYNOS_TME(CYN_TIM)->time[i].cb_entry(&timebase);
						}
					}
				}
			}
		}
	}
}










