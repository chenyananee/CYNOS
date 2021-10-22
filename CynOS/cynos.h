#ifndef __CYNOS_H
#define __CYNOS_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_cfg.h"
#include "cynos_kernel.h"
#include "cynos_task.h"
#include "cynos_fsm.h"

#if USE_CYNOS_DEBUG
#include "cynos_debug.h"
#endif

#if USE_CYNOS_EVENT
#include "cynos_event.h"
#endif

#if USE_CYNOS_FIFO
#include "cynos_firo.h"
#endif

#if USE_CYNOS_LIST
#include "cynos_list.h"
#endif

#if USE_CYNOS_TIME
#include "cynos_time.h"
#endif



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

