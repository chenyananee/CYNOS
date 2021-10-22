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

//define a kernel obj, name is ui and the max task number is 5
CREATE_KERNEL_OBJ(ui,5)
/*
	//and also you can create other kernel obj for the same time
	CREATE_KERNEL_OBJ(key,5)
	CREATE_KERNEL_OBJ(motor,5)
	CREATE_KERNEL_OBJ(sensor,5)
*/

/**
 * @description: timer interrupt for 1ms
 * @param {*}
 * @return {*}
 */
void timer_interrupt()
{
	 CynOS_KernelObj_Tick(CYNOS_KEROBJ(ui),1);
}

void user_bsp_init(void)
{
	//TODO do some bsp init,such like clk_init,gpio_init,or uart_init...
}

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void user_task_init(void)
{
	user_bsp_init();
}
/**
 * @description: 
 * @param {void} *
 * @return {*}
 */
void user_task(void *id)
{
	
}

/**
 * @description: the usertask will be run for every secend
 * @param {*}
 * @return {*}
 */
int appmain(void)
{
	CynOS_KernelObj_Init(CYNOS_KEROBJ(ui),5,0);
    CynOS_Kernel_Task_Create(CYNOS_KEROBJ(ui),user_task_init,user_task,1000);
	/*
	CynOS_Kernel_Task_Create(CYNOS_KEROBJ(key),key_task_init,user_task,10);
	CynOS_Kernel_Task_Create(CYNOS_KEROBJ(motor),motor_task_init,user_task,50);
	CynOS_Kernel_Task_Create(CYNOS_KEROBJ(sensor),sensor_task_init,user_task,2000);
	*/
	CynOS_Start(CYNOS_KEROBJ(ui),KERNEL_RUN_FOREVER);
	return 0;
}






