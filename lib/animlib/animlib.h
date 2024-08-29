#ifndef STDLIBS_H
#define STDLIBS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#endif

#ifndef MY_ALLOC
#define MY_ALLOC malloc
#endif

#ifndef MY_FREE
#define MY_FREE free
#endif

#ifndef MY_REALLOC
#define MY_REALLOC realloc
#endif

#define len(A) (int)(sizeof((A)) / sizeof((A)[0]))

typedef struct block {
    int val;
    float offset;
} block;

typedef struct process {
    int lefti;
    int righti;
    bool done;
} process;

typedef struct vector {
    void** arr;
    int size;
    int capacity;
} vector;

// USER RESPONSIBLE FOR FREEING using free_vector
vector init_vector(int capacity);
void free_vector(vector* vect); 
void vector_add(vector* vect, void *element);
void* vector_pop(vector* vect);
