#ifndef __CYNOS_TASK_H
#define __CYNOS_TASK_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"

typedef enum
{
	CynOSTask_FLOW_IDLE=0X10,
	CynOSTask_FLOW_STEP_1,
	CynOSTask_FLOW_STEP_2,
	CynOSTask_FLOW_STEP_3,
	CynOSTask_FLOW_STEP_4,
	CynOSTask_FLOW_STEP_5,
	CynOSTask_FLOW_STEP_6,
	CynOSTask_FLOW_STEP_7,
	CynOSTask_FLOW_STEP_8,
	CynOSTask_FLOW_STEP_9,
	CynOSTask_FLOW_STEP_A,
	CynOSTask_FLOW_STEP_B,
	CynOSTask_FLOW_STEP_C,
	CynOSTask_FLOW_STEP_D,
	CynOSTask_FLOW_STEP_E,
	CynOSTask_FLOW_STEP_F,
	CynOSTask_FLOW_DELAY,
}CynOSTask_FLOW;


typedef struct
{
	unsigned int  _time_cnt;
	unsigned int  _wait_time;
	CynOS_U8 _init_flag;
	CynOS_U8 _task_flow;
	CynOS_U8 _task_next_flow;
}CynOSTask_Sta;

/*
	任务运行状态操作接口
*/

//状态初始化（状态机初始为IDLE状态）
extern void Cynos_Task_Init(CynOSTask_Sta * cynostask_sta);
//状态跳转函数
extern void Cynos_TASK_Jump(CynOSTask_Sta * cynostask_sta,CynOSTask_FLOW next_step,unsigned int wait_time);
//延时自动跳转函数
extern void Cynos_TASK_Delay(CynOSTask_Sta * cynostask_sta);
//任务时基
extern void Cynos_TASK_SystickHandle(CynOSTask_Sta * cynostask_sta,unsigned int time);
//获取当前状态机状态
extern CynOS_U8 Cynos_GetTask_Step(CynOSTask_Sta * cynostask_sta);


//用户任务初始化（创建用户任务入口）
extern void Cynos_UserTask_Init(void);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

