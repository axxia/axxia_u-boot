

	/*
	  Enable system caches.
	*/

	/* loop through all syscaches */
#if !defined(ACP_DISABLE_L3)
	for (i = 0; i < num_sc_nodes; ++i) {
		/* enable the cache - unless the user asked not to */
		if (!sysmem->syscacheDisable)
			/*
			  TODO: This should only be done for
			  architectures before ACP2500V2!

			  See BZ38534.
			*/
			ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x100,
				    (0 == sysmem->enableECC) ? 0 : 8);
	}
#endif

	NCR_TRACE("# Initializing system cache\n");

	/*
	 * Determine appropriate value of the system cache address munge
	 * register based on the number of syscaches present.
	 * The field we program has a different value meaning for v1
	 * and v2:
	 *
	 *         v1                                v2
	 *   system_memory_size      value     memory_per_cache
	 *        64GB                 0            16GB
	 *        32GB                 1             8GB
	 *        16GB                 2             4GB
	 *         8GB                 3             2GB
	 *         4GB                 4             1GB
	 *         2GB                 5           512MB
	 *         1GB                 6           256MB
	 *       512MB                 7           128MB
	 */
#if defined( ACP_X1V1 )
	switch( ( 1 << ( sysmem_size - 20 ) ) ) {
	case 512:
		value = 7;
		break;
	case 1024:
		value = 6;
		break;
	case 2048:
		value = 5;
		break;
	case 4096:
		value = 4;
		break;
	case 8192:
		value = 3;
		break;
	case 16384:
		value = 2;
		break;
	case 32768:
		value = 1;
		break;
	case 65536:
		value = 0;
		break;
	default:
		printf( "Error Calculating Munge Value.\n" );
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		break;
	}
#elif defined(CONFIG_AXXIA_344X) || defined(CONFIG_AXXIA_342X) || defined(CONFIG_AXXIA_25xx)
	value = ( 1 << ( sysmem_size - 20 ) ) / num_sc_nodes;

	switch( value ) {
	case 128:
		value = 7;
		break;
	case 256:
		value = 6;
		break;
	case 512:
		value = 5;
		break;
	case 1024:
		value = 4;
		break;
	case 2048:
		value = 3;
		break;
	case 4196:
		value = 2;
		break;
	case 8192:
		value = 1;
		break;
	case 16384:
		value = 0;
		break;
	default:
		printf( "Error Calculating Munge Value.\n" );
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		break;
	}
#else
#error "Unsupported System!"
#endif

	/* if syscacheMode == 1 set the munge reg 'field_order' to 2 */
	munge_reg = value | (sysmem->syscacheMode << 4);

	/* Just match the RTE trace... */
	NCR_TRACE("ncpRead    0.24.255.0x0000000004 1\n");
	NCR_TRACE("ncpRead    0.32.0.0x0000000014 1\n");
	NCR_TRACE("ncpRead    0.32.0.0x0000000014 1\n");

	/* loop through all syscaches */
	for( i = 0; i < num_sc_nodes; ++ i ) {
		/* write 'magic value' to enable_init field */
		ncr_write32( NCP_REGION_ID(sc_nodes[i], 0), 0x18, 0xed );
		/* set init_cache_ram field */
		ncr_write32( NCP_REGION_ID(sc_nodes[i], 0), 0x18, 0x000200ed );

		/* wait for it to complete */
		if (0 != ncr_poll(NCP_REGION_ID(sc_nodes[i], 0), 0x20, 
				  0x4,        /* mask */
				  0,          /* value */
				  0,          /* delayTime */
				  1000))       /* delayLoops */
		{
			acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}

		/* set the munge register */
		ncr_write32( NCP_REGION_ID(sc_nodes[i], 0), 0x14, munge_reg );

		/*
		  BZ 33026
		  X1V2 & X2: WFQ Mechanism in SYSCACHE Needs New
		  Updated Weight Configuration
		*/
		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x1c, 0x23630323);

#ifdef ACP_X1V1
		/*
		  BZ 29933
		  Change the high water mark (the fifo_high_wm field in
		  mem_inf_write_scr_cmd_fifo_wm) to 4 (default is 5).
		  Should be done for all system caches in V1.
		*/
		ncr_write32( NCP_REGION_ID( sc_nodes[i], 1 ), 0x254,
			     0x00040004 );
#endif
	}

	/* Clear System Memory. */
	fill_sysmem(0ULL, (1ULL << sysmem_size), num_sc_nodes);

	/* If ECC is enabled, clear the status bits. */
	if (0 != sysmem->enableECC) {
		/* clear ECC interrupt status bits */
		for( i = 0; i < sysmem->num_interfaces; ++ i ) {
			ncr_read32( NCP_REGION_ID( sm_nodes [ i ], 0 ),
				    INT_STATUS_OFFSET, & value );
			value &= ECC_ERROR_MASK;
			ncr_write32( NCP_REGION_ID( sm_nodes [ i ], 0 ),
				     NCP_DENALI_CTL_89, value );
		}
	}

	/* Disable some speculative reads. */
#if defined(ACP_X1V1) || defined(CONFIG_AXXIA_344X) || defined(CONFIG_AXXIA_342X)
	if (sysmem->half_mem)
		dcr_write( 0x3377c800, 0xf00 );
	else
		dcr_write( 0x33774800, 0xf00 );
#endif

	/* set up NHA */
	if (sysmem->half_mem) {
		/* and all the other sysmem clients */
		mask = value = 0x10000000;
		ncr_modify32( NCP_REGION_ID(0x0b, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x0e, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x15, 0x00), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x16, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x19, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1c, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x17, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1f, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1a, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1a, 0x23), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x14, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x14, 0x0a), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x0c, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1b, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x00, 0x00), 0x4, mask, value );
	}

	/* WA for 34575 (applies to X1V2 and X2). */
#if defined(CONFIG_AXXIA_344X) || defined(CONFIG_AXXIA_342X)
	dcr_write(0, 0xf1f);
#endif


