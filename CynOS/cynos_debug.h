#ifndef __CYNOS_DEBUG_H
#define __CYNOS_DEBUG_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"

extern void CynOS_Debug(void(write)(char*data,unsigned int len),char*head,char * format,...);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

