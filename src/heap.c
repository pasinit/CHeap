#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "heap.h"



static void swap(Item* data, int i, int j)
{
    Item old = data[i];
    data[i] = data[j];
    data[j] = old;
}


Heap clean(Heap h)
{
    int i;
    for(i = 0; i < h->size; i++)
        free(h->data[i]);
    free(h->data);
    return init_heap();
}

static void iterative_heapify(Item* data, int(*compare)(const Item a, const Item b), int size, int i)
{
    while (i <= size)
    {
        int left = _GET_LEFT_CHILD_INDEX(i);
        int right = _GET_RIGHT_CHILD_INDEX(i);
        int min = 1;
        if (left <= size && compare(data[left], data[i]) < 0)
            min = left;
        else
            min = i;
        if (right <= size && compare(data[right], data[min]) < 0)
            min = right;
        if (min == i)
            break;
        else
        {
            swap(data, i, min);
            i = min;
        }
    }
}

Item get_min(Heap h)
{
    Item c = h->data[h->first];
    h->data[h->first] = h->data[h->size];
    h->size--;
    iterative_heapify(h->data, h->compare, h->size, 1);
    return c;
}

static void increase_key(Item* data, int index, Item value, int(*compare)(const Item, const Item))
{
    int parent = _GET_PARENT_INDEX(index);
    while (index > 1 && compare(data[parent], data[index]) > 0)
    {
        swap(data, index, parent);
        index = parent;
        parent = _GET_PARENT_INDEX(index); 
    }
}

//O(log n)
void add(const Heap h, Item c)
{
    Item* data = h->data;
    if (h->size == h->mem - 1)
    {
        h->mem = h->mem + ((h->mem) / 2) + 1;
        data = realloc(data, h->mem * sizeof (size_t));

    }
    h->size++;
    data[h->size] = c;
    increase_key(data, h->size, c, h->compare);
    h->data = data;
}

typedef unsigned long ItemType;

int compare(Item a, Item b)
{
    return *(ItemType*)a->value - *(ItemType*)b->value;

}

static Item* clone(Item* array, int size)
{
    int i;
    Item* clone = malloc(size * sizeof (struct item));
    for (i = 0; i < size; i++)
    {
        clone[i] = array[i];
    }
    return clone;
}

static void copy(Item* dst, Item* src, int start, int size)
{
    int i;
    for (i = 0; i < start; i++)
        dst[i] = NULL;
    for (i = start; i <= size; i++)
    {
        dst[i] = src[i - start];
    }
}

//O(size*log(size))
static Item* build_heap(Item* data, int size, int(*compare)(Item a, Item b))
{
    Item* heap = malloc((size + 1) * sizeof (struct item)); //heap index start from 1 to size included
    if (heap == NULL) return NULL;
    copy(heap, data, 1, size);
    int i;
    for (i = (size + 1) / 2; i >= 1; i--)
    {
        iterative_heapify(heap, compare, size, i);
    }

    return heap;
}

Heap initialize(Item* data, int size, int(*compare)(Item a, Item b))
{
    Item* store = build_heap(data, size, compare);
    int i = 0;
    if (store == NULL)return NULL;
    //init and set 0 the memory of the heap
    Heap h = malloc(sizeof(struct heap));
    h->data = store;
    h->compare = compare;
    h->get_min = get_min;
    h->add = add;
    h->size = size;
    h->mem = size + 1;
    h->first = 1;
    return h;
}

Heap init_heap()
{
    Item* data = malloc(sizeof(struct item));
    return initialize(data, 0, compare);
}

Item init_item(size_t q, void* v)
{
    Item i = malloc(sizeof(struct item));
    i->run = q;
    i->value = v;
    return i;
}




