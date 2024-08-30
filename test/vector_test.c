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
    block* b1 = (block *)blocks.arr[0];
    block* b2 = (block *)blocks.arr[1];
    print_blocks();

    block* temp = MY_ALLOC(sizeof(block));
    temp->val = b1->val;
    temp->offset= b1->offset;

    MY_FREE(b1); // need to write a swap function
    blocks.arr[0] = b2;
    blocks.arr[1] = temp;
    print_blocks();
}

int main(void) {
    blocks = init_vector(5);

    init_blocks();
    swap_blocks();

}
