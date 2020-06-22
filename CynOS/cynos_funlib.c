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
/*
*********************************************************************************************************
* 函数名称: CynOS_Mem_Cmp
*
* 函数说明: 内存比较
*
* 入口参数:
*
* 返回参数: 0x55：内存内容一致
*
* 特殊说明:
*********************************************************************************************************
*/
CynOS_U8 CynOS_Mem_Cmp (void *dst,void *src,CynOS_U32 len,CynOS_U32 limit)
{
	CynOS_U32 index = 0;
	
	len=(len>limit)?(limit):(len);
	CynOS_U8 *pdest=dst, *psrc=src;
	for (index = 0; index < len;index++)
	{
		if(pdest[index]!=psrc[index])
			return 0;
	}
		return 0x55;
}
/*
*********************************************************************************************************
* 函数名称: CynOS_Mem_LB_Change
*
* 函数说明: 大小端内存交换
*
* 入口参数:
*
* 返回参数: 
*
* 特殊说明:
*********************************************************************************************************
*/
CynOS_U8 CynOS_Mem_LB_Change(CynOS_U8 *data,CynOS_U16 len)
{
	CynOS_U8 tempdata=0;
	CynOS_U16 index=0,num=len/2;
	
	
	if(num>1)
	{
		for(index=0;index<num;index++)
		{
			tempdata = data[index];
			data[index] = data[len-index-1];
			data[len-index-1] = tempdata;
		}
	}
	return 0;
}

/*==============================================SOFTCRC================================================================*/
/*
*********************************************************************************************************
* 函数名称: CynOS_CheckSum
*
* 函数说明: 和校验
*
* 入口参数:
*
* 返回参数: 拷贝长度
*
* 特殊说明:
*********************************************************************************************************
*/
CynOS_U32 CynOS_CheckSum (CynOS_U32 init,CynOS_VOID *data, CynOS_U32 len)
{
	CynOS_U32 index=0;
	CynOS_U8 * pdata=data;
	for(index=0;index<len;index++)
	{
		init+=pdata[index];
	}
	return init;
}

/*==============================================DATA================================================================*/
/*********************************************************************************************************
* 函数名称: CynOS_Loop_Add
*
* 函数说明: 循环递增
*
* 入口参数:
*
* 返回参数: 拷贝长度
*
* 特殊说明:
*********************************************************************************************************
*/
CynOS_U64 CynOS_Loop_Add(CynOS_U64 dst,CynOS_U64 step, CynOS_U64 start,CynOS_U64 stop)
{
	CynOS_U64 tempdata = dst;
	
	tempdata += step;
	if(tempdata>stop)
	{
		tempdata = start;
	}
	return tempdata;
}
/*---------------------------------------------------------------------
  Function Name: BcdConvH_Single
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
CynOS_U8 CynOS_BcdConvH_Single(CynOS_U8  bcdtemp)
{
	return (((bcdtemp >> 4) & 0x0F) * 10 + (bcdtemp & 0x0F));
}
/*---------------------------------------------------------------------
  Function Name: HConvBcd_Single
  Description:   
  Inputs:        
  Returns:       
-----------------------------------------------------------------------*/
CynOS_U8 CynOS_HConvBcd_Single(CynOS_U8  hextemp)
{
	CynOS_U8 result_temp;
	result_temp = hextemp / 10;
	result_temp <<= 4;
	result_temp += hextemp % 10;
	return (result_temp);
}


/*==============================================calendar================================================================*/
static CynOS_U32 sMontoMin[12] = {44640, 28, 44640, 43200, 44640, 43200, 44640, 44640, 43200, 44640, 43200, 44640};

/*------------------------------------------------------------------------
 Procedure:     CynOS_CalendarClock
 Purpose:       年月日时分秒，转换为世纪分
 Input:
 Output:
 Errors:
------------------------------------------------------------------------*/
CynOS_U32 CynOS_CalendarClock(CynOS_U8 *pTime)
{
    CynOS_U32 iii = 0, centuryMin = 0;
	CynOS_U32 wYear = 2000 + pTime[5];
    if((wYear & 0x03) == 0)
        sMontoMin[1] = 41760;
    else
        sMontoMin[1] = 40320;

    if(wYear > 11000)
	{
		wYear = 11000;
	}

    for(iii = 1970; iii < wYear; iii++)
    {
        if((iii & 0x03) == 0)
            centuryMin += 527040; //366*24*60
        else
            centuryMin += 525600; //365*24*60
    }

    for(iii = 1; iii < pTime[4]; iii++)
    {
        centuryMin += sMontoMin[iii - 1];
    }
    centuryMin += (CynOS_U32)(pTime[3] - 1) * 1440;
    centuryMin += (CynOS_U32)pTime[2] * 60;
    centuryMin += (CynOS_U32)pTime[1];
    return(centuryMin);
}

/*------------------------------------------------------------------------
 Procedure:     CynOS_SystemClock
 Purpose:       世纪分，转换为年月日时分
 Input:
 Output:
 Errors:
------------------------------------------------------------------------*/
void  CynOS_SystemClock(CynOS_U32 centuryMin, CynOS_U8 *pTime)
{
    CynOS_U32	j, t;

    for(t = 1970; t < 11000; t++)
    {
        if((t & 0x03) == 0)
        {
            j = 527040;		//366*24*60
        }
        else
        {
            j = 525600;		//365*24*60
        }
        if(centuryMin >= j)
        {
            centuryMin -= j;
        }
        else
        {
            pTime[5] = (unsigned short)t;
            break;
        }
    }

	if((centuryMin & 0x03) == 0)
	{
		sMontoMin[1] = 41760;
	}
	else
	{
		sMontoMin[1] = 40320;
	}
	for(t = 0; t < 12; t++)
	{
		if(centuryMin >= sMontoMin[t])
		{
			centuryMin -= sMontoMin[t];
		}
		else
		{
			pTime[4] = (BYTE)(t + 1);
			break;
		}
	}

	pTime[3] = (CynOS_U8)(centuryMin / 1440 + 1);
	centuryMin = centuryMin % 1440;

	pTime[2] = (CynOS_U8)(centuryMin / 60);
	pTime[1] = (CynOS_U8)(centuryMin % 60);
}
/*---------------------------------------------------------------------
  Function Name: CynOS_GetWeekSn
  Description:   
  Inputs:        weekType 0:1-6-0,1:1-7
  Returns:       
-----------------------------------------------------------------------*/
CynOS_U8 CynOS_GetWeekSn(CynOS_U8 weekType, CynOS_U8 * pTime)
{
	CynOS_U32	centuryMin = CynOS_CalendarClock(pTime);
	if (weekType == 1)
	{
		centuryMin -= 4*24*60;
		centuryMin /= 1440;
		return (centuryMin%7+1);
	}
	else
	{
		centuryMin -= 3*24*60;
		centuryMin /= 1440;
		return (centuryMin%7);
	}
}













