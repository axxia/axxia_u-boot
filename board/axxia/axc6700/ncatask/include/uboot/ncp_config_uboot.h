/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_config.h
 *  @brief     Configuration Management
 * 
 *  @addtogroup _config_ Configuration Management
 * 
 *  @{
 */


#ifndef __NCP_CONFIG_UBOOT_H__
#define __NCP_CONFIG_UBOOT_H__

#include "uboot/ncp.h"
/* #include "uboot/ncp_dev_pvt.h" */


/**************************************************************************/
/* Constants & Type Definitions                                           */
/**************************************************************************/


/**************************************************************************/
/* APIs                                                                   */
/**************************************************************************/


NCP_API ncp_st_t
ncp_config_uboot_attach( ncp_uint32_t id,
                   ncp_hdl_t *ncpHdl);

NCP_API ncp_st_t
ncp_config_uboot_deatach(ncp_hdl_t *ncpHdl);

#endif /* __NCP_CONFIG_UBOOT_H__ */
