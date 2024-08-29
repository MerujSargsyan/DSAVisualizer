#include "animlib.h"

// USER RESPONSIBLE FOR FREEING using free_vector
void init_vector(vector* vect, int capacity) {
    vect->arr = MY_ALLOC(capacity * sizeof(void *));
    vect->size = 0;
    vect->capacity = capacity;
}

void free_vector(vector* vect) {
    MY_FREE(vect->arr);
}

void vector_add(vector* vect, void *element) {
    // test for resize
    if(vect->size > vect->capacity/2)  {
        vect->capacity *= 2;
        vect->arr = MY_REALLOC(vect->arr, vect->capacity * sizeof(void *)); 
    }

    vect->arr[vect->size] = element;
    vect->size++;
}

void* vector_pop(vector* vect) {
    void* output = vect->arr[0];

    for(int i = 1; i < vect->size; i++) {
        vect->arr[i-1] = vect->arr[i];
    }

    vect->size--;
    return output;
}
