#ifndef __CYNOS_FIFO_H
#define __CYNOS_FIFO_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_cfg.h"
#include "cynos_base.h"



/*
class cynfifo_os
{
	public:
		

};

*/




typedef struct
{
	unsigned short fifo_r;
	unsigned short fifo_w;
}fifo_arg;


typedef struct cynfifo_os
{
/*public方法*/	
/*所有方法第一个参数为模拟的this指针*/
	CYNOS_STATUS(*push)(struct cynfifo_os * fifo,unsigned char * data);	    //指定普通队列成员入队
	CYNOS_STATUS(*pop)(struct cynfifo_os * fifo,unsigned char * data);		//指定普通队列成员出队
	CYNOS_STATUS(*push_ex)(struct cynfifo_os * fifo,unsigned char * data);  //指定抢占队列成员入队
	CYNOS_STATUS(*pop_ex)(struct cynfifo_os * fifo,unsigned char * data);   //指定抢占队列成员出队
	CYNOS_STATUS(*get)(struct cynfifo_os * fifo,unsigned char * data);      //get方法优先获取抢占队列内的数据
/*protect成员禁止直接访问*/
	unsigned char fifo[CYNOS_FIFO_SIZE];
	fifo_arg fifo_sta;
#if USE_CYNOS_FIFO_EX	
	unsigned char fifo_ex[CYNOS_FIFO_SIZE_EX];
	fifo_arg fifo_ex_sta;
#endif
}CynOS_FIFO;

/*fifo类初始化*/
void CynOS_FIFO_Init(CynOS_FIFO * fifo);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif



