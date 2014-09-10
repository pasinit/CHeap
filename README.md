CHeap
=====

Simple Heap implementation in C

Provides the basic function of an heap (heapify extract-min add-node).
Nodes of heap are designed to be of a new type struct Item* that contains an integer and a 
pointer to void in order to make it general and also have an integer identifier for each data.
The heap is implemented as a vector where index start at 1. For each node i in the array, its children are at
2i and 2i + 1 and its father is at i/2.

The compare function is customizable so you can define your own function to sort elements in the heap.

The memory allocation is dynamic, an empty heap is created at the beginning and while you add nodes the memory 
grows, the following equation has been used to allocate new memory : new_mem = (old_mem + old_mem/2) + 1.

If you find any bug or you think something can be made better just let me know, i'm gonna be happy to improve my knowledge.

For any problem please contact me!!

Acknowledge:
I used this implementation for a univeristy homework where was required to speed up a k-way external merge sort algorithm
adding an heap to choose the mins between runs.
