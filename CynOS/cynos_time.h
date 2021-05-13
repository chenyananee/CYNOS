#ifndef __CYNOS_TIME_BASE_H
#define __CYNOS_TIME_BASE_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"




#define TIME_HOOK_MAX (CYNOS_TIME_MAX+1)


typedef  void(*time_hook_fun)(CynOS_U32 time);
typedef struct
{
    CynOS_U8 enable;
    CynOS_U32 time_cnt;
}CynOS_EventTimeHandle;



extern CYNOS_STATUS CynOS_Tim_Base_Login(void(*time_hook)(CynOS_U32 time));
extern CYNOS_STATUS CynOS_Tim_Base_Logout(void(*time_hook)(CynOS_U32 time));
extern void CynOS_Systick_Handle(CynOS_U32 timebase);



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

