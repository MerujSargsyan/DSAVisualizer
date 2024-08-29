#include <stdlib.h>

#ifndef MY_ALLOC
#define MY_ALLOC malloc
#endif

#ifndef MY_FREE
#define MY_FREE free
#endif

#define len(A) (int)(sizeof((A)) / sizeof((A)[0]))

typedef struct block {
    int val;
    float offset;
} block;

typedef struct {
    process* arr;
    int size;
    int capacity;
} vector;

// USER RESPONSIBLE FOR FREEING using free_vector
vector* init_vector(int capacity) {
    vector* vect = MY_ALLOC(sizeof(vector));
    
    vect = {0};
    vect->arr = MY_ALLOC(capacity * sizeof(process));
    vect->size = 0;
    vect->capacity = capacity;

    return vect;
}

void free_vector(vector* vect) {
    MY_FREE(vect->arr);
    MY_FREE(vect);
}
