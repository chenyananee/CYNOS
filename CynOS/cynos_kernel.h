#ifndef __OS_H
#define __OS_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"
#include "cynos_cfg.h"



#define CYNOS_KERNEL_DESC    "***************CYNOS***************"
#define CYNOS_KERNEL_VERSION "SV00.001"
#define CYNOS_KERNEL_DATE    "20200222"
#define CYNOS_KERNEL_BUILD_DATA  __DATE__
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
	void(*time_hook)(unsigned int time);
	void(*taskInit)(void);
	void(*task)(void *arg);
	void * prm;
	unsigned int task_tick;
	unsigned int task_tick_cnt;
	unsigned char task_id;
	unsigned char task_priority; //优先级未使用（防止优先调度使得低优先任务长时间无法执行）
	unsigned char task_event;
	CynOS_TASK_STA task_sta;
	
	void(*task_event_time_hook)(void);
	void(*task_event_pend_hook)(void);
	void(*task_event_resume_hook)(void);
	
}userTaskRun;



typedef struct
{
	unsigned char init_sta;
	
}cynos_status;


 

extern cynos_status gcynos_sta;



/*获取内核版本*/
extern unsigned char CynOS_Get_KernelVersion(void * out);  
/*获取内核日期*/
extern unsigned char CynOS_Get_KernelDate(void * out);     
/*获取内核编译日期*/
extern unsigned char CynOS_Get_KernelBuildDate(void * out);
/*获取内核编译时间*/
extern unsigned char CynOS_Get_KernelBuildTime(void * out);
	

/*系统初始化*/
extern void CynOS_Init(void);    
/*系统启动*/
extern void CynOsStart(void);
/*调度算法（保证每个任务都能执行，内核未使用，可对外提供排序算法）*/
extern void CynOsTaskSchedule(unsigned char*taskfifo,unsigned int size,unsigned char typesize);
/*挂起任务*/
extern void CynOS_PENDING(unsigned char taskid);
/*恢复任务*/
extern void CynOS_RESUM(unsigned char taskid);
/*注册系统级沟函数*/
extern void CynOS_Login_Hook(unsigned char taskid,CynOS_TASK_STA task_type,void(*eventhook)(void));
/*创建任务*/
extern unsigned char CynosTask_Creat(void(*time_hook)(unsigned int time),void(*taskInit)(void),void(*task)(void * arg),unsigned int tasktick);
/*删除任务*/
extern unsigned char CynosTask_Delete(unsigned char task_id);
/*系统异常*/
extern void CynOS_Assert(char asslv,char*head,void *arg);




/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

