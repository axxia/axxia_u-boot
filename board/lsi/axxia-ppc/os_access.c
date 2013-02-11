/*
 * os_access.c
 *
 * Provides access to NAND (read/write/erase), and the environment.
 * 
 * Copyright (C) 2010 LSI Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*#define LSI_DEBUG*/
#include <config.h>
#ifdef CONFIG_ACP3
#include <common.h>
#include <jffs2/jffs2.h>
#include <nand.h>
#include "ncp.h"

/*
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
*/

static nand_access_t nand_access;
static unsigned long gd_backup;
static unsigned long os_r2;
#define SAVE_R2( location ) do { \
__asm__ __volatile__ ( "ori %0,2,0" : "=r" ( location ) : ); \
} while( 0 );
#define RESTORE_R2( location ) do { \
__asm__ __volatile__ ( "ori 2,%0,0" : : "r" ( location ) ); \
} while( 0 );
static void * block_buffer;

/*
  ------------------------------------------------------------------------------
  get_offset_by_partition
*/

static int
get_offset_by_partition( const char * partition,
			 unsigned int * offset, unsigned int * size )
{
	struct mtd_device * dev;
	struct part_info * part;
	unsigned short pnum;

	if( ( 0 == mtdparts_init( ) ) &&
	    ( 0 == find_dev_and_part( partition, & dev, & pnum, & part ) ) ) {
		DEBUG_PRINT( "type=0x%x offset=0x%x size=0x%x num=%d\n",
			     dev->id->type, part->offset, part->size,
			     dev->id->num );
		* offset = part->offset;
		* size = part->size;
		return 0;
	}

	return -1;
}

/*
  ------------------------------------------------------------------------------
  os_access_nand_read
*/

static ncp_status_t
os_access_nand_read( const char * partition, unsigned int offset,
		     char * buffer, int size )
{
	ncp_status_t rc = NCP_SUCCESS;
	unsigned int part_offset;
	unsigned int part_size;
	int size_read = size;

	DEBUG_PRINT( "partition=%s size=%d\n", partition, size );
	SAVE_R2( os_r2 );
	RESTORE_R2( gd_backup );

	if( 0 != get_offset_by_partition( partition,
					  & part_offset, & part_size ) ) {
		rc = NCP_NAND_PARTITION_NOT_FOUND;
		goto cleanup;
	}

	if( offset > part_size ) {
		rc = NCP_NAND_OFFSET_TOO_BIG;
		goto cleanup;
	}

	if( ( offset + size ) > part_size ) {
		rc = NCP_NAND_SIZE_TOO_BIG;
		goto cleanup;
	}

	if( 0 != nand_read( & nand_info [ 0 ], ( part_offset + offset ),
			    & size_read, ( unsigned char * ) buffer ) ) {
		rc = NCP_NAND_HW_READ_FAIL;
		goto cleanup;
	}

	DEBUG_PRINT( "Read 0x%x bytes.\n", size_read );
 cleanup:
	RESTORE_R2( os_r2 );
	return rc;
}

/*
  ------------------------------------------------------------------------------
  os_access_nand_write
*/

static ncp_status_t
os_access_nand_write( const char * partition, unsigned int offset,
		      char * buffer, int size )
{
	ncp_status_t rc = NCP_SUCCESS;
	unsigned int part_offset;
	unsigned int part_size;
	int bytes_written = 0;
	unsigned int this_offset;
	int this_access;
	unsigned int es = ( nand_info [ 0 ] ).erasesize;
	int status;
	nand_erase_options_t erase;

	DEBUG_PRINT( "partition=%s offset=%d size=%d\n",
		     partition, offset, size );
	SAVE_R2( os_r2 );
	RESTORE_R2( gd_backup );

	if( 0 != get_offset_by_partition( partition,
					  & part_offset, & part_size ) ) {
		rc = NCP_NAND_PARTITION_NOT_FOUND;
		goto cleanup;
	}

	if( offset > part_size ) {
		rc = NCP_NAND_OFFSET_TOO_BIG;
		goto cleanup;
	}

	if( ( offset + size ) > part_size ) {
		rc = NCP_NAND_SIZE_TOO_BIG;
		goto cleanup;
	}

	erase.quiet = 0;
	erase.jffs2 = 0;
	erase.scrub = 0;

	if( 0 != ( offset % es ) ) {
		this_offset = part_offset + offset - ( offset % es );
		this_access = es;
		status = nand_read( & nand_info [ 0 ], this_offset,
				    & this_access, block_buffer );
		DEBUG_PRINT( "this_access=0x%x status=0x%x\n",
			     this_access, status );
		memcpy( ( void * ) ( block_buffer + ( offset % es ) ),
			buffer,
			( size > ( es - ( offset % es ) ) ) ?
			( es - ( offset % es ) ) : size );
		erase.length = es;
		erase.offset = this_offset;
		status = nand_erase_opts( & nand_info [ 0 ], & erase );
		DEBUG_PRINT( "status=0x%x\n", status );
		this_access = es;
		status = nand_write( & nand_info [ 0 ], this_offset,
				     & this_access, block_buffer );
		DEBUG_PRINT( "this_access=0x%x status=0x%x\n",
			     this_access, status );

		if( size > ( es - ( offset % es ) ) ) {
			offset += ( es - ( offset % es ) );
			size -= ( es - ( offset % es ) );
			buffer += ( es - ( offset % es ) );
		} else {
			size = 0;
		}

		DEBUG_PRINT( "offset=%d size=%d\n", offset, size );
	}

	while( es <= size ) {
		erase.length = es;
		erase.offset = part_offset + offset;
		status = nand_erase_opts( & nand_info [ 0 ], & erase );
		DEBUG_PRINT( "status=0x%x\n", status );
		this_access = es;
		status = nand_write( & nand_info [ 0 ],
				     ( part_offset + offset ), & this_access,
				     buffer );
		DEBUG_PRINT( "this_access=0x%x status=0x%x\n",
			     this_access, status );
		offset += es;
		size -= es;
		buffer += es;
		DEBUG_PRINT( "offset=%d size=%d\n", offset, size );
	}

	if( 0 != size ) {
		this_offset = part_offset + offset;
		this_access = es;
		DEBUG_PRINT( "this_offset=0x%x this_access=0x%x\n",
			     this_offset, this_access );
		status = nand_read( & nand_info [ 0 ], this_offset,
				    & this_access, block_buffer );
		DEBUG_PRINT( "this_access=0x%x status=0x%x\n",
			     this_access, status );
		memcpy( block_buffer, buffer, size );
		erase.length = es;
		erase.offset = this_offset;
		status = nand_erase_opts( & nand_info [ 0 ], & erase );
		DEBUG_PRINT( "status=0x%x\n", status );
		this_access = es;
		status = nand_write( & nand_info [ 0 ], this_offset,
				     & this_access, block_buffer );
		DEBUG_PRINT( "this_access=0x%x status=0x%x\n",
			     this_access, status );
		DEBUG_PRINT( "offset=%d size=%d\n", offset, size );
	}

 cleanup:
	RESTORE_R2( os_r2 );
	return rc;
}

/*
  ------------------------------------------------------------------------------
  os_access_nand_erase
*/

static ncp_status_t
os_access_nand_erase( const char * partition )
{
	ncp_status_t rc = NCP_SUCCESS;
	unsigned int part_offset;
	unsigned int part_size;
	nand_erase_options_t nand_erase_options;

	DEBUG_PRINT( "partition=%s\n", partition );
	SAVE_R2( os_r2 );
	RESTORE_R2( gd_backup );

	if( 0 != get_offset_by_partition( partition,
					  & part_offset, & part_size ) ) {
		rc = NCP_NAND_PARTITION_NOT_FOUND;
		goto cleanup;
	}

	nand_erase_options.length = part_size;
	nand_erase_options.offset = part_offset;
	nand_erase_options.quiet = 0;
	nand_erase_options.jffs2 = 0;
	nand_erase_options.scrub = 0;

	if( 0 != nand_erase_opts( & nand_info [ 0 ], & nand_erase_options ) ) {
		rc = NCP_NAND_HW_ERASE_FAIL;
		goto cleanup;
	}

 cleanup:
	RESTORE_R2( os_r2 );
	return rc;
}

/*
  ------------------------------------------------------------------------------
  os_access_get_env
*/

static ncp_status_t
os_access_get_env( const char * name, char * value, int size )
{
	char * variable;

	SAVE_R2( os_r2 );
	RESTORE_R2( gd_backup );
	DEBUG_PRINT( "name=%s size=%d\n", name, size );

	if( ( char * ) 0 == ( variable = getenv( name ) ) ) {
		DEBUG_PRINT( "getenv() failed\n" );
		RESTORE_R2( os_r2 );
		return NCP_UBOOT_PARAM_NAME_NOT_FOUND;
	}

	RESTORE_R2( os_r2 );

	if( strlen( variable ) >= size ) {
		DEBUG_PRINT( "Variable is too big for the buffer.\n" );
		return NCP_UBOOT_PARAM_VAL_SIZE_TOO_SMALL;
	}

	strcpy( value, variable );
	return NCP_SUCCESS;
}

/*
  ------------------------------------------------------------------------------
  os_access_set_env
*/

static ncp_status_t
os_access_set_env( const char * name, const char * value )
{
	DEBUG_PRINT( "name=%s value=%s\n", name, value );
	SAVE_R2( os_r2 );
	RESTORE_R2( gd_backup );

	if( 0 != setenv( name, value ) ) {
		RESTORE_R2( os_r2 );
		return NCP_UBOOT_ENV_FULL;
	}

	RESTORE_R2( os_r2 );
	return NCP_SUCCESS;
}

/*
  ------------------------------------------------------------------------------
  os_access_save_env
*/

static ncp_status_t
os_access_save_env( void )
{
	DEBUG_PRINT( "\n" );

	SAVE_R2( os_r2 );
	RESTORE_R2( gd_backup );

	if( 0 != saveenv( ) ) {
		RESTORE_R2( os_r2 );
		return NCP_NAND_HW_WRITE_FAIL;
	}

	RESTORE_R2( os_r2 );
	return NCP_SUCCESS;
}

/*
  ==============================================================================
  ==============================================================================
  Global Stuff
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  os_access_get_address
*/

void *
os_access_get_address( void )
{
	return ( void * ) & nand_access;
}

/*
  ------------------------------------------------------------------------------
  os_access_init
*/

int
os_access_init( void )
{
	if( 0 == ( block_buffer = malloc( ( nand_info [ 0 ] ).erasesize ) ) ) {
		return -1;
	}
	DEBUG_PRINT( "Allocated 0x%x bytes for a block buffer.\n",
		     ( nand_info [ 0 ] ).erasesize );
	nand_access.version = NCP_ACCESS_VERSION;
	nand_access.readFn = os_access_nand_read;
	nand_access.writeFn = os_access_nand_write;
	nand_access.eraseFn = os_access_nand_erase;
	nand_access.paramGetFn = os_access_get_env;
	nand_access.paramSetFn = os_access_set_env;
	nand_access.envSaveFn = os_access_save_env;

	/*
	  U-Boot uses a register (r2 in the PPC case) to store a
	  pointer to the global data structure.  Once control
	  transfers to the OS, the value of r2 will get changed.  So,
	  save the value of r2 locally.
	*/

	SAVE_R2( gd_backup );

	return 0;
}

#endif /* CONFIG_ACP3 */
