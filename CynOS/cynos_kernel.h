#ifndef __OS_H
#define __OS_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"
#include "cynos_cfg.h"



#define CYNOS_KERNEL_DESC    "***************CYNOS***************"
#define CYNOS_KERNEL_VERSION "SV00.002"
#define CYNOS_KERNEL_DATE    "20200222"
#define CYNOS_KERNEL_BUILD_DATE  __DATE__
#define CYNOS_KERNEL_BUILD_TIME  __TIME__


typedef enum
{
	CynOS_TASK_EVENT_NULL=0,
	CynOS_TASK_EVENT_RUN=0X01,
	CynOS_TASK_EVENT_TIME=0X02,
	CynOS_TASK_EVENT_PEND=0X04,
	CynOS_TASK_EVENT_RESUM=0X08,
}CynOS_TASK_STA;


typedef struct
{
	void(*time_hook)(CynOS_U32 time);
	void(*taskConstructor)(void);
	void(*taskDestructor)(void);
	void(*task)(void *arg);
	void * arg;
	CynOS_U32 task_tick;
	CynOS_U32 task_tick_cnt;
	CynOS_U8 task_id;
	CynOS_U8 task_event;
	CynOS_TASK_STA task_sta;
#if CYNOS_TASK_TIME_HOOK_EN
	void(*task_event_time_hook)(void);
#endif
#if CYNOS_TASK_PEND_HOOK_EN
    void(*task_event_pend_hook)(void);
#endif
#if CYNOS_TASK_RESUM_HOOK_EN
    void(*task_event_resume_hook)(void);
#endif

}CynOS_UserTask_Info_Handle;



typedef struct
{
	CynOS_U8 init_sta;
	CynOS_U32 task_id;
}CynOS_Run_Status;


 

extern CynOS_Run_Status gcynos_sta;



/*----------------------------------Kernel Info-------------------------------------*/
extern CynOS_U8 CynOS_Get_KernelVersion(void * out);  

extern CynOS_U8 CynOS_Get_KernelDate(void * out);     

extern CynOS_U8 CynOS_Get_KernelBuildDate(void * out);

extern CynOS_U8 CynOS_Get_KernelBuildTime(void * out);


/*----------------------------------Task Info-------------------------------------*/
extern void CynOS_Init(void);    

extern void CynOsStart(void);

extern CynOS_U32 CynOS_Get_Task_ID(void);

extern CYNOS_STATUS CynOS_Get_Task_Info(CynOS_U32 task_id,CynOS_UserTask_Info_Handle * task_info);

extern void CynOS_PENDING(CynOS_U8 taskid);

extern void CynOS_RESUM(CynOS_U8 taskid);

extern void CynOS_Login_Hook(CynOS_U8 taskid,CynOS_TASK_STA task_type,void(*eventhook)(void));

extern CynOS_U8 CynosTask_Create(void(*time_hook)(CynOS_U32 time),void(*Constructor)(void),void(*Destructor)(void),void(*task)(void * arg),CynOS_U32 tasktick);

extern CynOS_U8 CynosTask_Delete(CynOS_U8 task_id);

extern void CynOS_Assert(char asslv,char*head,char*format,...);




/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

