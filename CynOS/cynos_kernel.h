#ifndef __OS_H
#define __OS_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"
#include "cynos_cfg.h"
#include "cynos_task.h"


#define CYNOS_KERNEL_DESC    "***************CYNOS***************"
#define CYNOS_KERNEL_VERSION "SV03.000"
#define CYNOS_KERNEL_DATE    "20210909"
#define CYNOS_KERNEL_BUILD_DATE  __DATE__
#define CYNOS_KERNEL_BUILD_TIME  __TIME__

#define CYNOS_KERNEL_RUN 	0X10
#define CYNOS_KERNEL_STOP 	0X20
#define CYNOS_KERNEL_RESET 	0X30

typedef struct
{
	CynOS_U32 task_id;
	struct
	{
		CynOS_U8 init_flag : 1;
	}obj_flag;
	CynOS_U8 kernelstatus;
	CynOS_U8 tasknum;
	CynOSTaskHandle task[];
}CynOS_ObjHandle;


/*
	create the kernel object
	__N: handle name
	__S: task's num
*/
#define CREATE_KERNEL_OBJ(__N,__S) \
CynOS_U8 __N ## OBJ_MEM[sizeof(CynOS_ObjHandle)+sizeof(CynOSTaskHandle)*__S];\
CynOS_ObjHandle *KernelObj_ ## __N = (CynOS_ObjHandle *)__N ## OBJ_MEM;
/*
	get the kernel object's handle
*/
#define CYNOS_KEROBJ(N) KernelObj_##N
/*----------------------------------Kernel Info-------------------------------------*/

/*
	start the kernel obj
*/
extern CynOS_VOID CynOS_Start(CynOS_ObjHandle *obj,CynOS_U32 run_cnt);

/*
	the kernel obj init
*/
extern CYNOS_STATUS CynOS_KernelObj_Init(CynOS_ObjHandle *obj,CynOS_U8 max_task,CynOSVoidFun init_fun);

/*
	the kernel obj's tick interrupt, it must be run in the time interrupt
*/
extern CynOS_VOID CynOS_KernelObj_Tick(CynOS_ObjHandle *obj,CynOS_U32 tick);

/*
	create a task with the kernel obj
*/
extern CYNOS_STATUS CynOS_Kernel_Task_Create(CynOS_ObjHandle *obj,
									  CynOSVoidFun init_fun,
									  CynOSVoidFun entry,
									  CynOS_U32 tick);
/*
	set the kernel obj's status like: run , stop or reset
*/
extern CynOS_VOID CynOS_KernelObj_Set_Status(CynOS_ObjHandle *obj,CynOS_U32 status);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

