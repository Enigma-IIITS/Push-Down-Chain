#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include "utility.h"
bRootNode* Arr2Heap(int *arr, int size, bool minHeap);
bRootNode* pushHeap( bRootNode *root, int num, bool maxHeap );
popHeapResult popHeap(bRootNode* root, bool maxHeap);
bool HeapIsValid(bNode *root, bool maxHeap);

#endif