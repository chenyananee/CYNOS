#ifndef __CYNOS_FSM_H
#define __CYNOS_FSM_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"


typedef void (*_fsm_fun)(void *handle);



typedef struct 
{
    _fsm_fun entry;
    _fsm_fun exit;
    _fsm_fun poll;
    _fsm_fun event;
}_FsmFunc;


typedef struct 
{
    int last;
    int current;
    int next;
}_FsmInfo;

typedef struct _CynOSFsm_Handle
{
    _FsmInfo info;
    _FsmFunc func[];
}CynOSFsm_Handle;

#define CYNOS_FSM_NAME(__name) CynOSFsm ## __name
#define CYNOS_FSM_INIT_BEGIN(__name)  CynOSFsm_Handle CYNOS_FSM_NAME(__name)={


#define CYNOS_FSM_INFO_INIT(__last,__current,__next) \
        .info.last = 0, \
        .info.current = 0, \
        .info.next = 0,

#define CYNOS_FSM_FUNC_INIT(__map_list)       \
        .func = { __map_list } 

#define CYNOS_FSM_FUNC_MAP(__entry,__exit,__poll,__event) \
            {                            \
                .entry = __entry,   \
                .exit = __exit,     \
                .poll = __poll,     \
                .event = __event,   \
            },                          
         
        


#define CYNOS_FSM_INIT_END };

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

