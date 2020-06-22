#ifndef __CYNOS_FUNLIB_H
#define __CYNOS_FUNLIB_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"


extern CynOS_U32 CynOS_Mem_Cpy (void *dst, void *src, CynOS_U32 len, CynOS_U32 limit);
extern CynOS_U32 CynOS_Mem_Set (void *src,CynOS_U8 data, CynOS_U32 len, CynOS_U32 limit);
extern CynOS_U8 CynOS_Mem_Cmp(void *dst, void *src, CynOS_U32 len,CynOS_U32 limit);
extern CynOS_U8 CynOS_Mem_LB_Change(CynOS_U8 *data, CynOS_U16 len);

extern CynOS_U32 CynOS_CheckSum (CynOS_U32 init,CynOS_VOID *data, CynOS_U32 len);
extern CynOS_U64 CynOS_Loop_Add(CynOS_U64 dst,CynOS_U64 step, CynOS_U64 start,CynOS_U64 stop);

extern CynOS_U8 CynOS_BcdConvH_Single(CynOS_U8  bcdtemp);
extern CynOS_U8 CynOS_HConvBcd_Single(CynOS_U8  hextemp);
extern CynOS_U32 CynOS_CalendarClock(CynOS_U8 *pTime);
extern void  CynOS_SystemClock(CynOS_U32 centuryMin, CynOS_U8 *pTime);
extern CynOS_U8 CynOS_GetWeekSn(CynOS_U8 weekType, CynOS_U8 * pTime);


extern CynOS_U16 BitMAP_GetAvlNum(CynOS_U8 *bitmap,CynOS_U16 size);
extern CynOS_U16 BitMAP_GetNAvlNum(CynOS_U8 *bitmap,CynOS_U16 size);
extern CynOS_U16 BitMAP_GetFirstBIT(CynOS_U8 *bitmap,CynOS_U16 size,CynOS_U8 bittype);
extern CynOS_U16 BitMAP_GetBitIndex(CynOS_U8 *bitmap,CynOS_U16 size,CynOS_U8 bittype,CynOS_U16 bit_num);
extern CynOS_U8  BitMAP_GetBitStatus(CynOS_U8 *bitmap,CynOS_U16 size,CynOS_U16 index);
extern CynOS_U8  BitMAP_WriteBitStatus(CynOS_U8 *bitmap,CynOS_U16 size,CynOS_U16 index,CynOS_U8 bitsta);


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

