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



#include "cynos_funlib.h"



/*==============================================MEM================================================================*/
/*
*********************************************************************************************************
* 函数名称: CynOS_Mem_Cpy
*
* 函数说明: 数组拷贝函数
*
* 入口参数:
*
* 返回参数: 拷贝长度
*
* 特殊说明:
*********************************************************************************************************
*/

CynOS_U32 CynOS_Mem_Cpy (void *dst, void *src, CynOS_U32 len, CynOS_U32 limit)
{
	len=(len>limit)?(limit):(len);
	memcpy(dst,src,len);
	return len;
}
/*
*********************************************************************************************************
* 函数名称: CynOS_Mem_Set
*
* 函数说明: 数组设置
*
* 入口参数:
*
* 返回参数: 拷贝长度
*
* 特殊说明:
*********************************************************************************************************
*/

CynOS_U32 CynOS_Mem_Set (void *src,CynOS_U8 data, CynOS_U32 len, CynOS_U32 limit)
{
	len=(len>limit)?(limit):(len);
	memset(src,data,len);
	return len;
}


/*==============================================SOFTCRC================================================================*/




























