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

/*fifo底层操作*/
CYNOS_STATUS pop(unsigned char *fifo,unsigned char *data,fifo_arg *arg,unsigned short size)
{	
	unsigned short index=0;
	if(arg->fifo_r != arg->fifo_w)
	{
		index = arg->fifo_r;
		arg->fifo_r++;
		if(	arg->fifo_r>=size)
		{
			arg->fifo_r=0;
		}
		*data=fifo[index];
		return CYNOS_OK;
	}
	return CYNOS_ERR;
}

CYNOS_STATUS push(unsigned char *fifo,unsigned char data,fifo_arg *arg,unsigned short size)
{	
	unsigned short index=0;
	index = arg->fifo_w+1;
	if(index>=size)
	{
		index=0;
	}
	if(arg->fifo_r != index)
	{
		fifo[arg->fifo_w]=data;
		arg->fifo_w=index;
		return CYNOS_OK;
	}
	else
	{
		return CYNOS_ERR;
	}
}

CYNOS_STATUS fifo_push(CynOS_FIFO * fifo,unsigned char * data)
{	
	return push(fifo->fifo,*data,&fifo->fifo_sta,CYNOS_FIFO_SIZE);
}

CYNOS_STATUS fifo_pop(CynOS_FIFO * fifo,unsigned char * data)
{	
	return pop(fifo->fifo,data,&fifo->fifo_sta,CYNOS_FIFO_SIZE);
}

CYNOS_STATUS fifo_push_ex(CynOS_FIFO * fifo,unsigned char * data)
{	
	return push(fifo->fifo_ex,*data,&fifo->fifo_ex_sta,CYNOS_FIFO_SIZE_EX);
}

CYNOS_STATUS fifo_pop_ex(CynOS_FIFO * fifo,unsigned char * data)
{	
	return pop(fifo->fifo_ex,data,&fifo->fifo_ex_sta,CYNOS_FIFO_SIZE_EX);
}

CYNOS_STATUS fifo_get(CynOS_FIFO * fifo,unsigned char * data)
{	
	#if USE_CYNOS_FIFO_EX	
	if(fifo->fifo_ex_sta.fifo_w!=fifo->fifo_ex_sta.fifo_r)
	{
		return fifo_pop_ex(fifo,data);
	}
	else
	#endif
	{
		return fifo_pop(fifo,data);
	}
}

/*fifo类初始化*/
void CynOS_FIFO_Init(CynOS_FIFO * fifo)
{
	memset(&fifo->fifo_sta,0,sizeof(fifo_arg));
	memset(&fifo->fifo,0,CYNOS_FIFO_SIZE);
#if USE_CYNOS_FIFO_EX
	memset(&fifo->fifo_ex_sta,0,sizeof(fifo_arg));	
	memset(&fifo->fifo_ex,0,CYNOS_FIFO_SIZE_EX);	
#endif
	fifo->pop=fifo_pop;
	fifo->pop_ex=fifo_pop_ex;
	fifo->push=fifo_push;
	fifo->push_ex=fifo_push_ex;
	fifo->get=fifo_get;
}

/*
//使用实例

CynOS_FIFO testfifo;
void fifo_test(void)
{
	unsigned char t[10]={1,2,3,4,5,6,7,8,9};
	unsigned char e[10]={0};
	
	CynOS_FIFO_Init(&testfifo);
	
	for(char iii=0 ;iii<10;iii++)
	{
		testfifo.push(&testfifo,&t[iii]);
	}
	testfifo.push_ex(&testfifo,&t[8]);
	
	for(char iii=0 ;iii<10;iii++)
	{
		testfifo.get(&testfifo,&e[iii]);
	}
}	

*/








