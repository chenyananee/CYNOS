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

#if USE_CYNOS_EVENT
#include "cynos_kernel.h"
#include "cynos_event.h"
#include "cynos_funlib.h"

/**
 * @description: 
 * @param {CynosEventHandle} *evtque_handle
 * @param {CynOS_U16} quesize
 * @param {CynosEventHandle} *evt
 * @return {*}
 */
CYNOS_STATUS Cynos_EventPost(CynosEventHandle *evtque_handle,CynOS_U16 quesize,CynosEventHandle *evt)
{
	CynOS_U16 cnt=0;
	for(cnt=0;cnt<quesize;cnt++)
	{
		if(!evtque_handle[cnt].evt_avlable)
		{
			evtque_handle[cnt] = *evt;
			return CYNOS_OK;
		}
	}

	return CYNOS_ERR;
}
/**
 * @description: 
 * @param {CynosEventHandle} *evtque_handle
 * @param {CynOS_U16} quesize
 * @param {CynOS_U16} *staticIndex
 * @param {CynOS_U16} evtid
 * @param {CynosEventHandle} *evt
 * @return {*}
 */
CYNOS_STATUS Cynos_EventReceive(CynosEventHandle *evtque_handle,CynOS_U16 quesize,CynOS_U16 *staticIndex,CynOS_U16 evtid,CynosEventHandle *evt)
{
	CynOS_U16 cnt=0;

	cnt = *staticIndex;
	do
	{
		if(evtque_handle[*staticIndex].evt_avlable)
		{
			if(evtid)
			{
				if(evtque_handle[*staticIndex].id == evtid)
				{
					*evt = evtque_handle[*staticIndex];
					CynOS_Mem_Set(&evtque_handle[*staticIndex],0,sizeof(CynosEventHandle),sizeof(CynosEventHandle));
					return CYNOS_OK;
				}
			}
			else
			{
				*evt = evtque_handle[*staticIndex];
				CynOS_Mem_Set(&evtque_handle[*staticIndex],0,sizeof(CynosEventHandle),sizeof(CynosEventHandle));
				return CYNOS_OK;
			}
		}
		
		cnt++;
		*staticIndex++;
		if(*staticIndex >= quesize)
		{
			*staticIndex = 0;
		}
		
	} while (cnt != *staticIndex);

	return CYNOS_ERR;
}

#endif

