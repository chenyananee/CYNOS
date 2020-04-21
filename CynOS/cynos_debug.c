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



/*---------------------------------------------------------------------
  Function Name: CynOS_Debug
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Debug(void(write)(char*data,unsigned int len),char*head,char * format,...)
{
	CynOS_U8 debugbuff[CYNOS_DEBUG_SIZE+sizeof(CynOS_Debug_Handle)];
	CynOS_U16 debuge_len;
	CynOS_Debug_Handle *debug_handle=(CynOS_Debug_Handle *)debugbuff;
	debug_handle->debugsize=CYNOS_DEBUG_SIZE;
	
    va_list args;
	CynOS_Mem_Set(debug_handle->debug_buff,0,debug_handle->debugsize,debug_handle->debugsize);
	if(!debug_handle->debugsize)
		return;
    va_start(args, format);
	debuge_len+=sprintf((char*)&debug_handle->debug_buff[debuge_len], "[%s]:",head);
    debuge_len += vsprintf((char*)&debug_handle->debug_buff[debuge_len], format, args);
    va_end(args);
	write((char*)debug_handle->debug_buff,debuge_len);
}
/*---------------------------------------------------------------------
  Function Name: CynOS_Debug
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Print_Char(void(write)(char*data,unsigned int len),char * format,...)
{
	CynOS_U8 debugbuff[CYNOS_DEBUG_SIZE+sizeof(CynOS_Debug_Handle)];
	CynOS_U16 debuge_len;
	CynOS_Debug_Handle *debug_handle=(CynOS_Debug_Handle *)debugbuff;
	debug_handle->debugsize=CYNOS_DEBUG_SIZE;
	
    va_list args;
	CynOS_Mem_Set(debug_handle->debug_buff,0,debug_handle->debugsize,debug_handle->debugsize);
	if(!debug_handle->debugsize)
		return;
    va_start(args, format);
    debuge_len += vsprintf((char*)&debug_handle->debug_buff[debuge_len], format, args);
    va_end(args);
	write((char*)debug_handle->debug_buff,debuge_len);
}
/*---------------------------------------------------------------------
  Function Name: CynOS_Debug
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Print_Hex(void(write)(char*data,unsigned int len),char * data,unsigned int len)
{
	write(data,len);
}























