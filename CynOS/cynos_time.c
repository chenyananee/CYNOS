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
#include "cynos_cfg.h"
#include "cynos_time.h"
#include "cynos_kernel.h"

time_hook_fun gCynosTimebase_Hook[TIME_HOOK_MAX];


CYNOS_STATUS CynOS_Tim_Base_Login(void(*time_hook)(CynOS_U32 time))
{
	static char cynos_tim_base_init = 0;
	
	CynOS_U8 index=0;
	if(cynos_tim_base_init)
	{
		for(index=0;index<TIME_HOOK_MAX;index++)
		{
			if(gCynosTimebase_Hook[index]==0)
			{
				gCynosTimebase_Hook[index]=time_hook;
				return CYNOS_OK;
			}
		}
		
		return CYNOS_ERR_MEM;
	}
	else
	{
		cynos_tim_base_init=0X55;
		memset(gCynosTimebase_Hook,0,TIME_HOOK_MAX*sizeof(time_hook_fun));
		gCynosTimebase_Hook[0]=time_hook;
		return CYNOS_OK;
	}
	
}

CYNOS_STATUS CynOS_Tim_Base_Logout(void(*time_hook)(CynOS_U32 time))
{
	
	CynOS_U8 index=0;
	
	for(index=0;index<TIME_HOOK_MAX;index++)
	{
		if(gCynosTimebase_Hook[index]==time_hook)
		{
			gCynosTimebase_Hook[index]=0;
			return CYNOS_OK;
		}
	}
	
	return CYNOS_ERR;	
}

/*
	must run in time interrupt
*/
void CynOS_Systick_Handle(CynOS_U32 timebase)
{
	CynOS_U8 index=0;

	if(gcynos_sta.init_sta==0x55)
	{
		for(index=0;index<TIME_HOOK_MAX;index++)
		{
			if(gCynosTimebase_Hook[index]!=0)
			{
				gCynosTimebase_Hook[index](timebase);
			}
		}
	}
}










