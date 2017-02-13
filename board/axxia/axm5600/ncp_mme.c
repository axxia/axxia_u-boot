/*
 * TWM: Test 03-05-2014
 * New API.   Called by NCA after domain bundle is mapped
 * and mPCQ queue memory has been memset to 0.
 */
ncp_st_t ncp_mme_enable_mpcq(ncp_hdl_t ncpHdl,
                           ncp_uint32_t mpcqId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_dev_hdl_t devHdl;
    ncp_t *ncp = (ncp_t *)ncpHdl;
    ncp_mme_t *mme = NULL;

    NCP_CALL(NCP_CONFIG_VALIDATE_HANDLE(ncpHdl));
    devHdl = ncp_dev_hdls[ncp->id];
    mme = ncp->mmeHdl;

    if ( mpcqId > 1)
    {
        NCP_CALL(NCP_ST_MME_INVALID_MPCQ_ID);
    }

    if ( ! mme->mmeMPCQ[mpcqId].valid)
    {
        NCP_CALL(NCP_ST_MME_INVALID_MPCQ_ID);
    }
    
    if (mpcqId < 32)
    {    
        ncp_uint32_t enable0=0;
        ncp_uint32_t *pU32;
            
        pU32 = &enable0;
        NCP_CALL(ncp_read32(devHdl,
                        NCP_REGION_MME_MME_CORE,
                        NCP_MME_CORE_MPCQ_BASE + NCP_MPCQ_ENABLE0,      
                        ((ncp_uint32_t*)(pU32))));    
        enable0 = enable0 | ( 1 << mpcqId);
        
        NCP_CALL(ncp_write32(devHdl,
                         NCP_REGION_MME_MME_CORE,
                         NCP_MME_CORE_MPCQ_BASE + NCP_MPCQ_ENABLE0,
                         (*((ncp_uint32_t*)(pU32)))));            
    }
    else
    { 
        ncp_uint32_t enable1=0;
        ncp_uint32_t *pU32;
                   
        pU32 = &enable1;
        NCP_CALL(ncp_read32(devHdl,
                        NCP_REGION_MME_MME_CORE,
                        NCP_MME_CORE_MPCQ_BASE + NCP_MPCQ_ENABLE1,      
                        ((ncp_uint32_t*)(pU32))));  
        enable1 = enable1 | ( 1 << (mpcqId - 32));  
        
        NCP_CALL(ncp_write32(devHdl,
                         NCP_REGION_MME_MME_CORE,
                         NCP_MME_CORE_MPCQ_BASE + NCP_MPCQ_ENABLE1,
                         (*((ncp_uint32_t*)(pU32)))));                                  
    }                      

NCP_RETURN_LABEL
    if (mme != NULL) {
	    NCP_CLEANUP_MUTEX_CALL(NCP_MUTEX_UNLOCK(&mme->lock, &isLocked));
    }
    return ncpStatus;
}                               
