/**
 * 	\addtogroup nvm-exercise
 * @{
 */

/**
 * \defgroup gp-nvm-test Test example for general purpose NVM library.
 * @{
 *
 * Example code using the \ref gp-nvm-lib 
 * 
 * The example adds attributes with different datatypes and sizes.
 * There are four integer type attributes, four arrays with different integer types and one struct.
 * The example randomly picks an attribute each iteration for NUM_ITERATIONS.
 * The value of the attribute is read, updated and read again.  
 * The first read can fail if the attribute was not present in nvm.bin.
 * The example fails if there is no nvm.bin file in this directory.
 * 
 *
 */

/**
 * \file
 *         @brief       Example using the \ref gp-nvm-lib.
 * \author
 *         Peter Ruckebusch <peter.ruckebusch@gmail.com>
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gp-nvm.h"

// test data

#define MAX_ARRAY_LEN 10
#define NUM_ITERATIONS 10
#define NUM_TEST_DATA_EL 9
#define MAX_TEST_DATA_LEN MAX_ARRAY_LEN*sizeof(uint64_t)

uint8_t data1 = 1;
uint16_t data2 = 2;
uint32_t data3 = 3;
uint64_t data4 = 4;

uint8_t array1[MAX_ARRAY_LEN] = { [0 ... 9] = 1 };
uint16_t array2[MAX_ARRAY_LEN] = { [0 ... 9] = 2 };
uint32_t array3[MAX_ARRAY_LEN] = { [0 ... 9] = 3 };
uint64_t array4[MAX_ARRAY_LEN] = { [0 ... 9] = 4 };

typedef struct {
	uint8_t id;
	uint32_t options;
	uint8_t length;
	uint8_t data[MAX_ARRAY_LEN];
} gp_test_struct_t;

gp_test_struct_t test_struct1 = { 1, 2, 3, {[0 ... 9] = 1} };

uint8_t res_array[MAX_TEST_DATA_LEN] = {0};

uint8_t length_array[NUM_TEST_DATA_EL] = {sizeof(data1), sizeof(data2), sizeof(data3), sizeof(data4), sizeof(array1), sizeof(array2), sizeof(array3), sizeof(array4), sizeof(gp_test_struct_t)};

int main () {
	int i,j;
	time_t t;
	uint8_t length;

	gp_nvm_result_t result;
	void* test_list[NUM_TEST_DATA_EL] = {&data1, &data2, &data3, &data4, &array1, &array2, &array3, &array4, &test_struct1};
	
	/* Intializes random number generator */
	srand((unsigned) time(&t));

	gp_nvm_init();

	for( i=0 ; i<NUM_ITERATIONS; i++ ){
		int rvalue = rand() % NUM_TEST_DATA_EL;
		printf("Iteration %d: get/set/get attribute %d \n", i, rvalue+1);
		
		// try to get attribute
		printf("GET ATTRIBUTE 1:\n");
		result = gp_nvm_get_attribute(rvalue+1, &length, &res_array[0]);
		if( result == 0){
			printf("\t(size %u): ", length);
			for( j=0; j<length; j++){
				printf("%u ", res_array[j]);
			}
			printf("\n");
			memset(&res_array, 0, sizeof(res_array));
		} else {
			fprintf(stderr, "\tGET ATTRIBUTE error %u\n", result);
		}

		//try to set attribute
		printf("SET ATTRIBUTE:\n");
		result = gp_nvm_set_attribute(rvalue+1, length_array[rvalue], test_list[rvalue]);
		if( result == 0 ){
			printf("\t(size %u): ", length_array[rvalue]);
			for( j=0; j<length_array[rvalue]; j++ ){
				printf("%u ", ((uint8_t*) test_list[rvalue])[j]);
			}
			printf("\n");
		} else {
			fprintf(stderr, "\tSET ATTRIBUTE error %u\n", result);
		}

		//try to get attribute again
		printf("GET ATTRIBUTE 2:\n");
		result = gp_nvm_get_attribute(rvalue+1, &length, &res_array[0]);
		if( result == 0 ){
			printf("\t(size %u): ", length);
			for( j=0; j<length; j++ ){
				printf("%u ", res_array[j]);
			}
			printf("\n");
			memset(&res_array, 0, sizeof(res_array));
		} else {
			fprintf(stderr, "\tGET ATTRIBUTE error %u\n", result);
		}
	}
	return 0;
}


/** @} */
/** @} */