#ifndef __CYNOS_BASE_H
#define __CYNOS_BASE_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include "cynos_type.h"
#include "cynos_funlib.h"







	typedef enum
	{

		CYNOS_OK = 0,
		CYNOS_READY,
		CYNOS_ERR,
		CYNOS_TIMEOUT,
		CYNOS_BUSY,
		CYNOS_ERR_MEM,
		CYNOS_ERR_ARG,
	} CYNOS_STATUS;


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

