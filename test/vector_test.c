#include <animlib.h>
#include <stdio.h>

vector blocks;

void print_blocks() {
    for(int i = 0; i < blocks.size; i++) {
        block b = *(block *)blocks.arr[i];
        printf("addr: %p, val: %d, offset: %f size: %d\n", &b, b.val, b.offset, blocks.size);
        printf("----------------------------------------------------\n");
    }
}

void init_blocks() {
    for(int i = 0; i < 5; i++) {
        block b = {.val = i, .offset = 0.0f}; 
        vector_add(&blocks, &b);
        print_blocks();
    }
}

int main(void) {
    blocks = init_vector(5);

    init_blocks();
}
