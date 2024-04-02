/* SPDX-License-Identifier: Apache-2.0 */
/**
 * @file 		arrayutils.h
 *
 * @brief 		Header file for Array Utils Library 
 *
 * @copyright 	Copyright (C) 2024 Jackrabbit Founders LLC. All rights reserved.
 *
 * @date 		Feb 2024
 * @author 		Barrett Edwards <code@jrlabs.io>
 * 
 * Macro / Enumeration Prefixes 
 * AUVB - Verbose Macros 
 */

#ifndef _ARRAYUTILS_H
#define _ARRAYUTILS_H

/* INCLUDES ==================================================================*/

#include <linux/types.h>

/* MACROS ====================================================================*/

#define AUVB_DEFAULT_WIDTH 	16	//!< Default width for printing __u8 buffers 
#define AUVB_MIN_WIDTH 		4	//!< Minium width for printing buffers

/* ENUMERATIONS ==============================================================*/

/* STRUCTS ===================================================================*/

/* GLOBAL VARIABLES ==========================================================*/

/* PROTOTYPES ================================================================*/

void autl_prnt_buf(void *buf, unsigned long len, unsigned long width, int print_header);
int autl_csv_to_u8(__u8 *dst, char* src, unsigned max, int hex);
int autl_csv_to_u64(__u64 *dst, char* src, unsigned max, int hex);

/* INLINE FUNCTIONS ==========================================================*/

#endif //ifndef _ARRAYUTILS_H
