/**************************************************************************
 ** INTEL CONFIDENTIAL
 ** Copyright 2008 - 2015 Intel Corporation All Rights Reserved.
 **
 ** The source code contained or described herein and all documents related to 
 ** the source code ("Material") are owned by Intel Corporation or its 
 ** suppliers or licensors. Title to the Material remains with 
 ** Intel Corporation or its suppliers and licensors. 
 ** The Material contains trade secrets and proprietary and confidential
 ** information of Intel or its suppliers and licensors. The Material is 
 ** protected by worldwide copyright and trade secret laws and treaty 
 ** provisions. No part of the Material may be used, copied, reproduced, 
 ** modified, published, uploaded, posted, transmitted, distributed, or 
 ** disclosed in any way without Intel's prior express written permission.
 **
 ** No license under any patent, copyright, trade secret or other 
 ** intellectual property right is granted to or conferred upon you by 
 ** disclosure or delivery of the Materials, either expressly, by implication, 
 ** inducement, estoppel or otherwise. Any license under such intellectual 
 ** property rights must be express and approved by Intel in writing.
 *************************************************************************/

/*! @file      ncp_llist.h
 *  @brief     This file implements utility functions to add and remove entries
 *             from a doubly linked list. The linked list nodes must be of the 
 *             ncp_llist_t format.
 */

#ifndef _ncp_llist_h_
#define _ncp_llist_h_

/*
 * Base include file for our types
 */
#include "uboot/ncp_types.h"

#ifdef __cplusplus
extern "C" { 
#endif

/*!
 *  @defgroup _utility_ Utility
 *
 *  @addtogroup  _llist_ Linked List Object
 *  @brief Linked List Object (llist)
 *  @detail This module implements utility functions to add and remove entries
 *         from a doubly linked list. The linked list nodes must be of the 
 *         ncp_llist_t format.
 *  @{
 *  @ingroup _utility_
 */

/*!
 * @struct ncp_llist_t
 * @brief The structure of an entry in the linked list, including the root
 *        element.  Each node in the list should look like this.
 */
typedef struct _ncp_llist_t {
    struct _ncp_llist_t *next;
    struct _ncp_llist_t *prev;
} ncp_llist_t;

/*!
 * @fn ncp_llist_insert(ncp_llist_t *node, ncp_llist_t *pred)
 * @brief  Inserts the specified node after the predecessor.
 * @returns void
 */
NCP_API void ncp_llist_insert(ncp_llist_t *node, ncp_llist_t *pred);

/*!
 * @fn  ncp_llist_remove(ncp_llist_t *node)
 * @brief  Removes the node from the list
 * @returns void
 */
NCP_API void ncp_llist_remove(ncp_llist_t *node);

/*!
 * @fn ncp_llist_init_head(ncp_llist_t *node)
 * @brief  Initialize ncp_llist_t by pointing next and prev pointers to itself
 * @returns void
 */
NCP_API void ncp_llist_init_head(ncp_llist_t *node);

/*!
 * @fn ncp_llist_insert_tail(ncp_llist_t *node, ncp_llist_t *head)
 * @brief  Inserts the specified node at the tail of a circularly-linked list
 * @returns void
 */
NCP_API void ncp_llist_insert_tail(ncp_llist_t *node, ncp_llist_t *head);

/*!
 * @fn ncp_llist_empty(ncp_llist_t *head)
 * @brief  Tests if list is empty
 * @returns void
 */
NCP_API ncp_bool_t ncp_llist_empty(ncp_llist_t *head);

/*
 * ncp_llist_entry
 *      Given a head pointer and entry struct type, get the struct for
 *      the list entry
 *      head: the list head
 *      type: struct type ncp_llist_t is embedded in
 *      node: name of ncp_llist_t within the struct
 */
#define ncp_llist_entry(head, type, node) \
    ((type *)((char *)(head)-(unsigned long)(&((type *)0)->node)))

/* ncp_llist_for_each
 *      Iterate over a list
 *      pos: the ncp_llist_t struct to use as a loop counter
 *      head: the list head
 */
#define ncp_llist_for_each(pos,head) \
    for (pos = (head)->next; pos != (head); \
        pos = pos->next)

/* ncp_llist_for_each_safe
 *      Iterate over a list, safe against removal of list entries
 *      pos: the ncp_llist_t struct to use as a loop counter
 *      temp: temporary storage ncp_llist_t struct
 *      head: the list head
 */
#define ncp_llist_for_each_safe(pos,temp,head) \
    for (pos = (head)->next, temp = pos->next; pos != (head); \
        pos = temp, temp = pos->next)


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _ncp_llist_h_ */
