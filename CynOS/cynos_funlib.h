#ifndef __CYNOS_FUNLIB_H
#define __CYNOS_FUNLIB_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"

/* 两种不同的时钟格式 */
#define CynOS_CALCLOCK    0   /* Broken-down time 年月日时分秒毫秒 */
#define CynOS_SYSCLOCK    1   /* Calendar time 秒,毫秒 */

/*----------------------公共类定义----------------------------*/
/*日历时钟*/
typedef struct _tagVSysClock
{
    unsigned short wYear;		/*19XX-20XX*/
    unsigned char byMonth;		/*1-12*/
    unsigned char byDay;			/*1-31*/
    unsigned char byWeek;		/*0-6  from sunday*/
    unsigned char byHour;		/*0-23*/
    unsigned char byMinute;	/*0-59*/
    unsigned char bySecond;	/*0-59*/
    unsigned short wMSecond;	/*0-999*/
}CynOS_VCALCLOCK,*pCynOS_VCALCLOCK;

/*世纪秒及毫秒*/
typedef struct _tagVCalClock
{
    unsigned long dwSecond;	/* 世纪秒*/
    unsigned short wMSecond;	/* 毫秒*/
}CynOS_VSYSCLOCK,*pCynOS_VSYSCLOCK;

/*BCD码日期&时间*/
typedef struct _tagDateTimeType
{	
	unsigned char Time[3];	/*hhnnss*/
	unsigned char Date[4];	/*yymmddww*/
}CynOS_DATETIMETYPE,*pCynOS_DATETIMETYPE;






extern CynOS_U32 CynOS_Mem_Cpy (void *dst, void *src, CynOS_U32 len, CynOS_U32 limit);
extern CynOS_U32 CynOS_Mem_Set (void *src,CynOS_U8 data, CynOS_U32 len, CynOS_U32 limit);
extern CynOS_U8 CynOS_Mem_Cmp(void *dst, void *src, CynOS_U32 len,CynOS_U32 limit);
extern CynOS_U8 CynOS_Mem_LB_Change(CynOS_U8 *data, CynOS_U16 len);

extern CynOS_U32 CynOS_CheckSum (CynOS_U32 init,CynOS_VOID *data, CynOS_U32 len);
extern CynOS_U16 CynOS_CRC16X25(CynOS_U8 *data, CynOS_U32 datalen);
extern CynOS_U64 CynOS_Loop_Add(CynOS_U64 dst,CynOS_U64 step, CynOS_U64 start,CynOS_U64 stop);

extern CynOS_U8 CynOS_BcdConvH_Single(CynOS_U8  bcdtemp);
extern CynOS_U8 CynOS_HConvBcd_Single(CynOS_U8  hextemp);

extern void CynOS_CalendarClock(CynOS_U32 secend,pCynOS_VCALCLOCK pTime);
extern CynOS_U32 CynOS_SystemClock(pCynOS_VCALCLOCK pTime);

extern CynOS_U8 CynOS_BitStringAND(CynOS_U8 * dest,CynOS_U8 * source,CynOS_U32 u8size);
extern CynOS_U8 CynOS_BitStringOR(CynOS_U8 * dest,CynOS_U8 * source,CynOS_U32 u8size);
extern CynOS_U8 CynOS_BitStringML(CynOS_U8 * source,CynOS_U32 step,CynOS_U32 u8size);
extern CynOS_U32 CynOS_BitStringCount(CynOS_U8 * source,CynOS_U8 status,CynOS_U32 u8size);
extern CynOS_U8 CynOS_BitStringMR(CynOS_U8 * source,CynOS_U32 step,CynOS_U32 u8size);
extern CynOS_U8 CynOS_BitStringRead(CynOS_U8 * bitstring,CynOS_U32 index);
extern void CynOS_BitStringWrite(CynOS_U8 * bitstring,CynOS_U32 index,CynOS_U8 status);





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

