/*
Copyright © 2020 ChenYanan.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "cynos.h"

/**
 * @description: timer interrupt for 1ms
 * @param {*}
 * @return {*}
 */
void timer_interrupt()
{
	CynOS_Systick_Handle(1);
}

void bsp_init(void)
{
	//TODO do some bsp init,such like clk_init,gpio_init,or uart_init...
}

CynOSTask_Sta usertask1_handle;
/**
 * @description: 
 * @param {CynOS_U32} time
 * @return {*}
 */
void user_task_timehook(CynOS_U32 time)
{
	Cynos_TASK_SystickHandle(&usertask1_handle,time);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void user_task_init(void)
{
	Cynos_Task_Init(&usertask1_handle);
}
/**
 * @description: 
 * @param {void} *
 * @return {*}
 */
void user_task(void * arg)
{
	switch(Cynos_GetTask_Step(&usertask1_handle))
	{
		case CynOSTask_FLOW_IDLE:
			Cynos_TASK_Jump(&usertask1_handle,CynOSTask_FLOW_STEP_1,0);
			break;
		case CynOSTask_FLOW_STEP_1:
			Cynos_TASK_Jump(&usertask1_handle,CynOSTask_FLOW_STEP_2,0);
			break;
		case CynOSTask_FLOW_STEP_2:
			Cynos_TASK_Jump(&usertask1_handle,CynOSTask_FLOW_IDLE,0);
			break;
		case CynOSTask_FLOW_DELAY:
			Cynos_TASK_Delay(&usertask1_handle);
			break;
		default:
			Cynos_TASK_Jump(&usertask1_handle,CynOSTask_FLOW_IDLE,0);
			break;
	}
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void Cynos_UserTask_Init()
{
	CynosTask_Create(user_task_timehook, //任务可注册一个基础时钟模块
					 user_task_init,     //任务构造函数（用于初始化任务内所需要的资源）
					 0,				     //任务析构函数（用于任务删除时释放任务内的资源）
					 0,					 //任务参数
					 user_task,          //任务入口函数
					 1000);				 //任务运行周期
}

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
int main(void)
{
	bsp_init();
	CynOS_Init();
	Cynos_UserTask_Init();
	CynOsStart();
}






