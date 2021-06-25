#ifndef __CYNOS_LIST_H
#define __CYNOS_LIST_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"

typedef char (*__listfun)(void *arg);

typedef struct 
{
    __listfun entry;
    __listfun exit;
}_ListFunc;


typedef struct __cynos_list
{
  struct  __cynos_list *next;
  struct  __cynos_list *last;
  _ListFunc func; 

}CynOSList_Hanlde;

/*
    do
    {
        1.get the node
        2.do the usr logic
    }while(the next node is not null)
*/
#define CynOS_List_Iterator_Begin(plisthead,pnode)  \
CynOSList_Hanlde *iterator_index = plisthead;       \
do                                                  \
{                                                   \
    pnode = iterator_index;                         \
    iterator_index = iterator_index->next           \
}


#define CynOS_List_Iterator_End while(iterator_index != CynOS_NULL)

#define CynOS_List_Iterator_Break break;

#define CynOS_List_Init(plisthead) \
plisthead->next = plisthead->last = CynOS_NULL;

//TODO 
#define CynOS_List_Add(plisthead,pnode) \
CynOSList_Hanlde *iterator_index = plisthead;       \
CynOS_List_Init(pnode);                             \
if(iterator_index == CynOS_NULL)                    \
plisthead = pnode;                                  \


}

#define CynOS_List_Remove(pnode) \



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

