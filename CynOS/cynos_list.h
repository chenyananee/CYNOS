#ifndef __CYNOS_LIST_H
#define __CYNOS_LIST_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"

typedef struct __cynos_list
{
  struct  __cynos_list *next;
  struct  __cynos_list *last;
}CynOSList_Hanlde;



/*
    do
    {
        1.get the node
        2.do the usr logic
    }while(the next node is not null)
*/
#define CynOS_List_Foreach(__plisthead,__plistiterator_out)             \
{                                                                       \
    CynOSList_Hanlde **__listaddr =  (CynOSList_Hanlde **)(&__plistiterator_out);                 \
    *__listaddr = (CynOSList_Hanlde *)(__plisthead);                           \
    do                                                                      \
    {
    


#define CynOS_List_ForeachEnd(__plisthead)     \
        if((*__listaddr)->next) {*__listaddr = (*__listaddr)->next;}     \
    }while(((CynOSList_Hanlde *)(__plisthead) != (*__listaddr)) && ((*__listaddr)->next));  \
}

//break the loop when user need
#define CynOS_List_Iterator_Break break;

//init the list to loop mode
#define CynOS_List_Node_Init(plisthead)                                              \
CynOSList_Hanlde *__listiteratorforInit = (CynOSList_Hanlde *)(plisthead);      \
__listiteratorforInit->next = __listiteratorforInit->last = __listiteratorforInit;


extern int CynOSListInsert(void **head,void *insert,char flag);
extern int CynOSListDelete(void *head,void *rmnode);
extern void CynOSListToLoopMode(void *head);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

