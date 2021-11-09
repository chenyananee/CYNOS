/*
Copyright © 2020 ChenYanan.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "cynos_list.h"

#if USE_CYNOS_LIST


//flag=1: pnode will be insert to plisthead->last
//flag=0: pnode will be insert to plisthead->next
int CynOSListInsert(void **head,void *insert,char flag)
{
  CynOSList_Hanlde *listhead = (CynOSList_Hanlde *)(*((CynOSList_Hanlde **)head));
  CynOSList_Hanlde *pnode = (CynOSList_Hanlde *)insert;
  CynOSList_Hanlde *iterator_index = listhead; 
  if((!(head)) || (!pnode)) return CYNOS_ERR_MEM;

  CynOS_List_Node_Init(pnode);
  if(!(listhead))
  {
    CynOSList_Hanlde **__listaddr =  (CynOSList_Hanlde **)(head);
    *__listaddr = pnode;
    return CYNOS_OK;
  }

  if(flag)
  {
    pnode->last = iterator_index->last;
    pnode->next = iterator_index;
    iterator_index->last = pnode;
    if(pnode->last)
    {
      pnode->last->next = pnode;
    }
  }
  else
  {
    pnode->next = iterator_index->next;
    pnode->last = iterator_index;
    iterator_index->next = pnode;
    if(pnode->next)
    {
        pnode->next->last = pnode;
    }
  }

  return CYNOS_OK;
}


int CynOSListDelete(void *head,void *rmnode)
{
    CynOSList_Hanlde *listhead = head;
    CynOSList_Hanlde *pnode = rmnode;
    if((!pnode)) return CYNOS_ERR_MEM;

    if(listhead == pnode)
    {
      if(listhead != listhead->next)
      {
        listhead = listhead->next;
      }
      else
      {
        listhead = 0;
      }
    }

    if(pnode->next)
    {
      pnode->next->last = pnode->last;
    }
    
    if(pnode->last)
    {
      pnode->last->next = pnode->next;
    }
    
    return CYNOS_OK;
}


void CynOSListToLoopMode(void *head)
{
    CynOSList_Hanlde *listFirst = 0,*listLast = 0;
    CynOSList_Hanlde *list;
    CynOS_List_Foreach(head,list)

    if((list->last == list) || (!list->last))
    {
      //this is first node in list
      listFirst = list;
    }

    if((list->next == list) || (!list->next))
    {
      //this is last node in list
      listLast = list;
    }

    CynOS_List_ForeachEnd(head)

    if(listFirst)
    {
      listFirst->last = listLast;
    }
    
    if(listFirst)
    {
      listLast->next = listFirst;
    } 
}

/*example*/
/*
typedef struct
{
   CynOSList_Hanlde list; //must be first
   int data;
}list_t;

list_t ttttt[10];
list_t *lhead=0; 

void app()
{

  for(int iii=0;iii<10;iii++)
   {
      CynOSListInsert((void **)(&lhead),&ttttt[iii],1);
      ttttt[iii].data = iii;
   }

   list_t *lout=0;
   CynOS_List_Foreach(lhead,lout)
   printf("\r\nlist[%08d]-val = %d",(unsigned int)lout,lout->data);
   CynOS_List_ForeachEnd(lhead)

}
*/
#endif

