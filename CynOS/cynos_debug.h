#ifndef __CYNOS_DEBUG_H
#define __CYNOS_DEBUG_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"




typedef struct
{
	CynOS_U32 debugsize;
	CynOS_U8  debug_buff[];
}CynOS_Debug_Handle;

extern void CynOS_Debug(void(write)(char*data,unsigned int len),char*head,char * format,...);
extern void CynOS_Print_Char(void(write)(char*data,unsigned int len),char * format,...);
extern void CynOS_Print_Hex(void(write)(char*data,unsigned int len),char * data,unsigned int len);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

