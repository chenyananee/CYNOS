#ifndef __CYNOS_TIME_BASE_H
#define __CYNOS_TIME_BASE_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"




#define TIME_HOOK_MAX (USER_TASK_MAX)





typedef  void(*time_hook_fun)(CynOS_U32 time);



extern char CynOS_Tim_Base_Login(void(*time_hook)(CynOS_U32 time));
extern char CynOS_tim_base_logout(void(*time_hook)(CynOS_U32 time));
extern void CynOS_Systick_Handle(CynOS_U32 timebase);



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

