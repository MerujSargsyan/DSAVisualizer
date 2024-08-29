#include "animlib.h"

int main(void) {
    vector vect;
    int a = 10, b = 20, c = 30;

    init_vector(&vect, 5);
    
    vector_add(&vect, &a);
    vector_add(&vect, &b);
    vector_add(&vect, &c);

    for(int i = 0; i < vect.size; i++) {
        printf("%d, ", *(int *)vect.arr[i]);
    }
    printf("\n");

    free_vector(&vect);
    return 0;
}
