/*
 * Heap.h
 *
 *  Created on: Sep 22, 2014
 *      Author: Christopher McGrath
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>
#include <stdbool.h>

#define MAX 1
#define MIN 0
#define DEFAULT_SIZE 256

// Defines a Heap data structure.
typedef struct Heap {
	// Current size of heap (# of elements in array)
	size_t size;

	// The total number of int memory locations currently
	// allocated in array
	int capacity;

	// Either MIN or MAX
	int type;

	// The heap: an array of integer keys. Keys can either
	// be sorted by their value, or be hashed to some other
	// value.
	int* array;
} Heap;

// Allocates and returns a new Heap. The capacity specifies the number of
// memory locations to be allocated in the key array. Returns NULL if
// initialization failed.
Heap* H_init(int type, size_t capacity);

// Releases the Heap resources.
void H_destroy(Heap* heap);

// Returns true if the heap is empty. Returns false otherwise.
bool H_isEmpty(Heap* heap);

// Builds the heap from an unsorted array of keys. The size parameter
// specifies the length of the array. Type is to be either MIN or MAX.
// Returns NULL if initialization failed.
Heap* H_buildHeap(int type, int* array, int size);

// Inserts a new value "n" into the heap. Returns true if n was successfully
// added to the heap.
bool H_insert(Heap* heap, int n);

// Returns the value currently at the top of the heap.
int H_peakFirst(Heap* heap);

// Removes and returns the value currently at the top of the heap.
int H_extractFirst(Heap* heap);

// Prints the current statistics of the heap to the screen.
void H_printHeapStats(Heap* heap);

// Prints the contents of the heap along with the statistics of the
// heap to the screen.
void H_printHeap(Heap* heap);

#endif /* HEAP_H_ */
