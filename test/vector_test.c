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
     block* b = MY_ALLOC(sizeof(block)); 
     b->val = 1;
     b->offset= 0.0f;
     vector_add(&blocks, b);
     print_blocks();

     block* b2 = MY_ALLOC(sizeof(block));
     b2->val = 2;
     b2->offset = 0.0f;
     vector_add(&blocks, b2);
     print_blocks();
}

void swap_blocks() {
    print_blocks();

    vector_swap(&blocks, 0, 1);
    print_blocks();
}

int main(void) {
    blocks = init_vector(5);

    init_blocks();
    swap_blocks();

}
