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
#include "cynos_mutex.h"


CYNOS_STATUS CynOs_Mutex_Lock(struct cynos_mutex * mutex,CynOS_U32 process_id)
{
	if(mutex->mutex_val==CynOS_Mutex_LOCK)
	{
		if(mutex->process_id==process_id)
		{
			return CYNOS_OK;
		}
		else
		{
			return CYNOS_ERR;
		}
	}
	else
	{
		mutex->mutex_val=CynOS_Mutex_LOCK;
		mutex->process_id=process_id;
		return CYNOS_OK;
	}
}

CYNOS_STATUS CynOs_Mutex_UNLock(struct cynos_mutex * mutex,CynOS_U32 process_id)
{
	if(mutex->mutex_val==CynOS_Mutex_LOCK)
	{
		if(mutex->process_id==process_id)
		{
			mutex->mutex_val=CynOS_Mutex_UNLOCK;
			mutex->process_id=CynOS_U32_MAX;
			return CYNOS_OK;
		}
		else
		{
			return CYNOS_ERR;
		}
	}
	else
	{
		mutex->mutex_val=CynOS_Mutex_UNLOCK;
		mutex->process_id=CynOS_U32_MAX;
		return CYNOS_OK;
	}
	
}

CYNOS_STATUS CynOs_Mutex_Get(struct cynos_mutex * mutex,CynOS_U32 process_id)
{
	if(mutex->mutex_val==CynOS_Mutex_LOCK)
	{
		if(mutex->process_id==process_id)
		{
			return CYNOS_OK;
		}
		else
		{
			return CYNOS_ERR;
		}
	}
	else
	{
		return CYNOS_OK;
	}

}





CYNOS_STATUS CynOs_Mutex_Init(CynOS_Mutex * mutex)
{
	if(mutex)
	{
		memset(mutex,0,sizeof(CynOS_Mutex));
		mutex->lock=CynOs_Mutex_Lock;
		mutex->unlock=CynOs_Mutex_UNLock;
		mutex->get=CynOs_Mutex_Get;
		mutex->mutex_val=CynOS_Mutex_UNLOCK;
		mutex->process_id=CynOS_U32_MAX;
		return CYNOS_OK;
	}	
	return CYNOS_ERR;
}





