/*
 *  common/cmd_lsi_isu.c
 *
 *  Copyright (C) 2006 Agere Systems Inc.
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
 */

#include <config.h>

#if defined( CONFIG_COMMANDS ) && ! defined( CONFIG_ACP )

#include <common.h>
#include <command.h>
#include <linux/string.h>
#include <asm/io.h>

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_isu:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#undef WARN
#define WARN
#if defined( WARN )
#define WARN_PRINT( format, args... ) do { \
printf( "cmd_isu:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_isu:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Globals
  ======================================================================
  ======================================================================
  ======================================================================
*/

#define DESCRIPTION_ "isu     - In Service Upgrade\n"

#define USAGE_ \
"\n" \
"b,oot    -- Boot the appropriate image\n" \
"d,isplay -- Show what would be done based on the current environment\n"

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Local Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

typedef enum {

  ISU_SELECTED_A, ISU_SELECTED_B, ISU_SELECTED_NOT_SET

} isu_selected_t;

typedef enum {

  ISU_STATUS_VALID, ISU_STATUS_INVALID, ISU_STATUS_NOT_SET

} isu_status_t;

typedef struct {

  isu_selected_t selected;
  isu_status_t image_a_status;
  isu_status_t image_b_status;

} isu_system_state_t;

static void isu_get_system_state_( isu_system_state_t * );
static void isu_set_system_state_( isu_system_state_t * );
static void isu_display_system_state_( isu_system_state_t * );
static void isu_failure_( void );
static void isu_run_( isu_selected_t );

/*
  ----------------------------------------------------------------------
  isu_get_system_state_
*/

static void isu_get_system_state_( isu_system_state_t * system_state ) {

  uchar * isu_selected_ = ( char * ) 0;
  uchar * isu_image_a_status_ = ( char * ) 0;
  uchar * isu_image_b_status_ = ( char * ) 0;

  system_state->selected = ISU_SELECTED_NOT_SET;

  if( ( uchar * ) 0 != ( isu_selected_ = getenv( "isu_selected" ) ) ) {

    if( 0 == strncmp( isu_selected_, "image_a", strlen( "image_a" ) ) ) {

      system_state->selected = ISU_SELECTED_A;

    } else if( 0 == strncmp( isu_selected_, "image_b", strlen( "image_b" ) ) ) {

      system_state->selected = ISU_SELECTED_B;

    }

  }

  system_state->image_a_status = ISU_STATUS_NOT_SET;

  if( ( uchar * ) 0 !=
      ( isu_image_a_status_ = getenv( "isu_image_a_status" ) ) ) {

    if( 0 ==
        strncmp( isu_image_a_status_,
                 "valid", strlen( "valid" ) ) ) {

      system_state->image_a_status = ISU_STATUS_VALID;

    } else if( 0 ==
               strncmp( isu_image_a_status_,
                        "invalid", strlen( "invalid" ) ) ) {

      system_state->image_a_status = ISU_STATUS_INVALID;

    }

  }

  system_state->image_b_status = ISU_STATUS_NOT_SET;

  if( ( uchar * ) 0 !=
      ( isu_image_b_status_ = getenv( "isu_image_b_status" ) ) ) {

    if( 0 ==
        strncmp( isu_image_b_status_,
                 "valid", strlen( "valid" ) ) ) {

      system_state->image_b_status = ISU_STATUS_VALID;

    } else if( 0 ==
               strncmp( isu_image_b_status_,
                        "invalid", strlen( "invalid" ) ) ) {

      system_state->image_b_status = ISU_STATUS_INVALID;

    }

  }

}

/*
  ----------------------------------------------------------------------
  isu_set_system_state_
*/

static void isu_set_system_state_( isu_system_state_t * system_state ) {

  switch( system_state->selected ) {

  case ISU_SELECTED_A:
    setenv( "isu_selected", "image_a" );
    break;
  case ISU_SELECTED_B:
    setenv( "isu_selected", "image_b" );
    break;
  default:
    setenv( "isu_selected", "none" );
    break;

  }

  switch( system_state->image_a_status ) {

  case ISU_STATUS_VALID:
    setenv( "isu_image_a_status", "valid" );
    break;
  case ISU_STATUS_INVALID:
    setenv( "isu_image_a_status", "invalid" );
    break;
  default:
    setenv( "isu_image_a_status", "none" );
    break;

  }

  switch( system_state->image_b_status ) {

  case ISU_STATUS_VALID:
    setenv( "isu_image_b_status", "valid" );
    break;
  case ISU_STATUS_INVALID:
    setenv( "isu_image_b_status", "invalid" );
    break;
  default:
    setenv( "isu_image_b_status", "none" );
    break;

  }

}

/*
  ----------------------------------------------------------------------
  isu_display_system_state
*/

static void isu_display_system_state_( isu_system_state_t * system_state ) {

  printf( "{ " );

  switch( system_state->selected ) {

  case ISU_SELECTED_A: printf( "ISU_SELECTED_A, " ); break;
  case ISU_SELECTED_B: printf( "ISU_SELECTED_B, " ); break;
  default: printf( "ISU_SELECTED_NOT_SET, " ); break;

  }

  switch( system_state->image_a_status ) {

  case ISU_STATUS_VALID: printf( "ISU_STATUS_VALID, " ); break;
  case ISU_STATUS_INVALID: printf( "ISU_STATUS_INVALID, " ); break;
  default: printf( "ISU_STATUS_NOT_SET, " ); break;

  }

  switch( system_state->image_b_status ) {

  case ISU_STATUS_VALID: printf( "ISU_STATUS_VALID " ); break;
  case ISU_STATUS_INVALID: printf( "ISU_STATUS_INVALID " ); break;
  default: printf( "ISU_STATUS_NOT_SET " ); break;

  }

  printf( "}\n" );

}

/*
  ----------------------------------------------------------------------
  isu_failure_
*/

static void isu_failure_( void ) {

  uchar * bootcmd_ = ( uchar * ) 0;
  uchar * bootargs_ = ( uchar * ) 0;
  uchar command_ [ CFG_CBSIZE ];
  uchar arguments_ [ CFG_CBSIZE ];

  printf( "ISU Failed!\n" );

  if( ( ( uchar * ) 0 != ( bootcmd_ = getenv( "isu_failed_bootcmd" ) ) ) &&
      ( ( uchar * ) 0 != ( bootargs_ = getenv( "isu_failed_bootargs" ) ) ) ) {

    printf( "Copying isu_failed_boot* to boot*\n" );
    strcpy( command_, bootcmd_ );
    strcpy( arguments_, bootargs_ );
    setenv( "bootcmd", command_ );
    setenv( "bootargs", arguments_ );
    printf( "Disabling the watchdog\n" );
    setenv( "watchdog_timeout", "0" );

  } else {

    setenv( "bootcmd", "" );

  }

  return;

}

/*
  ----------------------------------------------------------------------
  isu_run_
*/

static void isu_run_( isu_selected_t selected ) {

  uchar * boot_cmd_ = ( uchar * ) 0;
  uchar * boot_args_ = ( uchar * ) 0;
  uchar command_ [ CFG_CBSIZE ];
  uchar arguments_ [ CFG_CBSIZE ];

  switch( selected ) {

  case ISU_SELECTED_A:

    if( ( ( uchar * ) 0 ==
          ( boot_cmd_ = getenv( "isu_image_a_bootcmd" ) ) ) ||
        ( ( uchar * ) 0 ==
          ( boot_args_ = getenv( "isu_image_a_bootargs" ) ) ) ) {

      isu_failure_( );

    } else {

      strcpy( command_, boot_cmd_ );
      strcpy( arguments_, boot_args_ );
      setenv( "bootcmd", command_ );
      setenv( "bootargs", arguments_ );
      watchdog_initialize( );

    }

    break;

  case ISU_SELECTED_B:

    if( ( ( uchar * ) 0 ==
          ( boot_cmd_ = getenv( "isu_image_b_bootcmd" ) ) ) ||
        ( ( uchar * ) 0 ==
          ( boot_args_ = getenv( "isu_image_b_bootargs" ) ) ) ) {

      isu_failure_( );

    } else {

      strcpy( command_, boot_cmd_ );
      strcpy( arguments_, boot_args_ );
      setenv( "bootcmd", command_ );
      setenv( "bootargs", arguments_ );
      watchdog_initialize( );

    }

    break;

  default:
    isu_failure_( );
    break;

  }

}

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Global Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_isu
*/

int do_isu( cmd_tbl_t * command_table, int flag, int argc, char * argv [ ] ) {

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 0 == strncmp( argv [ 1 ], "b", strlen( "b" ) ) ) {

    isu_system_state_t state_;
    int save_ = 0;

    /*
      ======================================================================
      If the cause of the last reset was a watchdog timeout, change
      the status of the selected image to invalid.
    */

    isu_get_system_state_( & state_ );
    isu_display_system_state_( & state_ );

    if( watchdog_flag_get( ) ) {

      /*
        The last reset was caused by a watchdog timeout!  Adjust the status
        of the selected image accordingly.
      */

      switch( state_.selected ) {

      case ISU_SELECTED_A:

        if( ISU_STATUS_VALID == state_.image_a_status ) {

          state_.image_a_status = ISU_STATUS_INVALID;
          isu_set_system_state_( & state_ );
          save_ = 1;

        }

        if( ISU_STATUS_VALID == state_.image_b_status ) {

          state_.selected = ISU_SELECTED_B;
          isu_set_system_state_( & state_ );
          save_ = 1;

        }

        break;

      case ISU_SELECTED_B:


        if( ISU_STATUS_VALID == state_.image_b_status ) {

          state_.image_b_status = ISU_STATUS_INVALID;
          isu_set_system_state_( & state_ );
          save_ = 1;

        }

        if( ISU_STATUS_VALID == state_.image_a_status ) {

          state_.selected = ISU_SELECTED_A;
          isu_set_system_state_( & state_ );
          save_ = 1;

        }

        break;

      default:
        break;

      }

      watchdog_flag_clear( );

    }

    /*
      ======================================================================
      Change the selected image if the currently selected image is not
      valid.
    */

    isu_get_system_state_( & state_ );
    isu_display_system_state_( & state_ );

    switch( state_.selected ) {

    case ISU_SELECTED_A:

      if( ( ISU_STATUS_VALID != state_.image_a_status ) &&
          ( ISU_STATUS_VALID == state_.image_b_status ) ) {

        state_.selected = ISU_SELECTED_B;
        isu_set_system_state_( & state_ );
        save_ = 1;

      }

    case ISU_SELECTED_B:

      if( ( ISU_STATUS_VALID != state_.image_b_status ) &&
          ( ISU_STATUS_VALID == state_.image_a_status ) ) {

        state_.selected = ISU_SELECTED_A;
        isu_set_system_state_( & state_ );
        save_ = 1;

      }

    default:
      break;

    }

    if( 1 == save_ ) {

      saveenv( );

    }

    /*
      ======================================================================
      Run the selected image if possible.
    */

    isu_get_system_state_( & state_ );
    isu_display_system_state_( & state_ );

    switch( state_.selected ) {

    case ISU_SELECTED_A:

      if( ISU_STATUS_VALID == state_.image_a_status ) {

        isu_run_( ISU_SELECTED_A );

      } else {

        isu_failure_( );

      }

      break;

    case ISU_SELECTED_B:

      if( ISU_STATUS_VALID == state_.image_b_status ) {

        isu_run_( ISU_SELECTED_B );

      } else {

        isu_failure_( );

      }

      break;

    default:
      isu_failure_( );
      break;

    }

  } else if( 0 == strncmp( argv [ 1 ], "d", strlen( "d" ) ) ) {

    isu_system_state_t state_;

    isu_get_system_state_( & state_ );
    isu_display_system_state_( & state_ );

  } else {

    printf( "%s", USAGE_ );

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( isu, 100, 0, do_isu, DESCRIPTION_, USAGE_ );

#endif /* CONFIG_COMMANDS */
