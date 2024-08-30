#include <animlib.h>
#include <stdio.h>

vector blocks;

void print_blocks() {
    for(int i = 0; i < blocks.size; i++) {
        block* b = (block *)blocks.arr[i];
        printf("addr: %p, val: %d, offset: %f size: %d\n", b, b->val, b->offset, blocks.size);
    }
    printf("----------------------------------------------------\n");
}

void init_blocks() {
     block b = {.val = 0, .offset = 0.0f}; 
     vector_add(&blocks, &b);
     print_blocks();

     block b2 = {.val = 1, .offset = 0.0f};
     vector_add(&blocks, &b2);
     print_blocks();

     b = (block){2, 0.0f}; // cannot add using single variable in a loop
     vector_add(&blocks, &b);
     print_blocks();
}

int main(void) {
    blocks = init_vector(5);

    init_blocks();

}
