/*
 * Heap.c
 *
 *  Created on: Sep 22, 2014
 *      Author: Christopher McGrath
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "Heap.h"
#include "ArrayInteger.h"

Heap* H_init(int type, size_t size){
	Heap* newHeap = malloc(sizeof(Heap));
	if (!newHeap){
		printf("Error: H_init: unable to allocate memory.\n");
		fflush(stdout);
		return NULL;
	}
	newHeap->size = 0;
	newHeap->capacity = size;
	newHeap->array = malloc(sizeof(int) * newHeap->capacity);
	newHeap->type = type;
	return newHeap;
}

void H_destroy(Heap* heap){
	if (heap != NULL){
		free(heap->array);
		free(heap);
	}
}

bool H_isEmpty(Heap* heap){
	if (heap == NULL){
		printf("Error: H_isEmpty: heap points to NULL.\n");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	return heap->size == 0;
}

void H_heapify(Heap* heap, int index){
	if (heap == NULL){
		printf("Error: H_heapify: heap points to NULL.\n");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	int leftIndex = 2 * index + 1;
	int rightIndex = 2 * index + 2;
	if (leftIndex >= heap->size){
		return;
	}
	if (rightIndex >= heap->size){
		int temp = heap->array[index];
		switch (heap->type){
		case MAX:
			if (temp < heap->array[leftIndex]){
				heap->array[index] = heap->array[leftIndex];
				heap->array[leftIndex] = temp;
				H_heapify(heap, leftIndex);
			}
			break;
		case MIN:
			if (temp > heap->array[leftIndex]){
				heap->array[index] = heap->array[leftIndex];
				heap->array[leftIndex] = temp;
				H_heapify(heap, leftIndex);
			}
			break;
		}
	} else {
		int temp = heap->array[index];
		switch (heap->type){
		case MAX:
			if (heap->array[leftIndex] > heap->array[rightIndex]){
				if (temp < heap->array[leftIndex]){
					heap->array[index] = heap->array[leftIndex];
					heap->array[leftIndex] = temp;
					H_heapify(heap, leftIndex);
				}
			} else if (temp < heap->array[rightIndex]){
				heap->array[index] = heap->array[rightIndex];
				heap->array[rightIndex] = temp;
				H_heapify(heap, rightIndex);
			}
			break;
		case MIN:
			if (heap->array[leftIndex] < heap->array[rightIndex]){
				if (temp > heap->array[leftIndex]){
					heap->array[index] = heap->array[leftIndex];
					heap->array[leftIndex] = temp;
					H_heapify(heap, leftIndex);
				}
			} else if (temp > heap->array[rightIndex]){
				heap->array[index] = heap->array[rightIndex];
				heap->array[rightIndex] = temp;
				H_heapify(heap, rightIndex);
			}
			break;
		}
	}
}

// Reallocates the Heap with twice its current capacity and returns it.
Heap* H_doubleCapacity(Heap* heap){
	if (heap == NULL){
		printf("Error: H_doubleCapacity: heap points to NULL.\n");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	Heap* newHeap = H_init(heap->type, heap->capacity * 2);
	if (!newHeap){
		return NULL;
	}
	newHeap->size = heap->size;
	int i;
	for (i = 0; i < heap->size; i += 1){
		newHeap->array[i] = heap->array[i];
	}
	H_destroy(heap);
	return newHeap;
}


Heap* H_buildHeap(int type, int* array, int size){
	Heap* heap = H_init(type, DEFAULT_SIZE);
	if (heap == NULL){
		printf("Error: H_buildHeap: heap points to NULL.\n");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	int doubler = size >> 8;
	while (doubler > 0){
		heap = H_doubleCapacity(heap);
		if (!heap){
			return NULL;
		}
		doubler = doubler >> 1;
	}
	heap->size = size;
	int i;
	for (i = 0; i < size; i += 1){
		heap->array[i] = array[i];
	}

	for (i = size / 2 - 1; i >= 0; i -= 1){
		H_heapify(heap, i);
	}
	return heap;
}

bool H_insert(Heap* heap, int n){
	if (heap == NULL){
		printf("Error: H_insert: heap points to NULL.");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	if (heap->capacity == heap->size){
		heap = H_doubleCapacity(heap);
		if (!heap){
			printf("Error: H_insert: error doubling heap capacity.");
			fflush(stdout);
			exit(EXIT_FAILURE);
		}
	}
	heap->array[heap->size] = n;
	heap->size += 1;
	int i;
	for (i = heap->size / 2 - 1; i >= 0; i -= 1){
		H_heapify(heap, i);
	}
	return true;
}

int H_peakFirst(Heap* heap){
	if (heap == NULL){
		printf("Error: H_peakFirst: heap points to NULL.");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	if (heap->size > 0){
		return heap->array[0];
	} else {
		return -1;
	}
}

int H_extractFirst(Heap* heap){
	if (heap == NULL){
		printf("Error: H_extractFirst: heap points to NULL.");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	if (heap->size == 0){
		printf("Error: tried to extract from empty heap.");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
	int first = heap->array[0];
	heap->size -= 1;
	if (heap->size > 0){
		heap->array[0] = heap->array[heap->size];
		H_heapify(heap, 0);
	}
	return first;
}


void H_printHeapStats(Heap* heap){
	if (heap == NULL){
		printf("Error: H_printHeapStats: heap points to NULL.\n");
		fflush(stdout);
		return;
	}
	printf("    type = %s\n", (heap->type == MAX ? "max" : "min"));
	printf("    size = %d\n", heap->size);
	printf("    capacity = %d\n", heap->capacity);
}

void H_printHeap(Heap* heap){
	printf("Heap: - - - - - - - - - -\n");
	if (heap == NULL){
		printf("Error: H_printHeap: heap points to NULL.\n");
		fflush(stdout);
	} else {
		H_printHeapStats(heap);
		printf("    array:");
		int i;
		for (i = 0; i < heap->size; i += 1){
			printf(" %d", heap->array[i]);
		}
	}
	printf("\n- - - - - - - - - - - - \n\n");
}
