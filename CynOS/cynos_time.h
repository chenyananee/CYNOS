#ifndef __CYNOS_TIME_BASE_H
#define __CYNOS_TIME_BASE_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_cfg.h"
#include "cynos_base.h"

#define CYNOS_TIME_RUN 0X55

typedef struct
{
	struct
	{
		CynOS_U8 avl_flag       : 1;
        CynOS_U8 status_flag    : 2;
	}time_flag;

    CynOS_U8 id;
	CynOSPointFun cb_entry;
	
	CynOS_U32  time_cnt;
	CynOS_U32  frq;
}CynOSTime;


typedef struct
{
    CynOS_U8 init;
	CynOS_U8 timeNum;
	CynOSTime time[];
}CynOS_TimeHandle;

/*
	create the time
	__N: handle name
	__S: task's num
*/
#define CREATE_TIME_OBJ(__N,__S) \
CynOS_U8 __N ## TIM_MEM[sizeof(CynOS_TimeHandle)+sizeof(CynOSTime)*__S];\
CynOS_TimeHandle *CynOSTime ## __N = (CynOS_TimeHandle *)__N ## TIM_MEM;

/*
	get thetime's handle
*/
#define CYNOS_TME(N) CynOSTime ## N

extern void CynOS_Time_Init(void);
extern CYNOS_STATUS CynOS_Time_Login(CynOS_U8 id,CynOS_U32 tick,CynOSPointFun cb);
extern CYNOS_STATUS CynOS_Time_Logout(CynOS_U8 id);
extern CYNOS_STATUS CynOS_Time_Stop(CynOS_U8 id);
extern CYNOS_STATUS CynOS_Time_Start(CynOS_U8 id);
extern void CynOS_Time_TickInterrupt(CynOS_U32 timebase);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

