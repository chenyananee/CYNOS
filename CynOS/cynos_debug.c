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




/*---------------------------------------------------------------------
  Function Name: CynOS_Debug
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
void CynOS_Debug(void(write)(char*data,unsigned int len),char*head,char * format,...)
{
	CynOS_U8 debugbuff[1024];
	CynOS_U16 debuge_len;
	
    va_list args;
    va_start(args, format);
	debuge_len+=sprintf((char*)&debugbuff[debuge_len], "[%s]:",head);
    debuge_len += vsprintf((char*)&debugbuff[debuge_len], format, args);
    va_end(args);
	write((char*)debugbuff,debuge_len);
}
























