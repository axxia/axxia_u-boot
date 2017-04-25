/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*   file      ncp_config.h
 *   brief     Device Configuration APIs.
 */


#ifndef __NCP_CONFIG_PVT_H__
#define __NCP_CONFIG_PVT_H__

/**************************************************************************/
/* Constants & Type & Macros  Definitions                                 */
/**************************************************************************/


#ifndef NCP_CHECK_DISABLED                                 
#define NCP_CONFIG_VALIDATE_HANDLE(_pconfigHdl)            \
({                                                         \
        ncp_t *_pncp = (ncp_t*) _pconfigHdl;               \
        ncp_st_t _status = NCP_ST_SUCCESS;                 \
        if ( ( _pncp == NULL) ||                           \
                ( _pncp->cookie != NCP_HANDLE_COOKIE)) {   \
                _status = NCP_ST_INVALID_HANDLE;           \
                 }                                         \
       _status;                                            \
})                                                         
#else                                                      
#define NCP_CONFIG_VALIDATE_HANDLE(_pconfigHdl) ({         \
        NCP_ST_SUCCESS;                                    \
})                                                         
#endif                                                     


typedef ncp_st_t (* ncp_module_cfg_fn_t)(
        ncp_t     *ncp,
        ncp_map_t *map);


typedef ncp_st_t (* ncp_module_warm_cfg_fn_t)(
        ncp_t     *ncp);


typedef ncp_st_t (* ncp_module_destroy_fn_t)(
        ncp_t *ncp);


typedef struct
{
    const char *            name;
    /* Insert other attributes here at some point. */
} ncp_chip_config_t;


typedef struct
{
    /* 
     * The revision name in the XML, i.e. "V1", "V2", ...
     */
    const char *            revName;
    /*!
     * The chip type value associated with the revName.
     */
    ncp_uint8_t             chipType;
} ncp_chip_revision_mapping_t;

#endif /* __NCP_CONFIG_H__ */
