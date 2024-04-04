/* SPDX-License-Identifier: Apache-2.0 */
/**
 * @file 		arrayutils.c
 *
 * @brief 		Code file for Array Utils library
 *
 * @copyright 	Copyright (C) 2024 Jackrabbit Founders LLC. All rights reserved.
 *
 * @date 		Feb 2024
 * @author 		Barrett Edwards <code@jrlabs.io>
 * 
 */

/* INCLUDES ==================================================================*/

/* printf()
 */
#include <stdio.h>

/* strtoul()
 */
#include <stdlib.h>

/* memset()
 */
#include <string.h>

#include "main.h"

/* MACROS ====================================================================*/

/* ENUMERATIONS ==============================================================*/

/* STRUCTS ===================================================================*/

/* GLOBAL VARIABLES ==========================================================*/

/* PROTOTYPES ================================================================*/

/* FUNCTIONS =================================================================*/

/*
 * Print a unsigned char buffer 
 */
void autl_prnt_buf(void *buf, unsigned long len, unsigned long width, int print_header)
{
	unsigned long i, j, k, rows;
	__u8 *ptr;

	/* STEP 1: Verify Inputs */
	if ( buf == NULL) 
		return;

	if ( len == 0 )
		return;
	
	if ( width == 0 )
		width = AUVB_DEFAULT_WIDTH;
	
	if ( width < AUVB_MIN_WIDTH )
		width = AUVB_MIN_WIDTH;

	ptr = (__u8*) buf;

	/* Compute the number of rows to print */
	rows = len / width;
	if ( (len % width) > 0)
		rows++;

	/* Print index '0x0000: ' */
	if (print_header) {
		printf("            ");
		for ( i = 0 ; i < width ; i++ )
			printf("%02lu ", i);
		printf("\n");
	}

	k = 0;
	for ( i = 0 ; i < rows ; i++ ) {
		printf("0x%08lx: ", i * width);
		for ( j = 0 ; j < width ; j++ ) {
			if (k >= len)
				break;

			printf("%02x ", ptr[i*width + j]);

			k++;
		}
		printf("\n");
	}

	return;
}

/**
 * Split a comma separated string of __u8 into a __u8[] array
 *
 * @param src char* to a comma separated array of __u8 values
 * @param dst __u8* array to store parsed values in
 * @param max Maximum number of values to convert (i.e. size of dst array)
 * @param hex 0=auto detect base, non zero = treat all values as hex
 */
int autl_csv_to_u8(__u8 *dst, char* src, unsigned max, int hex)
{
	char *head, *tail;
	char buf[8];
	unsigned i; 
	unsigned base;

	// Initialize variables 
	i = 0;
	head = src;
	tail = src; 
	memset(buf,0,8);
	if (hex)
		base = 16;
	else 
		base = 0;

	// Loop through the character array
	while (*tail != 0) 
	{
		if (*tail == ',') 
		{
			memcpy(buf, head, tail - head);
			dst[i] = strtoull(buf, NULL, base);
			memset(buf,0,8);
			i++;
			tail++;
			head = tail;
		}
		else 
			tail++;

		if (i >= max)
			return i;
	}

	// Catch last entry in the CSV list 
	if (head != tail) 
	{
		memcpy(buf, head, tail - head);
		dst[i] = strtoull(buf, NULL, base);
		i++;
	}

	return i;
}

/**
 * Split a comma separated string of __u64 into a __u64[] array
 *
 * @param src char* to a comma separated array of __u64 values
 * @param dst __u64* array to store parsed values in
 * @param max Maximum number of values to convert (i.e. size of dst array)
 * @param hex 0=auto detect base, non zero = treat all values as hex
 */
int autl_csv_to_u64(__u64 *dst, char* src, unsigned max, int hex)
{
	char *head, *tail;
	char buf[64];
	unsigned  i; 
	unsigned base;

	i = 0;
	head = src;
	tail = src; 
	memset(buf,0,64);
	if (hex)
		base = 16;
	else 
		base = 0;

	while (*tail != 0) 
	{
		if (*tail == ',') 
		{
			memcpy(buf, head, tail - head);
			dst[i] = strtoull(buf, NULL, base);
			memset(buf,0,64);
			i++;
			tail++;
			head = tail;
		}
		else 
			tail++;

		if (i >= max)
			return i;
	}

	// Catch last entry in the CSV list 
	if (head != tail) 
	{
		memcpy(buf, head, tail - head);
		dst[i] = strtoull(buf, NULL, base);
		i++;
	}

	return i;
}

