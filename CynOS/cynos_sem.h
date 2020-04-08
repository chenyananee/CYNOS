#ifndef __CYNOS_SEM_H
#define __CYNOS_SEM_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"


typedef struct cynos_sem
{
/*public方法*/
	CYNOS_STATUS(*post)(struct cynos_sem * mutex);
	CYNOS_STATUS(*pend)(struct cynos_sem * mutex);
	CYNOS_STATUS(*clear)(struct cynos_sem * mutex);
/*protect成员禁止直接访问*/	
	unsigned int sem_type;
	unsigned int sem_val;
}CynOS_Sem;

/*
0-1:二值信号量
>1: 多值信号量
*/
/*sem类初始化*/
CYNOS_STATUS CynOs_Sem_Init(CynOS_Sem * sem,unsigned int sem_type);





/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif



