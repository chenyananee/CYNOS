/*
Copyright ? 2020 ChenYanan.

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
CynOS_U16 CynOS_CRC16X25(CynOS_U8 *data, CynOS_U32 datalen)
{
	CynOS_U8 i;
	CynOS_U16 crc = 0xffff;	// Initial value
	while(datalen--)
	{
		crc ^= *data++;	    // crc ^= *data; data++;
		for (i = 0; i < 8; ++i)
		{
			if (crc & 1)
				crc = (crc >> 1) ^ 0x8408;	// 0x8408 = reverse 0x1021
			else
				crc = (crc >> 1);
		}
	}
	return ~crc;
}
/*==============================================DATA================================================================*/
/*********************************************************************************************************
* 函数名称: CynOS_Average
*
* 函数说明: get Average
*
* 入口参数:
*
* 返回参数: 
*
* 特殊说明:
*********************************************************************************************************
*/
CynOS_Float CynOS_Average(CynOS_S16 *array1,CynOS_U16 len)
{
	CynOS_Double sum=0;
	CynOS_U16 index;
	for(index=0;index<len;index++)
	{
		sum += array1[index];
	}
	if(len)
	{
		return (sum/len);
	}
	else
	{
		return 0;
	}    
}
/*********************************************************************************************************
* 函数名称: CynOS_Pearson
*
* 函数说明: 计算曲线相似度
*
* 入口参数:
*
* 返回参数: 
*
* 特殊说明:
*********************************************************************************************************
*/
CynOS_Float CynOS_Pearson(CynOS_S16 *array1,CynOS_S16 *array2, CynOS_U16 len)
{
	CynOS_Float ra = CynOS_Average(array1,len);
    CynOS_Float rb= CynOS_Average(array2,len);
	CynOS_U16 index;
	
    CynOS_Double s = 0, r1 = 0,r2 = 0;
	
    for (index = 0; index < len; index++) 
	{
        s += (array1[index] - ra) * (array2[index] - rb);
        r1 += pow(array1[index] - ra, 2);
        r2 += pow(array2[index] - rb, 2);
    }
	
	r1 = sqrt(r1 * r2);
	s = (r1 == 0) ? 1 : s / r1;
    return s;
}
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
static CynOS_U32 sMonToMin[12] = {44640, 28, 44640, 43200, 44640, 43200, 44640, 44640, 43200, 44640, 43200, 44640};

/*------------------------------------------------------------------------
 Procedure:     CynOS_CalendarClock
 Purpose:       年月日时分秒，转换为世纪分
 Input:
 Output:
 Errors:
------------------------------------------------------------------------*/
void CynOS_CalendarClock(CynOS_U32 secend,pCynOS_VCALCLOCK pTime)
{
    unsigned long	j, t;

	pTime->bySecond = secend % 60;
	secend = secend / 60;
	
    j = secend / 1440 + 1; /*总天数*/
    j %= 7;
    j += 3; /*1970.1.1 星期4*/
	#ifdef __RTC_WEEK1TO7__
    if (j > 7) j -= 7;
	#else
    if (j >= 7) j -= 7;
	#endif
 	pTime->byWeek = j;
    for(t = 1970; t < 11000; t++)
    {
        if((t & 0x03) == 0)
            j = 527040;			//366*24*60
        else
            j = 525600;    //365*24*60
        if(secend >= j)
            secend -= j;
        else
        {
            pTime->wYear = (unsigned short)t;
            break;
        }
    }

    if((pTime->wYear & 0x03) == 0)
        sMonToMin[1] = 41760;
    else
        sMonToMin[1] = 40320;
    for(t = 0; t < 12; t++)
    {
        if(secend >= sMonToMin[t]) //24*60;
            secend -= sMonToMin[t];
        else
        {
            pTime->byMonth = (unsigned char)(t + 1);
            break;
        }
    }

    pTime->byDay = (unsigned char)(secend / 1440 + 1);
    secend = secend % 1440;

    pTime->byHour = (unsigned char)(secend / 60);
    pTime->byMinute = (unsigned char)(secend % 60);
}

/*------------------------------------------------------------------------
 Procedure:     CynOS_SystemClock
 Purpose:       世纪分，转换为年月日时分
 Input:
 Output:
 Errors:
------------------------------------------------------------------------*/
CynOS_U32 CynOS_SystemClock(pCynOS_VCALCLOCK pTime)
{
   CynOS_U32 i = 0, t;

    if((pTime->wYear & 0x03) == 0)
        sMonToMin[1] = 41760;
    else
        sMonToMin[1] = 40320;

    if(pTime->wYear > 11000)  pTime->wYear = 11000;

    for(t = 1970; t < pTime->wYear; t++)
    {
        if((t & 0x03) == 0)
            i += 527040; //366*24*60
        else
            i += 525600; //365*24*60
    }

    for(t = 1; t < pTime->byMonth; t++)
        i += sMonToMin[t - 1]; //24*60;
    i += (CynOS_U32)(pTime->byDay - 1) * 1440; //24*60;
    i += (CynOS_U32)pTime->byHour * 60; //60;
    i += (CynOS_U32)pTime->byMinute;
	i *= (CynOS_U32)60;
    i += (CynOS_U32)pTime->bySecond;
    return(i);
}






/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
void CynOS_BitStringWrite(CynOS_U8 * bitstring,CynOS_U32 index,CynOS_U8 status)
{
	if(status)
	{
		bitstring[index/8] |= (1<<(index%8));
	}
	else
	{
		bitstring[index/8] &= ~(1<<(index%8));
	}	
}

/****************************************************************
*FUNCTION NAME: BitStringRead
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
CynOS_U8 CynOS_BitStringRead(CynOS_U8 * bitstring,CynOS_U32 index)
{
	return (bitstring[index/8] >> (index%8))&0x01;
}
/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
CynOS_U8 _bitmr(CynOS_U8 * source,CynOS_U8 step,CynOS_U32 u8size)
{
	CynOS_U8 data_temp=0,pre_data,res=0x99;
	
	if(step>8)
	{
		return res;
	}
	
	if(step == 0)
	{
		return 0;
	}
	
	for(CynOS_U32 iii=0;iii<u8size;iii++)
	{
		
		if(iii == (u8size - 1))
		{
			pre_data = 0;
		}
		else
		{
			pre_data = source[u8size-iii-2];
		}	
		
		
		data_temp = source[u8size-iii-1];
		data_temp >>= step;
		pre_data <<= (8-step);
		data_temp |= pre_data;
		source[u8size-iii-1] = data_temp;
	}
	return 0x55;
}

/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
CynOS_U8 _bitml(CynOS_U8 * source,CynOS_U8 step,CynOS_U32 u8size)
{
	CynOS_U8 data_temp=0,next_data,res=0x99;
	
	if(step>8)
	{
		return res;
	}
	
	if(step == 0)
	{
		return 0;
	}
	
	for(CynOS_U32 iii=0;iii<u8size;iii++)
	{
		
			if(iii == (u8size - 1))
			{
				next_data = 0;
			}
			else
			{
				next_data = source[iii+1];
			}	
			
			
			data_temp = source[iii];
			data_temp <<= step;
			next_data >>= (8-step);
			data_temp |= next_data;
			source[iii] = data_temp;
	}
	return 0x55;
}

/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
CynOS_U8 CynOS_BitStringMR(CynOS_U8 * source,CynOS_U32 step,CynOS_U32 u8size)
{
	CynOS_U8 bit_step,byte_data;
	CynOS_U32 byte_step;
	
	bit_step = step%8;
	byte_step = step/8;
	
	if(ceil(step*1.0/8)>u8size)
	{
		return 0x99;
	}
	
	
	if(byte_step)
	{
		//数组字节移动
		for(CynOS_U32 iii=u8size;iii>0;iii--)
		{
			if(iii>byte_step)
			{
				byte_data = source[iii-1-byte_step];
			}
			else
			{
				byte_data=0;
			}
			
			source[iii-1] = byte_data;
		}
	}
	//数组位移动
	if(bit_step)
	{
		_bitmr(source,bit_step,u8size);
	}
	return 0;
}

/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/

CynOS_U32 CynOS_BitStringCount(CynOS_U8 * source,CynOS_U8 status,CynOS_U32 u8size)
{
	CynOS_U8 mask,cnt;
	CynOS_U32 num = 0;
	mask = (status)?(0xff):(0);
	
	//for(CynOS_U32 iii=0;iii<u8size;iii++)
	{
		switch (mask)
		{
			case 0:
				//num of 0
				for(CynOS_U32 iii=0;iii<u8size;iii++)
				{
					if(source[iii])
					{
						for(cnt=0;cnt<8;cnt++)
						{
							if(!((source[iii]>>cnt)&0x01))
							{
								num++;
							}
						}
					}
					else
					{
						num += 8;
					}
				}
				break;
			case 0xff:
				// num of 1
				for(CynOS_U32 iii=0;iii<u8size;iii++)
				{
					if(source[iii] != 0xff)
					{
						for(cnt=0;cnt<8;cnt++)
						{
							if((source[iii]>>cnt)&0x01)
							{
								num++;
							}
						}
					}
					else
					{
						num += 8;
					}
				}
				break;
		}
	}
	return num;
}
/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
CynOS_U8 CynOS_BitStringML(CynOS_U8 * source,CynOS_U32 step,CynOS_U32 u8size)
{
	CynOS_U8 bit_step,byte_data;
	CynOS_U32 byte_step;
	
	bit_step = step%8;
	byte_step = step/8;
	
	if(ceil(step*1.0/8)>u8size)
	{
		return 0x99;
	}
	
	
	if(byte_step)
	{
		//数组字节移动
		for(CynOS_U32 iii=0;iii<u8size;iii++)
		{
			if((iii+byte_step) < u8size)
			{
				byte_data = source[iii+byte_step];
			}
			else
			{
				byte_data=0;
			}
			
			source[iii] = byte_data;
		}
	}
	//数组位移动
	if(bit_step)
	{
		_bitml(source,bit_step,u8size);
	}
	
	return 0;
}
/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
CynOS_U8 CynOS_BitStringOR(CynOS_U8 * dest,CynOS_U8 * source,CynOS_U32 u8size)
{
	for(CynOS_U32 iii=0;iii<u8size;iii++)
	{
		dest[iii] |= source[iii];
	}
	
	return 0;
}
/****************************************************************
*FUNCTION NAME: AppCCOTask_Comm_Init
*DESCRIPTION:  
*INPUT: 
*OUTPUT: 
*RETURN: 
*GLOBAL:  
*NOTE:     
*MODIFY        DATE        VERSION        AUTHOR         REASON
=================================================================
****************************************************************/
CynOS_U8 CynOS_BitStringAND(CynOS_U8 * dest,CynOS_U8 * source,CynOS_U32 u8size)
{
	for(CynOS_U32 iii=0;iii<u8size;iii++)
	{
		dest[iii] &= source[iii];
	}
	return 0;
}









