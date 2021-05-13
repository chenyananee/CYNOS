#ifndef __CYNOS_CFG_H
#define __CYNOS_CFG_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif





#ifndef USE_CYNOS
#define USE_CYNOS (1) 
#endif




#define CYNOS_CPU_LEN             (32) 
#define CYNOS_USER_TASK_MAX        10   
#define CYNOS_TIME_MAX             (CYNOS_USER_TASK_MAX)
#define CYNOS_SYSTICK_FRQ          1  

#define CYNOS_TASK_SYSTICK_EN      1   
#define CYNOS_TASK_TIME_HOOK_EN    0   
#define CYNOS_TASK_PEND_HOOK_EN    0   
#define CYNOS_TASK_RESUM_HOOK_EN   0   
/*=======================================================*/
#define CYNOS_DEBUG_KERNEL_EN      1
#define CYNOS_DEBUG_KERNEL_PRINT printf

#define USE_CYNOS_DEBUG      0
#define USE_CYNOS_MUTEX      0
#define USE_CYNOS_SEM        0
#define USE_CYNOS_FIFO       0
#define USE_CYNOS_EVENT      1
/*DEBUG CFG*/
#if USE_CYNOS_DEBUG
#define CYNOS_DEBUG_SIZE      1024 
#else
#define CYNOS_DEBUG_SIZE      0 
#endif

/*FIFO CFG*/
#if USE_CYNOS_FIFO
#define CYNOS_FIFO_SIZE      10 
#if USE_CYNOS_FIFO_EX
#define CYNOS_FIFO_SIZE_EX   5  
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

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

