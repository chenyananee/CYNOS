#ifndef __CYNOS_BITVARYING_H
#define __CYNOS_BITVARYING_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_cfg.h"
#include "cynos_base.h"



typedef struct
{
	CynOS_U16 buff_size;
	CynOS_U32 bit_size;
	CynOS_U8 * bitstring;
}CynOSBitVarying_Handle;

extern void CynOS_BitVarying_Init(CynOSBitVarying_Handle *handle,CynOS_U8 *buff,CynOS_U16 buffsize);
extern CYNOS_STATUS CynOS_BitVarying_Write(CynOSBitVarying_Handle *handle,CynOS_U16 index,CynOS_U8 data);
extern CynOS_U8 CynOS_BitVarying_Read(CynOSBitVarying_Handle *handle,CynOS_U16 index);
extern CYNOS_STATUS CynOS_BitVarying_Get(CynOSBitVarying_Handle *handle,CynOS_U16 index,CynOS_U8 * out,CynOS_U16 bitsize);
extern CynOS_U8 CynOS_BitVarying_Check(CynOSBitVarying_Handle *handle,CynOS_U16 bitsize,CynOS_U8 data);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif



