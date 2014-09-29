/*
 * examples.c
 *
 *  Created on: Sep 22, 2014
 *      Author: Christopher McGrath
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "examples.h"
#include "ArrayInteger.h"
#include "Heap.h"

#define INIT_SIZE 10
#define CHANGE_IN_SIZE 10

// Sample program that uses a min heap and a max heap to create
// an integer arrays sorted in increasing order and decreasing
// order respectively. The heap is built from an array holding 10
// random numbers, then 10 more numbers are added to each heap.
int exampleHeap(){
	printf("Example Heap - - - - - - - - - - - - - - \n\n");
	int* startingInts = malloc(sizeof(int) * 10);
	srand(time(NULL));
	int i = 0;

	for (i = 0; i < INIT_SIZE; i += 1){
		startingInts[i] = rand() % 50;
	}

	Heap* minHeap = H_buildHeap(MIN, startingInts, INIT_SIZE);
	Heap* maxHeap = H_buildHeap(MAX, startingInts, INIT_SIZE);

	for (i = 0; i < CHANGE_IN_SIZE; i += 1){
		int n = rand() % 30;
		H_insert(minHeap, n);
		H_insert(maxHeap, n);
	}

	H_printHeap(minHeap);
	H_printHeap(maxHeap);

	int minSize = minHeap->size;
	int* minSort = malloc(sizeof(int) * (minHeap->size));
	int maxSize = maxHeap->size;
	int* maxSort = malloc(sizeof(int) * (maxHeap->size));

	for (i = 0; i < minSize; i += 1){
		minSort[i] = 0;
	}

	for (i = 0; i < maxSize; i += 1){
		maxSort[i] = 0;
	}

	i = 0;
	while (!H_isEmpty(minHeap)){
		minSort[i] = H_extractFirst(minHeap);
		i += 1;
	}

	i = 0;
	while (!H_isEmpty(maxHeap)){
		maxSort[i] = H_extractFirst(maxHeap);
		i += 1;
	}

	printf("Increasing order sort:\n");
	AI_print(minSort, minSize);
	printf("\nDecreasing order sort:\n");
	AI_print(maxSort, maxSize);
	printf("\nEnd Example Heap - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
	return EXIT_SUCCESS;
}
