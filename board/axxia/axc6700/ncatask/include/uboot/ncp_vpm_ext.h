/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_VPM_EXT_H_
#define _NCP_VPM_EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "uboot/ncp_pvt.h"
/* #include "uboot/ncp_cow_ext.h" */


typedef enum ncp_vp_param_format_e {
    ncp_vp_param_format_legacy = 0,
    ncp_vp_param_format_classification,
    ncp_vp_param_format_egress,
    ncp_vp_param_format_multicast,
    ncp_vp_param_format_learning_notification
} ncp_vp_param_format_t;


#ifndef NCP_KERNEL

/*!
 * @fn ncp_st_t ncp_vpm_config(ncp_t     *ncp,
 *                             ncp_map_t *map)
 * @brief Configure VPM module at config load time.
 * @param ncp:  NCP API state handle.
 * @param map: map pointing to ACP3->VirtualPipelines element.
 */

NCP_API ncp_st_t
ncp_vpm_config(ncp_t     *ncp,
               ncp_map_t *map);

/*!
 * @fn ncp_st_t ncp_vpm_warm_restart(ncp_t     *ncp)
 * @brief Configure VPM module at warm restart time.
 * @param ncp:  NCP API state handle.
 */

NCP_API ncp_st_t
ncp_vpm_warm_restart(ncp_t *ncp);

/*!
 * @fn ncp_st_t ncp_vpm_destroy(ncp_t *ncpHdl)
 * @brief Destroy all the memory and other resources allocated by VPM module at
 *        config load time.
 * @param ncp:  NCP API state handle in user mode and devHdl in kernel mode.
 */

NCP_API ncp_st_t
ncp_vpm_destroy(ncp_t *ncpHdl);

/*!
 * @fn ncp_st_t ncp_vpm_attach(ncp_t     *ncp)
 * @brief This function initializes function pointer structs. It is called from
 *        ncp_config_attach API.
 * @param ncp:  NCP API state handle.
 */

NCP_API ncp_st_t
ncp_vpm_attach(ncp_t *ncp);

/*!
 * @fn ncp_st_t ncp_vpm_detach(ncp_t     *ncp)
 * @brief This function frees memory for function pointers. It is called from
 *        ncp_config_detach API.
 * @param ncp:  NCP API state handle.
 */

NCP_API ncp_st_t
ncp_vpm_detach(ncp_t *ncp);

#endif /* #ifndef NCP_KERNEL */

/*!
 * @fn ncp_st_t ncp_vp_handle_get_by_id(ncp_hdl_t ncpHdl,
 *                                      ncp_launch_engine_type_t type,
 *                                      ncp_uint8_t vpId,
 *                                      ncp_vp_hdl_t *vpHdl)
 * @brief Get VP handle by vp id.
 * @param ncpHdl:  NCP API state handle.
 * @param type: Launch engine type.
 * @param vpId: virtual pipeline id.
 * @param vpHdl: virtual pipeline handle is returned.
 */

NCP_API ncp_st_t
ncp_vp_handle_get_by_id(ncp_hdl_t  ncpHdl,
                        ncp_launch_engine_type_t type,
                        ncp_uint8_t vpId,
                        ncp_vp_hdl_t *vpHdl);

/*!
 * @fn ncp_st_t ncp_vp_handle_get_by_name(ncp_hdl_t ncpHdl,
 *                                        ncp_launch_engine_type_t type,
 *                                        char *vpName,
 *                                        ncp_vp_hdl_t *vpHdl)
 * @brief Get VP handle by vp name.
 * @param ncpHdl:  NCP API state handle.
 * @param type: Launch engine type.
 * @param vpId: virtual pipeline name.
 * @param vpHdl: virtual pipeline handle is returned.
 */
NCP_API ncp_st_t
ncp_vp_handle_get_by_name(ncp_hdl_t  ncpHdl,
                          ncp_launch_engine_type_t type,
                          char *vpName,
                          ncp_vp_hdl_t *vpHdl);



/*!
 * @fn ncp_st_t ncp_vp_out_param_format_get(ncp_vp_hdl_t vpHdl,
 *                                      ncp_vp_param_format_t *format)
 * @brief Get the output parameter format for launch engine of the pipeline
 * @param vpHdl: The virtual pipeline handle.
 * @param format: The output parameter format is returned.
 */
NCP_API ncp_st_t
ncp_vp_out_param_format_get(ncp_vp_hdl_t vpHdl, ncp_vp_param_format_t *format);

/*!
 * @fn ncp_st_t ncp_vp_in_param_format_get(ncp_vp_hdl_t vpHdl,
 *                                     ncp_vp_param_format_t *format)
 * @brief Get the input parameter format for launch engine of the pipeline
 * @param vpHdl: The virtual pipeline handle.
 * @param format: The input parameter format is returned.
 */
NCP_API ncp_st_t
ncp_vp_in_param_format_get(ncp_vp_hdl_t vpHdl, ncp_vp_param_format_t *format);

ncp_st_t
ncp_vpm_kernel_config(ncp_dev_hdl_t devHdl, ncp_hdl_t uVpmHdl);

ncp_st_t
ncp_vpm_kernel_destroy(ncp_dev_hdl_t devHdl);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_VPM_EXT_H_ */

