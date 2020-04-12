#ifndef __CYNOS_H
#define __CYNOS_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_cfg.h"
#ifndef USE_CYNOS_MUTEX
#define CYNOS_MUTEX_EN  0
#else
#define CYNOS_MUTEX_EN  USE_CYNOS_MUTEX
#endif
#ifndef USE_CYNOS_FIFO
#define CYNOS_FIFO_EN  0
#else
#define CYNOS_FIFO_EN  USE_CYNOS_FIFO
#endif
#ifndef USE_CYNOS_SEM
#define CYNOS_SEM_EN  0
#else
#define CYNOS_SEM_EN  USE_CYNOS_SEM
#endif
#ifndef USE_CYNOS_SLOT
#define CYNOS_SLOT_EN  0
#else
#define CYNOS_SLOT_EN  USE_CYNOS_SLOT
#endif



#include "cynos_kernel.h"
#include "cynos_time.h"
#include "cynos_task.h"

#if CYNOS_MUTEX_EN
#include "cynos_mutex.h"
#endif
#if CYNOS_FIFO_EN
#include "cynos_fifo.h"
#endif
#if CYNOS_SEM_EN
#include "cynos_sem.h"
#endif

#if CYNOS_SLOT_EN
#include "cynos_slot.h"
#endif


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

