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

void add_block(int val) {
    block* b = MY_ALLOC(sizeof(block)); 
    b->val = val;
    b->offset= 0.0f;
    vector_add(&blocks, b);
    print_blocks();
}

void init_blocks() {
    add_block(1);
    add_block(2);
    add_block(3);
    add_block(4);
    add_block(5);
}

void swap_blocks() {
    vector_swap(&blocks, 2, 3);
    print_blocks();
}

int main(void) {
    blocks = init_vector(5);

    init_blocks();
    swap_blocks();

}
