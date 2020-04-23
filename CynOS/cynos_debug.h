#ifndef __CYNOS_DEBUG_H
#define __CYNOS_DEBUG_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"



typedef struct
{
	CynOS_U8 debug_en;
	void(*write)(char*data,unsigned int len);
}CynOS_Debug_Cfg;
	
typedef struct
{
	CynOS_U32 debugsize;
	CynOS_U8  debug_buff[];
}CynOS_Debug_Handle;


extern void CynOS_Debug_Init(void(*write)(char*data,unsigned int len));
extern void CynOS_Debug(char*head,char * format,...);
extern void CynOS_Print_Char(char * format,...);
extern void CynOS_Print_Hex(char * data,unsigned int len);
extern void CynOS_Debug_Open(void);
extern void CynOS_Debug_Close(void);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

