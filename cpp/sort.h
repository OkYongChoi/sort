#pragma once
#include <cstdlib>
#include <ctime>

template<typename T> void insertionsort(T array[], int size);
template<typename T> void selectionsort(T array[], int size);
template<typename T> void bubblesort(T array[], int size);
template<typename T> void mergesort(T array[], int left, int right);
template<typename T> void merge(T array[], int left, int right);
template<typename T> void mergesort_sequential(T array[], int size);
template<typename T> void quicksort(T array[], int left, int right);
template<typename T> int partition(T array[], int left, int right);
template<typename T> void quicksort_sequential(T array[], int left, int right);
template<typename T> void maxheapify(T array[], int size, int node);
template<typename T> void buildMaxHeap(T array[], int size);
template<typename T> void heapsort(T array[], int size);

template<typename T> void swap(T &, T &);

// Insertion sort
template<typename T>
void insertionsort(T array[], int size) {
	int i, j;
	T key;
	for (j = 1; j < size; ++j) {
		key = array[j];
		i = j - 1;
		while (i >= 0 && key < array[i]) {
			array[i + 1] = array[i];
			--i;
		}
		array[i + 1] = key;
	}
}
// Selection sort
template<typename T>
void selectionsort(T array[], int size) {
	int max;
	T temp;
	for (int i = size - 1; i > 0; --i) {
		max = i;
		for (int j = 0; j < i; ++j) {
			if (array[j] > array[max])
				max = j;
		}
		temp = array[i];
		array[i] = array[max];
		array[max] = temp;
	}
}
// Bubble sort
template<typename T>
void bubblesort(T array[], int size)
{
	T temp;

	for (int i = size - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (array[j] > array[j + 1]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

// Merge sort(Recursive Ver.)
template<typename T>
void mergesort(T array[], int Left, int Right) {
	int Mid;
	if (Left < Right) {
		Mid = (Left + Right) / 2;
		mergesort(array, Left, Mid);
		mergesort(array, Mid + 1, Right);
		merge(array, Left, Right);
	}
}

// Generic Merge Procedure
template<typename T>
void merge(T array[], int left, int right) {
	int num = right - left + 1;

	int i = left;
	int mid = (left + right) / 2;
	int j = mid + 1;
	int cnt = 0;

	T *sortArr = new T[num];

	while (i <= mid && j <= right) 	{
		if (array[i] == array[j]) {
			sortArr[cnt] = array[i];
			sortArr[cnt + 1] = array[j];
			++i; ++j;
			cnt = cnt + 2;
		}
		else if (array[i] < array[j]) {
			sortArr[cnt] = array[i];
			++i;
			++cnt;
		}
		else {
			sortArr[cnt] = array[j];
			++j;
			++cnt;
		}
	}
	while (j <= right) {
		sortArr[cnt] = array[j];
		++j;
		++cnt;
	}

	while (i <= mid) {
		sortArr[cnt] = array[i];
		++i;
		++cnt;
	}

	for (cnt = 0; cnt < num; cnt++)	{
		array[left + cnt] = sortArr[cnt];
	}
	delete[] sortArr;
}

// Merge sort(Sequential Ver.)
template<typename T>
void mergesort_sequential(T array[], int size) {
int *sortedArr = new int[size];
    int mid, right;
    int i, j, l;

    for (int k=1; k < size; k *= 2 ) {
        for (int left=0; left+k < size; left += k*2 ) {
            mid = left + k;        
            right = mid + k;
            if (right > size) right = size; 
            l = left; i = left; j = mid; 
            while (i < mid && j < right) { 
                if (array[i] <= array[j]) {         
                    sortedArr[l] = array[i]; 
					++i;
                } 
				else {
                    sortedArr[l] = array[j]; 
					++j;
                }
                ++l;
            }
            while (i < mid) { 
                sortedArr[l]=array[i]; 
                ++i; ++l;
            }
            while (j < right) { 
                sortedArr[l]=array[j]; 
                ++j; ++l;
            }
            for (l=left; l < right; ++l) { 
                array[l] = sortedArr[l]; 
            }
        }
    }
    delete [] sortedArr;
}

// Quick sort (Recursive Ver.)
template<typename T>
void quicksort(T array[], int left, int right) {
	if (right <= left) return;

	int nPartition = partition(array, left, right);
	quicksort(array, left, nPartition - 1);
	quicksort(array, nPartition + 1, right);
}

// Set partition for quick sort
template<typename T>
int partition(T array[], int left, int right) {
	/* //in order to make a randomized quicksort
	srand(time(NULL)); */
	int pivot = left + rand() % (right - left + 1);
	swap(array[pivot], array[right]);

	int smallerPart = left - 1; // stands for the smaller part than the pivot.

	for (int i = left; i < right; ++i) {
		if (array[i] <= array[right]) {
			++smallerPart;
			swap(array[i], array[smallerPart]);
		}

	}
	swap(array[smallerPart + 1], array[right]);

	return smallerPart + 1;
}

//Quick Sort (Sequential Ver.)
template<typename T>
void quicksort_sequential(T array[], int left, int right) {
    // Create an auxiliary stack
    int stack[ right - left + 1 ];

   // initialize top of stack 
   int top = -1; 

   // push initial values of left and right to stack 
   stack[ ++top ] = left; 
   stack[ ++top ] = right; 

   // Keep popping from stack while is not empty 
	while ( top >= 0 ) { 
		// Pop right and left 
		right = stack[ top-- ]; 
		left = stack[ top-- ]; 

		// Set pivot element at its correct position 
		// in sorted array 
		int p = partition( array, left, right); 

		// If there are elements on left side of pivot, 
		// then push left side to stack 
		if ( p-1 > left ) { 
			stack[ ++top ] = left; 
			stack[ ++top ] = p - 1; 
		} 

		// If there are elements on right side of pivot, 
		// then push right side to stack 
		if ( p+1 < right ) { 
			stack[ ++top ] = p + 1; 
			stack[ ++top ] = right; 
		}
	} 
}

// A function to create the Max Heap at the specified i-th node.
template<typename T>
void maxheapify(T array[], int size, int node) { //i is the subtree of the root
	int largest = node;
	int l = 2 * node + 1;
	int r = 2 * node + 2;

	// If left child is larger than root
	if (l < size && array[l] > array[largest])
		largest = l;

	// If right child is larger than largest so far
	if (r < size && array[r] > array[largest])
		largest = r;

	// If largest is not root
	if (largest != node){
		swap(array[node], array[largest]);

		// Recursively heapify the affected sub-tree
		maxheapify(array, size, largest);
	}
}

// A function that converts an Array to Max Heap.
template<typename T>
void buildMaxHeap(T array[], int size) {
	for (int i = size / 2 - 1; i >= 0; --i)
		maxheapify(array, size, i);
}

// Heap sort
template<typename T>
void heapsort(T array[], int size) {
	buildMaxHeap(array, size);

	// One by one extract an T from heap
	for (int i = size - 1; i >= 0; --i)
	{
		// Swaps first and last node
		swap(array[0], array[i]);

		// creates max heap on the reduced array
		maxheapify(array, i, 0);
	}
}

template<typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}