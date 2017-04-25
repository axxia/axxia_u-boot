/********************************************************
 ********************************************************/ 
#ifndef _NCP_MAIN_H_
#define _NCP_MAIN_H_

#include <common.h>
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"

/*#define DEBUG_PRINTS 1*/

#define FIXED_BUFFER_POOL     31
#define SHARED_BUFFER_POOL2   2

/* MACRO for conditional printing. Used only for "success" case prints...*/
#if DEBUG_PRINTS
#define SMART_PRINT(...) printf(__VA_ARGS__)
#else
#define SMART_PRINT(...)
#endif

extern ncp_hdl_t inNcpHdl;
extern void invokeAllTests(int*, int, int);

/*Define API Inputs*/
const char          *TestCaseDescription;
char                apiName[128];
unsigned char       useNcpHdl;
ncp_st_t            expRetval;

#endif /*_NCP_MAIN_H_*/
