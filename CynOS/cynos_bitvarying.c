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
#include "cynos_fifo.h"
#include "cynos_bitvarying.h"




void CynOS_BitVarying_Init(CynOSBitVarying_Handle *handle,CynOS_U8 *buff,CynOS_U16 buffsize)
{
	handle->buff_size = buffsize;
	handle->bit_size = buffsize*8;
	handle->bitstring = buff;
	CynOS_Mem_Set(buff,0,buffsize,buffsize);
}

CYNOS_STATUS CynOS_BitVarying_Write(CynOSBitVarying_Handle *handle,CynOS_U16 index,CynOS_U8 data)
{
	if(data)
	{
		handle->bitstring[index/8] |= (1<<(index%8));
		return CYNOS_OK;
	}
	else
	{
		handle->bitstring[index/8] &= ~(1<<(index%8));
		return CYNOS_OK;
	}	
}


CynOS_U8 CynOS_BitVarying_Read(CynOSBitVarying_Handle *handle,CynOS_U16 index)
{
	return (handle->bitstring[index/8] >> (index%8))&0x01;
}



CynOS_U8 CynOS_BitVarying_Check(CynOSBitVarying_Handle *handle,CynOS_U16 bitsize,CynOS_U8 data)
{

	CynOS_U32 sum=0,rel=0;;
	sum = bitsize/8;
	rel = bitsize%8;
	
	for(CynOS_U16 iii =0;iii<sum;iii++)
	{
		if(data) //ур1
		{
			if(handle->bitstring[iii])
			{
				return 0x55;
			}
			
		}
		else     //ур0
		{
			if((handle->bitstring[iii] & 0xff) != 0xff)
			{
				return 0x55;
			}
		}
	}
	if(rel)
	{
		if(data) //ур1
		{
			if(handle->bitstring[sum] & (0xff>>(8-rel)))
			{
				return 0x55;
			}
		}
		else     //ур0
		{
			if((handle->bitstring[sum] & (0xff>>(8-rel))) != (0xff>>(8-rel)))
			{
				return 0x55;
			}
		}
	}
	
	return 0;
}


CYNOS_STATUS CynOS_BitVarying_Get(CynOSBitVarying_Handle *handle,CynOS_U16 index,CynOS_U8 * out,CynOS_U16 bitsize)
{
	CynOS_U8 res=0;
	CynOS_U32 cnt=0,sum=0,dest_bit_cnt=0,dest_byte_cnt=0,avl_cnt=0;
	sum = handle->buff_size;
	for(CynOS_U16 iii =0;iii<sum;iii++)
	{
		for(CynOS_U8 jjj =0;jjj<8;jjj++)
		{
			res = ((handle->bitstring[iii]>>jjj)&0x01);
			if((cnt >= index)&&(avl_cnt<bitsize))
			{
				out[dest_byte_cnt] |= (res<<dest_bit_cnt);
				avl_cnt++;
				dest_bit_cnt++;
				if(dest_bit_cnt>=8)
				{
					dest_bit_cnt=0;
					dest_byte_cnt++;
				}
			}
			cnt++;
		}
	}
	
	return CYNOS_OK;
}














