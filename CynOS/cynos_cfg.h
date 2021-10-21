#ifndef __CYNOS_CFG_H
#define __CYNOS_CFG_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/*
    user include
*/



#ifndef USE_CYNOS
#define USE_CYNOS (1) 
#endif


#define CYNOS_CPU_LEN             (32) 
#define CYNOS_SYSTICK_FRQ          1  

/*=======================================================*/

#define USE_CYNOS_DEBUG      0
#define USE_CYNOS_EVENT      0
#define USE_CYNOS_FIFO       0
#define USE_CYNOS_LIST       0
#define USE_CYNOS_TIME       0

/*DEBUG CFG*/
#if USE_CYNOS_DEBUG
#define CYNOS_DEBUG_SIZE      1024 
#else
#define CYNOS_DEBUG_SIZE      1 
#endif

/*DEBUG CFG*/
#if USE_CYNOS_TIME
#define CYNOS_TIME_SIZE      10 
#else
#define CYNOS_TIME_SIZE      0 
#endif


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

