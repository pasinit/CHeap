/* 
 * File:   heap.h
 * Author: orion
 *
 * Created on 6 agosto 2014, 18.45
 */

#ifndef HEAP_H
#define	HEAP_H
#include<stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif


#define _GET_PARENT_INDEX(child) (child >> 1)//divisione per due e parte intera 
#define _GET_RIGHT_CHILD_INDEX(parent)((parent << 1) + 1) // left shift 1 = per 2
#define _GET_LEFT_CHILD_INDEX(parent)(parent << 1) // left shift 1 = per 2

    typedef struct item {
        size_t run;
        void* value;
    } *Item;

    typedef struct heap {
            Item* data; //array di item
            int size; //dimensione dell'heap
            int mem; //memoria allocata per l'heap
            int first; //indice del primo elemento dell'heap (tipicamente 1).
            Item(*get_min)(struct heap* h); //funzione che restituisce il minimo (O ( log(size)))
            void (*add)(struct heap* h, Item c); //funzione che aggiunge un item all'heap(O(log(size)))
            int (*compare)(const Item a, const Item b); //funzione che confronta due elementi
            void (*print_heap)(struct heap* h); //funzione che stampa a video l'heap
    } *Heap;


    Heap init_heap();
    Item init_item(size_t q, void* v);



#ifdef	__cplusplus
}
#endif

#endif	/* HEAP_H */

