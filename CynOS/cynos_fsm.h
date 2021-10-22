#ifndef __CYNOS_FSM_H
#define __CYNOS_FSM_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"


/* fsm for switch/case begin*/

#define CynOSTask_FLOW_IDLE 0X0
#define CynOSTask_FLOW_DELAY 0xFF

typedef struct 
{
    CynOS_U8 _task_current_flow;
	CynOS_U8 _task_next_flow;
	CynOS_U32 delay_cnt;
	CynOS_U32 delay;
}CynOSFSM_SC_Handle;

/* fsm for switch/case end*/




/* fsm for status begin*/

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
        .info.last = __last, \
        .info.current = __current, \
        .info.next = __next,

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
/* fsm for status end*/


extern CynOS_VOID Cynos_Fsm_Jump(CynOSFsm_Handle *fsm,int newstatus);
extern CynOS_VOID Cynos_Fsm_Goback(CynOSFsm_Handle *fsm);

extern CynOS_VOID Cynos_FsmSC_Jump(CynOS_VOID *scFsm,CynOS_U8 next_step,CynOS_U32 wait_time);
extern CynOS_VOID Cynos_FsmSC_TimeHook(CynOS_VOID *scFsm,CynOS_U32 tick);
extern CynOS_VOID Cynos_FsmSC_Wait(CynOS_VOID *scFsm);
extern CynOS_U8 Cynos_FsmSC_GetStep(CynOS_VOID *scFsm);
/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

