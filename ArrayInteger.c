/*
 * ArrayInteger.c
 *
 *  Created on: Sep 22, 2014
 *      Author: Christopher McGrath
 */

#include <stdlib.h>
#include <stdio.h>

#include "ArrayInteger.h"

void AI_swap(int* array, int indexA, int indexB){
	int temp = array[indexA];
	array[indexA] = array[indexB];
	array[indexB] = temp;
}

void AI_print(int* array, int size){
	printf("int:");
	int i;
	for (i = 0; i < size; i += 1){
		printf(" %d", array[i]);
	}
	printf("\n");
}
