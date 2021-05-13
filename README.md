# CynOS（轻量可裁剪伪操作系统）

___
> ***注：为提高系统资源利用率用户任务内避免阻塞，系统已提供一套简单的状态机编程模块***
___

## 特性
1. 占用少量资源，组件耦合低，可裁剪性强，移植简单

2. 方便裸机模块化编程

3. 提供系统模块常用框架

## 系统裁剪

1. 配置cynos_cfg.h文件即可
## 移植方法
1. 包含cynos.h文件
2. 在定时器中断内调用void CynOS_Systick_Handle(CynOS_U32 timebase)函数
3. 调用系统初始化函数CynOS_Init()
4. 在Cynos_UserTask_Init()函数内建立用户任务
5. 启动轮询调度
```
	sys_bsp_init(); //系统底层初始化函数等
	CynOS_Init();
	Cynos_UserTask_Init();
	CynOsStart();
```
## 移植DEMO
> 系统移植DEMO - 任务建立及状态机模块的使用示例（可查看demo.c）
```
//任务句柄
CynOSTask_Sta usertask1_handle;

void user_task_timehook(CynOS_U32 time)
{
	Cynos_TASK_SystickHandle(&usertask1_handle,time);
}

void user_task_init(void)
{
	Cynos_Task_Init(&usertask1_handle);
}

/*             
	状态机内通过usertask1_handle来实现状态的保存
	通过Cynos_TASK_Jump函数实现状态间的跳转，并且跳转时可设置调转时间，如跳转时间为1000ms时，状态会切换至delay状态等时间到达会自动由delay状态切换至目标状态，由此能够有效的提高CPU资源利用率，并且建议开发者在条件允许的情况下使用状态机编程。
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

void Cynos_UserTask_Init()
{
	CynosTask_Create(user_task_timehook, //任务可注册一个基础时钟模块
					 user_task_init,     //任务构造函数（用于初始化任务内所需要的资源）
					 0,				     //任务析构函数（用于任务删除时释放任务内的资源）
					 0,					 //任务参数
					 user_task,          //任务入口函数
					 1000);				 //任务运行周期
}

//主函数
int main(void)
{
	bsp_init();
	CynOS_Init();
	Cynos_UserTask_Init();
	CynOsStart();
}


```
## 重要函数功能介绍
| 函数名 | 功能 | 描述 |
| :------------ |:---------------:|:---------------:|
| CynOS_Init      | 系统内核初始化 | 初始化内核内存等 |
| Cynos_UserTask_Init | 用户任务初始化  | 用户在此函数内建立自己的应用任务 |
| CynOsStart 	| 系统启动	| 开启任务调度 |
| CynOS_Systick_Handle | 内核时基中断	| （*）为内核提供合适的系统时钟 |
## 配置文件介绍

### 模块开关
| 宏名 | 描述 |
| :------------ |:---------------:|
| CYNOS_CPU_LEN      | 系统位宽 |
| CYNOS_USER_TASK_MAX | 最大用户任务数  |
| CYNOS_SYSTICK_FRQ 	| 系统时基速度（产生一次中断的时间单位MS）	|
| CYNOS_TASK_SYSTICK_EN 	| 内核是否根据时间片调度	|
| CYNOS_TASK_TIME_HOOK_EN 	| 时间片钩函数	|
| CYNOS_TASK_PEND_HOOK_EN 	| 任务挂起钩函数	|
| CYNOS_TASK_RESUM_HOOK_EN 	| 任务恢复钩函数	|
| CYNOS_DEBUG_KERNEL_PRINT 	| 用户如果开启内核打印的功能需给此处给出打印接口	|
| USE_CYNOS_DEBUG 	| 调试模块开关	|
| USE_CYNOS_MUTEX 	| 互斥量模块开关	|
| USE_CYNOS_SEM 	| 信号量模块开关	|
| USE_CYNOS_FIFO 	| FIFO模块开关	|
| USE_CYNOS_EVENT | 事件功能开关	|

### 模块配置  
1. DEBUG 配置 

| 宏名 | 描述 |
| :------------ |:---------------:|
| CYNOS_DEBUG_SIZE | DEBUG 模块资源 |

2. FIFO 配置 

| 宏名 | 描述 |
| :------------ |:---------------:|
| CYNOS_FIFO_SIZE      | FIFO模块占用资源 |

3. MUTEX 配置  

| 宏名 | 描述 |
| :------------ |:---------------:|
| null      | null |

3. SEM 配置  

| 宏名 | 描述 |
| :------------ |:---------------:|
| null      | null |

3. EVENT 配置  

| 宏名 | 描述 |
| :--- | :--: |
| null | null |

