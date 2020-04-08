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
#include "cynos_sem.h"

CYNOS_STATUS CynOs_Sem_post(struct cynos_sem * sem)
{
	if(sem)
	{
		if(sem->sem_val < (sem->sem_type))
		{
			sem->sem_val++;
			return CYNOS_OK;
		}
		else
		{
			return CYNOS_ERR;
		}
	}
	return CYNOS_ERR;
}


CYNOS_STATUS CynOs_Sem_pend(struct cynos_sem * sem)
{
	if(sem)
	{
		if(sem->sem_val)
		{
			sem->sem_val--;
			return CYNOS_OK;
		}
		return CYNOS_ERR;
	}
	return CYNOS_ERR;
}

CYNOS_STATUS CynOs_Sem_Clear(struct cynos_sem * sem)
{
	if(sem)
	{
		sem->sem_val=0;
		return CYNOS_OK;
	}
	return CYNOS_ERR;
}

CYNOS_STATUS CynOs_Sem_Init(CynOS_Sem * sem,unsigned int sem_type)
{
	if(sem)
	{
		sem->pend=CynOs_Sem_pend;
		sem->post=CynOs_Sem_post;
		sem->clear=CynOs_Sem_Clear;
		sem->sem_type=(sem_type?(sem_type):(1));
		sem->sem_val=0;
		return CYNOS_ERR;
	}
	return CYNOS_ERR;
}





