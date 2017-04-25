/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_types.h
    @brief     OS Specific types are located here. 
*/


#ifndef __NCP_SAL_TYPES_H__
#define __NCP_SAL_TYPES_H__

/* #include "ncp_sal_target.h" */

#ifndef SWIG

#ifdef __cplusplus
extern "C"
{
#endif /* #ifdef __cplusplus */

/**************************************************************************
* Platform Dependent Type Definitions
**************************************************************************/

#ifdef NCP_LINUX

/* #include "ncp_sal_types_linux.h" */

#endif /* NCP_LINUX */

#ifdef WIN32

/* #include "ncp_sal_types_mingw.h" */

#endif /* WIN32 */

#ifndef NULL
#define NULL    0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#define NCP_S8        ncp_int8_t
#define NCP_S16       ncp_int16_t
#define NCP_S32       ncp_int32_t
#define NCP_S64       ncp_int64_t
#define NCP_U8        ncp_uint8_t
#define NCP_U16       ncp_uint16_t
#define NCP_U32       ncp_uint32_t
#define NCP_U64       ncp_uint64_t
#define NCP_BOOL      ncp_bool_t

#else

    /*
%header
%{
#include "ncp_sal.h"
#include "ncp_sal_types.h"
%}
*/

NCPTCL_SETUP();

    typedef unsigned char      ncp_uint8_t;
    typedef unsigned short     ncp_uint16_t;
    typedef unsigned int       ncp_uint32_t;

    typedef unsigned char      ncp_bool_t;

    typedef unsigned char **   ncp_uint8p_t;

%inline
%{
NCPTCL_REF(ncp_st_t);
NCPTCL_REF(ncp_bool_t);
NCPTCL_REF(ncp_uint8_t);
NCPTCL_REF_ARY(ncp_uint8_t);
NCPTCL_REF(ncp_uint16_t);
NCPTCL_REF_ARY(ncp_uint16_t);
NCPTCL_REF(ncp_uint32_t);
NCPTCL_REF_ARY(ncp_uint32_t);
NCPTCL_REF_DETAIL(char*,p_char,void,,);
%}

#endif /* #ifndef SWIG */


#ifdef SWIG
NCPTCL_WO_EXCEPTIONS();
#endif /* #ifdef SWIG */


#ifndef SWIG
#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */
#endif /* #ifndef SWIG */

#endif /* NCP_SAL_TYPES_H */
