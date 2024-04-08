/* SPDX-License-Identifier: Apache-2.0 */
/**
 * @file 		testbench.c
 *
 * @brief 		Testbench code file for Array Utils library
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

/* memset()
 */
#include <string.h>

/* malloc()
 * free()
 */
#include <stdlib.h>

/* __u8
 * __u64
 */
#include <linux/types.h>

#include "main.h"

/* MACROS ====================================================================*/

/* ENUMERATIONS ==============================================================*/

/* STRUCTS ===================================================================*/

/* GLOBAL VARIABLES ==========================================================*/

/* PROTOTYPES ================================================================*/

int main()
{

	// TEST 1: Print u8 buffer
	printf("TEST 1: Print u8 buffer\n");
	{ 
		int i;
		__u8 *u8;

		// Allocate memory
		u8 = (__u8*) malloc(64);
	
		// Fill with data
		for ( i = 0 ; i < 64 ; i ++ ) 
			u8[i] = i;	
	
		// Print buffer 
		autl_prnt_buf(u8, 64, 16, 1);

		// Clean up 
		free(u8);
	}

	// TEST 2: convert CSV string of __u8 values into a __u8[] array 
	printf("\n");
	printf("TEST 2: convert CSV string of __u8 values into a __u8[] array\n");
	{
		int rv;
		char str[] = "1,2,3,4,5,6,7,8,9,10";
		__u8 array[32]; 

		memset(array, 0, 32);

		rv = autl_csv_to_u8(array, str, 32, 0);

		printf("STR: %s\n", str);
		printf("Number of values converted: %d\n", rv);
		autl_prnt_buf(array, 32, 4, 0);
	}
	
	// TEST 3: convert CSV string of __u8 values into a __u8[] array with trailing ,
	printf("\n");
	printf("TEST 3: convert CSV string of __u8 values into a __u8[] array with trailing ,\n");
	{
		int rv;
		char str[] = "1,2,3,4,5,6,7,8,9,10,";
		__u8 array[32]; 

		rv = autl_csv_to_u8(array, str, 32, 0);

		printf("STR: %s\n", str);
		printf("Number of values converted: %d\n", rv);
		autl_prnt_buf(array, 10, 4, 0);
	}

	// TEST 4: Convert a mixed decimal / hex string
	printf("\n");
	printf("TEST 4: Convert a mixed decimal / hex string\n");
	{
		int rv;
		char str[] = "0x1,0x2,0x3,4,5,6,7,8,9,10,0x10";
		__u8 array[32]; 

		memset(array, 0, 32);

		rv = autl_csv_to_u8(array, str, 32, 0);

		printf("STR: %s\n", str);
		printf("Number of values converted: %d\n", rv);
		autl_prnt_buf(array, 32, 4, 0);
	}

	// TEST 5: Test max count
	printf("\n");
	printf("TEST 5: Test max count\n");
	{
		int rv;
		char str[] = "0x1,0x2,0x3,4,5,6,7,8,9,10,0x10";
		__u8 array[32]; 

		memset(array, 0, 32);

		rv = autl_csv_to_u8(array, str, 5, 0);

		printf("STR: %s\n", str);
		printf("Number of values converted: %d\n", rv);
		autl_prnt_buf(array, 32, 4, 0);
	}

	// TEST 6: Test base 16
	printf("\n");
	printf("TEST 6: Test base 16\n");
	{
		int rv;
		char str[] = "0x1,0x2,0x3,4,5,6,7,8,9,10,0x10";
		__u8 array[32]; 

		memset(array, 0, 32);

		rv = autl_csv_to_u8(array, str, 32, 1);

		printf("STR: %s\n", str);
		printf("Number of values converted: %d\n", rv);
		autl_prnt_buf(array, 32, 4, 0);
	}

	// TEST 7: Test __u64 conversion
	printf("\n");
	printf("TEST 7: Test __u64 conversion\n");
	{
		int rv;
		char str[] = "12345678, 0x12345678, 0x12345678a1a2a3a4";
		__u64 array[8]; 

		memset(array, 0, 8*sizeof(__u64));

		rv = autl_csv_to_u64(array, str, 8, 0);

		printf("STR: %s\n", str);
		printf("Number of values converted: %d\n", rv);
		autl_prnt_buf(array, 8*sizeof(*array), 4, 0);
	}

	// TEST 8: Test __u64 conversion all hex
	printf("\n");
	printf("TEST 8: Test __u64 conversion all hex\n");
	{
		int rv;
		char str[] = "12345678, 0x12345678, 0x12345678a1a2a3a4";
		__u64 array[8]; 

		memset(array, 0, 8*sizeof(__u64));

		rv = autl_csv_to_u64(array, str, 8, 1);

		printf("STR: %s\n", str);
		printf("Number of values converted: %d\n", rv);
		autl_prnt_buf(array, 8*sizeof(*array), 4, 0);
	}

	return 0;
}
