#ifndef __CYNOS_TIME_BASE_H
#define __CYNOS_TIME_BASE_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"




#define TIME_HOOK_MAX (USER_TASK_MAX)





typedef  void(*time_hook_fun)(unsigned int time);



extern char cynos_tim_base_login(void(*time_hook)(unsigned int time));
extern char cynos_tim_base_logout(void(*time_hook)(unsigned int time));
extern void cynos_time_run(unsigned int timebase);



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

