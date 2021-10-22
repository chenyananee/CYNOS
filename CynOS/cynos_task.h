#ifndef __CYNOS_TASK_H
#define __CYNOS_TASK_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"
#include "cynos_fsm.h"


typedef struct
{
	FSM_SC_Handle fsm;     //must be 1st
	struct
	{
		CynOS_U8 avl_flag : 1;
		CynOS_U8 init_flag  : 1;
	}task_flag;

	CynOSVoidFun init;
	CynOSPointFun task_entry;

	CynOS_U8 id;

	CynOS_U32  task_time_cnt;
	CynOS_U32  task_frq;
}CynOSTaskHandle;
extern CYNOS_STATUS CynOS_TaskHandleInit(CynOSTaskHandle *taskhandle,CynOSVoidFun init_fun,CynOSPointFun entry,CynOS_U32 tick);
extern CynOS_VOID Cynos_TASK_SystickHandle(CynOSTaskHandle * handle,CynOS_U32 tick);
extern CynOS_VOID Cynos_TASK_Delay(CynOSTaskHandle * handle);
extern CynOS_U8 Cynos_GetTask_Step(CynOSTaskHandle * handle);
extern CynOS_VOID Cynos_TASK_Jump(CynOSTaskHandle * handle,CynOS_U32 next_step,CynOS_U32 wait_time);



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

