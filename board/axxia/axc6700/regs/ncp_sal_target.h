/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_target.h
    @brief     Include Target specific header file here.
*/


#ifndef __NCP_SAL_TARGET_H__
#define __NCP_SAL_TARGET_H__

/* 
 * Include the right target-processor type based on platform and 
 * the right processor as defined by -DPROC_<processor-name>
 */

#ifdef NCP_LINUX

#ifdef PROC_PPC476
#include "ncp_sal_linux-ppc476.h"
#define NCP_ARCH_PPC
#endif

#ifdef PROC_ARMA15
#include "ncp_sal_linux-arma15.h"
#define NCP_ARCH_ARM
#endif

#ifdef PROC_ARMA53
#include "ncp_sal_linux-arma53.h"
#define NCP_ARCH_ARM
#endif

#ifdef PROC_ARMA57
#include "ncp_sal_linux-arma57.h"
#define NCP_ARCH_ARM
#endif

#ifdef PROC_X86
#include "ncp_sal_linux-x86.h"
#define NCP_ARCH_X86
#endif

#ifdef PROC_X86_PLX64
#ifdef NCP_WRL_X86_64
#include "ncp_sal_wrl-x86_64.h"
#else
#include "ncp_sal_linux-x86_64.h"
#endif
#define NCP_ARCH_X86
#endif

#if defined(PROC_EP8572)
#include "ncp_sal_linux-ep8572.h"
#define NCP_ARCH_PPC
#endif

#ifdef PROC_EP8641
#include "ncp_sal_linux-ep8641.h"
#define NCP_ARCH_PPC
#endif

#ifdef PROC_EP4080
#include "ncp_sal_linux-ep4080.h"
#define NCP_ARCH_PPC
#endif

#ifdef PROC_EP5020
#include "ncp_sal_linux-ep5020.h"
#define NCP_ARCH_PPC
#endif

#ifdef PROC_PM750F
#include "ncp_sal_hhl-pmppc750f.h"
#define NCP_ARCH_PPC
#endif

#ifdef PROC_EP5020
#include "ncp_sal_linux-ep5020.h"
#define NCP_ARCH_PPC
#endif

#endif /* NCP_LINUX */

#ifdef WIN32 

#ifdef PROC_X86
#include "ncp_sal_mingw-w32.h"
#endif

#endif /* WIN32 */

#endif /* NCP_SAL_TARGET_H */
