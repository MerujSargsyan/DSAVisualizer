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
    vect->arr[vect->size] = element;
    vect->size++;
}
