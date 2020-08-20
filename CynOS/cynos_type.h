#ifndef __CYNOS_TYPE_H
#define __CYNOS_TYPE_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_cfg.h"


#define CynOS_MaybeUnused __attribute__((unused))
#define CynOS_MemAT(addr) __attribute__((at(addr)))


#define CynOSBIT0 0X01
#define CynOSBIT1 0X02
#define CynOSBIT2 0X04
#define CynOSBIT3 0X08
#define CynOSBIT4 0X10
#define CynOSBIT5 0X20
#define CynOSBIT6 0X40
#define CynOSBIT7 0X80


#if((CPU_LEN==8)||(CPU_LEN==16)||(CPU_LEN==32))
#define CPU_TYPE CPU_LEN
#else
#define CPU_TYPE 16
#endif


#if (CPU_TYPE==32)
#define CynOS_S8_MAX (0X7F)
#define CynOS_S16_MAX (0X7FFF)
#define CynOS_S32_MAX (0X7FFFFFFF)
#define CynOS_U8_MAX (0XFF)
#define CynOS_U16_MAX (0XFFFF)
#define CynOS_U32_MAX (0XFFFFFFFF)
#elif ((CPU_TYPE==8)||(CPU_TYPE==16))
#define CynOS_S8_MAX (0X7F)
#define CynOS_S16_MAX (0X7FFF)
#define CynOS_S32_MAX (0X7FFF)
#define CynOS_U8_MAX (0XFF)
#define CynOS_U16_MAX (0XFFFF)
#define CynOS_U32_MAX (0XFFFF)
#endif
#if (CPU_TYPE==32)
typedef void CynOS_VOID;
typedef unsigned char CynOS_U8;
typedef unsigned short CynOS_U16;
typedef unsigned int CynOS_U32;
typedef unsigned long long  CynOS_U64;
typedef signed char CynOS_S8;
typedef signed short CynOS_S16;
typedef signed int CynOS_S32;
typedef signed long long  CynOS_S64;
typedef float   CynOS_Float;
typedef double  CynOS_Double;
#elif ((CPU_TYPE==8)||(CPU_TYPE==16))
typedef unsigned char CynOS_U8;
typedef unsigned short CynOS_U16;
typedef unsigned int CynOS_U32;
typedef unsigned long long  CynOS_U64;
typedef signed char CynOS_S8;
typedef signed short CynOS_S16;
typedef signed int CynOS_S32;
typedef signed long long  CynOS_S64;	
typedef float   CynOS_Float;
typedef double  CynOS_Double;
#endif



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

