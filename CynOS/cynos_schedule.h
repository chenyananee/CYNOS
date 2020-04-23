#ifndef __CYNOS_Schedule_H
#define __CYNOS_Schedule_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_cfg.h"
#include "cynos_base.h"


typedef struct cynos_schedule_handle
{
//public
	CYNOS_STATUS(*schedule_append)(struct cynos_schedule_handle *handle,CynOS_U32 id);
	CYNOS_STATUS(*schedule_delete)(struct cynos_schedule_handle *handle,CynOS_U32 id);
	CYNOS_STATUS(*schedule_get)(struct cynos_schedule_handle *handle,CynOS_U32 id);
//private
	CynOS_U32 schedule_fifo_size;
	CynOS_U32 schedule_len;
	CynOS_U32 schedule_fifo[];
}CynOS_Schedule_Handle;



CYNOS_STATUS CynOS_Schedule_Init(CynOS_Schedule_Handle * schedule_fifo,CynOS_U32 fifo_size);




/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif



