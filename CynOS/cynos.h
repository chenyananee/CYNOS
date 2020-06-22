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
#ifndef USE_CYNOS_DEBUG
#define CYNOS_SLOT_EN  0
#else
#define CYNOS_DEBUG_EN  USE_CYNOS_DEBUG
#endif
#ifndef USE_CYNOS_SCHEDULE
#define CYNOS_SCHEDULE_EN  0
#else
#define CYNOS_SCHEDULE_EN  USE_CYNOS_SCHEDULE
#endif

#ifndef USE_CYNOS_BITVARYING
#define CYNOS_BITVARYING_EN  0
#else
#define CYNOS_BITVARYING_EN  USE_CYNOS_BITVARYING
#endif

#include "cynos_task.h"
#include "cynos_kernel.h"
#include "cynos_time.h"



#if CYNOS_DEBUG_EN
#include "cynos_debug.h"
#endif
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

#if CYNOS_SCHEDULE_EN
#include "cynos_schedule.h"
#endif

#if CYNOS_BITVARYING_EN
#include "cynos_bitvarying.h"
#endif

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

