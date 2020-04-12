#ifndef __CYNOS_CFG_H
#define __CYNOS_CFG_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//debug 



#ifndef USE_CYNOS
#define USE_CYNOS (1) //多系统共生选择
#endif



#define CPU_LEN             (16) //CPU位宽长度
#define USER_TASK_MAX        10 //最大用户任务数目
#define SYSTICK_FRQ          1  //ms（系统时钟周期ms）
#define OS_ASSERT_EN         1  //异常处理

#define TASK_SYSTICK_EN      1  //系统时间片调度
#define TASK_TIME_HOOK_EN    1  //时间片钩函数
#define TASK_PEND_HOOK_EN    1  //任务挂起钩函数
#define TASK_RESUM_HOOK_EN   1  //任务恢复钩函数


/*==========================系统组件裁剪=============================*/
/*调试配置*/
#define DEBUG_KERNEL_EN      0
#define DEBUG_KERNEL_PRINTF printf

#define USE_CYNOS_MUTEX      1
#define USE_CYNOS_SEM        1
#define USE_CYNOS_FIFO       0
#define USE_CYNOS_FIFO_EX    0  //可抢占队列（需使能队列）
/*调试配置*/
/*FIFO CFG*/
#if USE_CYNOS_FIFO
#define CYNOS_FIFO_SIZE      10 //队列大小（byte）
#if USE_CYNOS_FIFO_EX
#define CYNOS_FIFO_SIZE_EX   5  //抢占队列大小（byte）
#endif
#else
#define CYNOS_FIFO_SIZE      0 
#endif
/*MUTEX CFG*/
#if USE_CYNOS_MUTEX


#endif


/*SEM CFG*/
#if USE_CYNOS_SEM



#endif


#if OS_ASSERT_EN 
#define OS_ASSERT_HardFault  0  
#define OS_Warning_Assert    1  
#endif


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

