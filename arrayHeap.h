#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// MaxHeap implementation

int* pushArrayHeap ( int num, int* heap, int* size, int* maxSize )
{
    if (heap == NULL) 
    {
        heap = (int *)malloc(*maxSize * sizeof(int));
        heap[0] = num;
        if (heap == NULL) 
        {
            return NULL;
        }
        *size = 1;
        *maxSize = 10;
        return heap;
    }
    if (*size >= *maxSize) {
        int newMaxSize = (*maxSize) * 2;
        int* newHeap = (int *)malloc(newMaxSize * sizeof(int));
        if (newHeap == NULL) {
            // Error handling for failed memory allocation
            return NULL;
        }
        memcpy(newHeap, heap, (*size) * sizeof(int));
        free(heap);
        heap = newHeap;
        *maxSize = newMaxSize;
    }

    int index = *size;
    heap[index] = num;
    *size = index + 1;
    int parent = (index - 1) / 2;
    
    while ( index > 0 && (heap[index] > heap[parent]) )
    {
        int temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;
        index = parent;
        parent = (index - 1) / 2;
    }
    return heap;
}

int popArrayHeap ( int* heap, int* size )
{
    if (*size == 0) {
        return -1; // Heap is empty
    }
    
    int root = heap[0];
    heap[0] = heap[*size - 1];
    *size = *size - 1;
    
    int index = 0;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    
    while (leftChild < *size) {
        int largest = index;
        
        if (heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        
        if (rightChild < *size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }
        
        if (largest == index) {
            break;
        }
        
        int temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;
        
        index = largest;
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
    }
    
    return root;
}