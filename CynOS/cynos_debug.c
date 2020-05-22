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



#include "cynos_debug.h"
#include "cynos_funlib.h"


CynOS_Debug_Cfg gdebug_cfg;

/*---------------------------------------------------------------------
  Function Name: CynOS_Debug_Init
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Debug_Init(void(*write)(char*data,unsigned int len))
{
	memset(&gdebug_cfg,0,sizeof(CynOS_Debug_Cfg));
	gdebug_cfg.write=write;
	gdebug_cfg.debug_en=0x55;
}
/*---------------------------------------------------------------------
  Function Name: CynOS_Debug_Open
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Debug_Open(void)
{
	if(gdebug_cfg.write)
	{
		gdebug_cfg.debug_en=0x55;
	}
}
/*---------------------------------------------------------------------
  Function Name: CynOS_Debug_Close
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Debug_Close(void)
{
	gdebug_cfg.debug_en=0;
}
/*---------------------------------------------------------------------
  Function Name: CynOS_Debug
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Debug(char*head,char * format,...)
{
	CynOS_U8 debugbuff[CYNOS_DEBUG_SIZE+sizeof(CynOS_Debug_Handle)];
	CynOS_U16 debuge_len = 0;
	CynOS_Debug_Handle *debug_handle=(CynOS_Debug_Handle *)debugbuff;
	debug_handle->debugsize=CYNOS_DEBUG_SIZE;
	
    va_list args;
    CynOS_Mem_Set(debug_handle->debug_buff,0,debug_handle->debugsize,debug_handle->debugsize);
    if(!debug_handle->debugsize)
      return;
    va_start(args, format);
	if (head != NULL)
	{
		debuge_len += sprintf((char*)&debug_handle->debug_buff[debuge_len], "\r\n[%s]:",head);
	}
    debuge_len += vsprintf((char*)&debug_handle->debug_buff[debuge_len], format, args);
    va_end(args);
	if((gdebug_cfg.write)&&(gdebug_cfg.debug_en==0x55))
	{
		gdebug_cfg.write((char*)debug_handle->debug_buff,debuge_len);
	}
}
/*---------------------------------------------------------------------
  Function Name: CynOS_Debug
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Print_Char(char * format,...)
{
	CynOS_U8 debugbuff[CYNOS_DEBUG_SIZE+sizeof(CynOS_Debug_Handle)];
	CynOS_U16 debuge_len = 0;
	CynOS_Debug_Handle *debug_handle=(CynOS_Debug_Handle *)debugbuff;
	debug_handle->debugsize=CYNOS_DEBUG_SIZE;
	
    va_list args;
	CynOS_Mem_Set(debug_handle->debug_buff,0,debug_handle->debugsize,debug_handle->debugsize);
	if(!debug_handle->debugsize)
		return;
    va_start(args, format);
    debuge_len += vsprintf((char*)&debug_handle->debug_buff[debuge_len], format, args);
    va_end(args);
	if((gdebug_cfg.write)&&(gdebug_cfg.debug_en==0x55))
	{
		gdebug_cfg.write((char*)debug_handle->debug_buff,debuge_len);
	}
}
/*---------------------------------------------------------------------
  Function Name: CynOS_Debug
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Print_Hex(unsigned char * data,unsigned int len)
{
	CynOS_U8 debugbuff[CYNOS_DEBUG_SIZE];
	CynOS_U16 debuge_len = 0;
	
	while (len--)
	{
		debuge_len += sprintf((char*)&debugbuff[debuge_len], "%.2X ", data[0]);
		data++;
		if (debuge_len + 2 >= CYNOS_DEBUG_SIZE)
		{
			break;
		}
	}
	if((gdebug_cfg.write) && (gdebug_cfg.debug_en == 0x55))
	{
		gdebug_cfg.write((char*)&debugbuff[0], debuge_len);
	}
}























