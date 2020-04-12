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


extern void Cynos_Task_Init(CynOSTask_Sta * cynostask_sta);

extern void Cynos_TASK_Jump(CynOSTask_Sta * cynostask_sta,CynOSTask_FLOW next_step,unsigned int wait_time);

extern void Cynos_TASK_Delay(CynOSTask_Sta * cynostask_sta);

extern void Cynos_TASK_SystickHandle(CynOSTask_Sta * cynostask_sta,unsigned int time);

extern CynOS_U8 Cynos_GetTask_Step(CynOSTask_Sta * cynostask_sta);

extern void Cynos_UserTask_Init(void);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

