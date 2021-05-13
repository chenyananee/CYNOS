#ifndef __CYNOS_EVENT_H
#define __CYNOS_EVENT_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"



typedef struct
{
    CynOS_U8 evt_avlable;//0:unavlable or avlable
    CynOS_U16 id;
    CynOS_U16 evt_type;
    CynOS_U16 evt_cmd;
    CynOS_U16 evt_subcmd;
    CynOS_U16 evtDataSize;
    CynOS_VOID *evtData;
}CynosEventHandle;


CYNOS_STATUS Cynos_EventPost(CynosEventHandle *evtque_handle,CynOS_U16 quesize,CynosEventHandle *evt);
CYNOS_STATUS Cynos_EventReceive(CynosEventHandle *evtque_handle,CynOS_U16 quesize,CynOS_U16 *staticIndex,CynOS_U16 evtid,CynosEventHandle *evt);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

