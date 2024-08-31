#include <raylib.h>
#include <animlib.h>
#include <stdio.h>

bool animating = true;

vector blocks;
vector processes;

int nums[] = {10, 2, 1, 5, 3, 6, 8};

const int WIDTH = 100; 
const int BASE_HEIGHT = 50; 
const float BASE_SPEED = 2.0f;

Vector2 STARTING_PT = {.x = 0, .y = 0};

int max_num() {
    int max = 0x80000000;
    for(int i = 0; i < len(nums); i++) {
        if(nums[i] > max) max = nums[i];
    }
    return (max < 1) ? 1: max;
}

void print_blocks() {
    for(int i = 0; i < blocks.size; i++) {
        block* b = (block *)blocks.arr[i];
        printf("addr: %p, val: %d, offset: %f size: %d\n", b, b->val, b->offset, blocks.size);
    }
    printf("----------------------------------------------------\n");
}

void draw(Color c) {
    float curr_x = STARTING_PT.x;
    for(int i = 0; i < blocks.size; i++) {
        block b = *(block *)blocks.arr[i];
        int height = b.val * BASE_HEIGHT;
        DrawRectangle(curr_x + b.offset, STARTING_PT.y - height, WIDTH, height, c);
        curr_x += WIDTH;
    }
}

bool animate(int left, int right) {
    block* b1 = (block *)blocks.arr[left];
    block* b2 = (block *)blocks.arr[right];
    int scale = right-left;
    if(b1->offset != WIDTH * scale) {
        b1->offset += BASE_SPEED * scale;
        b2->offset -= BASE_SPEED * scale;     
        return false;
    } else {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;

        b1->offset = 0.0f;
        b2->offset = 0.0f;
        vector_swap(&blocks, left, right);
        return true;
    }
}

void init_blocks() {
    for(int i = 0; i < len(nums); i++) {
        block* b = MY_ALLOC(sizeof(block));
        b->val = nums[i];
        b->offset = 0.0f;
        vector_add(&blocks, b);
    }
}

void add_processes() {
    // write custom processes here
    process* p2 = MY_ALLOC(sizeof(process));
    p2->lefti = 0;
    p2->righti = 2;
    p2->done = false;
    vector_add(&processes, p2);
}


void do_process() {
    if(processes.size == 0) return;

    process current = *(process *)processes.arr[0];
    if(animating && !current.done) {
        current.done = animate(current.lefti, current.righti);
    }

    if(current.done) {
        vector_pop(&processes);
    }
}

int main(void) {
    SetTargetFPS(30);
    SetTraceLogLevel(LOG_WARNING);

    blocks = init_vector(5);
    processes = init_vector(5);

    init_blocks();
    add_processes();

    STARTING_PT.y = max_num()*BASE_HEIGHT;
    InitWindow(WIDTH * len(nums), STARTING_PT.y, "DSAV");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        do_process();
        draw(BLUE);
        EndDrawing();
    }

    CloseWindow();
    free_vector(&blocks);
    free_vector(&processes);
    return 0;
}
