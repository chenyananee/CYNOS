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
#include "cynos_schedule.h"
#include "cynos_funlib.h"

extern CYNOS_STATUS CynOsTaskSchedule(CynOS_VOID*taskfifo,CynOS_U32 size,CynOS_U8 typesize,CynOS_U8 dir);


CYNOS_STATUS cynos_schedule_get(CynOS_Schedule_Handle * handle,CynOS_U32 id)
{
	if((handle->schedule_len)&&(handle->schedule_fifo[handle->schedule_len-1]==id))
	{
		return CYNOS_OK;
	}
	return CYNOS_ERR;
}


CYNOS_STATUS cynos_schedule_append(CynOS_Schedule_Handle *handle,CynOS_U32 id)
{
	CynOS_U32 index = 0;
	if(handle->schedule_len<handle->schedule_fifo_size)
	{
		for (index = 0; index < handle->schedule_len;index++)
		{
			if(handle->schedule_fifo[index] == id)
			{
				if(handle->schedule_fifo[handle->schedule_len-1]==id)
				{
					return CYNOS_OK;
				}
				return CYNOS_ERR;
			}
		}
		handle->schedule_fifo[handle->schedule_len]=id;
		handle->schedule_len++;
		CynOsTaskSchedule(handle->schedule_fifo,handle->schedule_len,sizeof(CynOS_U32),1);
		if(handle->schedule_fifo[handle->schedule_len-1]==id)
		{
			return CYNOS_OK;
		}
	}
	return CYNOS_ERR;
}

CYNOS_STATUS cynos_schedule_delete(CynOS_Schedule_Handle *handle,CynOS_U32 id)
{
	if(handle->schedule_len)
	{
		for(CynOS_U32 iii=0;iii<handle->schedule_len;iii++)
		{
			if(id==handle->schedule_fifo[iii])
			{
				CynOS_Mem_Cpy(&handle->schedule_fifo[iii],
							  &handle->schedule_fifo[iii+1],
							  (sizeof(CynOS_U32)*(handle->schedule_len-iii-1)),
							  (sizeof(CynOS_U32)*(handle->schedule_len-iii-1)));
				handle->schedule_len-=1;
				return CYNOS_OK;
			}
		}
	}
	return CYNOS_ERR;
}

CYNOS_STATUS CynOS_Schedule_Init(CynOS_Schedule_Handle * schedule_fifo,CynOS_U32 fifo_size)
{
	memset(schedule_fifo,0,sizeof(CynOS_Schedule_Handle));
	if(fifo_size<=sizeof(CynOS_Schedule_Handle))
		return CYNOS_ERR;
	
	schedule_fifo->schedule_fifo_size=fifo_size-sizeof(CynOS_Schedule_Handle);
	schedule_fifo->schedule_get=cynos_schedule_get;
	schedule_fifo->schedule_append=cynos_schedule_append;
	schedule_fifo->schedule_delete=cynos_schedule_delete;
	return CYNOS_OK;
}







