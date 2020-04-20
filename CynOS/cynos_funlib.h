#ifndef __CYNOS_FUNLIB_H
#define __CYNOS_FUNLIB_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"


extern CynOS_U32 CynOS_Mem_Cpy (void *dst, void *src, CynOS_U32 len, CynOS_U32 limit);
extern CynOS_U32 CynOS_Mem_Set (void *src,CynOS_U8 data, CynOS_U32 len, CynOS_U32 limit);

	
extern CynOS_U32 CynOS_CheckSum (CynOS_U32 init,CynOS_VOID *data, CynOS_U32 len);
	

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

