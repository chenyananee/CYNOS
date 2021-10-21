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
## 移植方法（可具体查看demo.c）
1. 包含cynos.h文件
2. 创建一个内核对象如：CREATE_KERNEL_OBJ(ui,5)  //创建了一个ui的内核对象，该对象内可以创建5个任务
3. 在定时器中断系统中调用 CynOS_KernelObj_Tick(CYNOS_KEROBJ(ui),1);  //为ui内核对象提供时钟
4. 初始化内核对象    CynOS_KernelObj_Init(CYNOS_KEROBJ(ui),5,0);
5. 创建任务               CynOS_Kernel_Task_Create(CYNOS_KEROBJ(ui),user_task_init,user_task,1000); //创建一个user_task的任务 该任务的出初始化函数为user_task_init 并且该任务没1000ms运行一次
6. 开始任务调度       CynOS_Start(CYNOS_KEROBJ(ui),KERNEL_RUN_FOREVER);  //启动ui内核对象的线程调度 



## 移植DEMO
> 系统移植DEMO - 任务建立及状态机模块的使用示例（可查看demo.c）


## 配置文件介绍

### 模块开关
| 宏名 | 描述 |
| :------------ |:---------------:|
| CYNOS_CPU_LEN      | 系统位宽 |
| ~~CYNOS_USER_TASK_MAX~~ | ~~最大用户任务数~~ |
| CYNOS_SYSTICK_FRQ 	| 系统时基速度（产生一次中断的时间单位MS）	|
| ~~CYNOS_TASK_SYSTICK_EN~~ | ~~内核是否根据时间片调度~~	|
| ~~CYNOS_TASK_TIME_HOOK_EN~~ | ~~时间片钩函数~~	|
| ~~CYNOS_TASK_PEND_HOOK_EN~~ | ~~任务挂起钩函数~~	|
| ~~CYNOS_TASK_RESUM_HOOK_EN~~ | ~~任务恢复钩函数~~	|
| ~~CYNOS_DEBUG_KERNEL_PRINT~~ | ~~用户如果开启内核打印的功能需给此处给出打印接口~~	|
| USE_CYNOS_DEBUG 	| 调试模块开关	|
| ~~USE_CYNOS_MUTEX~~ | ~~互斥量模块开关~~	|
| ~~USE_CYNOS_SEM~~ | ~~信号量模块开关~~	|
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

