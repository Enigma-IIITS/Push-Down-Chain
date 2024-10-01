Run this to see benchmarks : 

    `g++ benchmark.cpp heap.c utility.c arrayHeap.h -o a.out && ./a.out`

### Pre-requisites : 
- Heap
- Linked list
- Memory fragmentation
- DFS 
- BFS

There are two famous heap implementations:
1) Array
2) Linked List (Binary Tree)

## Array implementation 
### Disadvantages :

- You have to use realloc every time you run out of memory.
- If there is not enough memory, the entire array is copied elsewhere instead of simply extending the memory, which causes overhead.
- It is not suitable for environments with memory fragmentation issues.

### Advantages :

- It is much faster than linked list implementations, as finding the last element during deletion and the correct position during insertion is relatively easier, given that we know the length of the array.

## Linked List Implementation:
### Disadvantages : 
#### Insertion:
- You have to find the right place to insert the element to maintain the full binary tree property.
- This involves performing DFS or BFS every single time you want to insert an element, which can be very slow when the tree is too large.
#### Deletion:
- You have to find the last leaf node every time you want to delete to maintain the full binary tree property.
- This also involves performing DFS or BFS each time, which can be very slow when the tree is too large.

### Advantages:
- It allocates memory separately for each node, allowing it to work in fragmented memory scenarios.


## Enigma's implementation : "push down - Chain"
Combines the best of both - Speed and ability to work efficiently in fragmented memory

Uses linked list (binary tree) to take care of fragmented memory scenarios
Uses "push down" instead of "bubble up" like the classic heap implementation (both array and linked list) do.
 - Does not insert the element at the end and then bubble it up, instead inserts the element at the top, and the pushes it down along a specific path which leads to the correct location (Location at which, inserting maintains complete binary tree property)
 - Time taken to find this appropriate path is **always** directly proportional to height of the tree O(log(n)).
 - Uses a different approach to find the last leaf node element during deletion whose time complexity is always (constant) **O(1)**