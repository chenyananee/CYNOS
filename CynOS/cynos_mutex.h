#ifndef __CYNOS_MUTEX_H
#define __CYNOS_MUTEX_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"

typedef enum
{
	CynOS_Mutex_LOCK=0X28,
	CynOS_Mutex_UNLOCK,
	CynOS_Mutex_ERR,
}CynOS_Mutex_STA;


typedef struct cynos_mutex
{
/*public*/	
	CYNOS_STATUS(*lock)(struct cynos_mutex * mutex,CynOS_U32 process_id);
	CYNOS_STATUS(*unlock)(struct cynos_mutex * mutex,CynOS_U32 process_id);
	CYNOS_STATUS(*get)(struct cynos_mutex * mutex,CynOS_U32 process_id);
/*protect*/
	CynOS_Mutex_STA mutex_val;
	CynOS_U32 process_id;
}CynOS_Mutex;


CYNOS_STATUS CynOs_Mutex_Init(CynOS_Mutex * mutex);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

