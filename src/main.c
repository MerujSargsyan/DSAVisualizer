#include <raylib.h>
#include <animlib.h>
#include <stdio.h>

#define DESIRED_COUNT 10 

bool sorted = false;

/*
 * defined as:
 *  int val, offset;
 */
vector blocks;

/*
 * defined as:
 *  int lefti, righti
 *  bool done
 */
vector processes;

int* nums;

const int WIDTH = 50; 
const int BASE_HEIGHT = 50; 
const float BASE_SPEED = 2.0f; // for animation

Vector2 STARTING_PT = {.x = 0, .y = 0};

int max_num() {
    int max = 0x80000000;
    for(int i = 0; i < DESIRED_COUNT; i++) {
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
        if(b.offset != 0) {
            DrawRectangle(curr_x + b.offset, STARTING_PT.y - height, WIDTH, height, RED);
        } else {
            DrawRectangle(curr_x + b.offset, STARTING_PT.y - height, WIDTH, height, c);
        }
        curr_x += WIDTH;
    }
}

// moves blocks i1 and i2 by a certain factor every frame
// locks updates their values and positions after finishing
bool animate(int i1, int i2) {
    int right = i1 > i2 ? i1 : i2;
    int left = i1 > i2 ? i2 : i1;
    block* b1 = (block *)blocks.arr[left];
    block* b2 = (block *)blocks.arr[right];
    int scale = right-left;
    if(b1->offset != WIDTH * scale) {
        b1->offset += BASE_SPEED * scale;
        b2->offset -= BASE_SPEED * scale;     
        return false;
    } else {
        b1->offset = 0.0f;
        b2->offset = 0.0f;
        vector_swap(&blocks, left, right);
        return true;
    }
}

void init_blocks() {
    for(int i = 0; i < DESIRED_COUNT; i++) {
        block* b = MY_ALLOC(sizeof(block));
        b->val = nums[i];
        b->offset = 0.0f;
        vector_add(&blocks, b);
    }
}

void swap(int i1, int i2) {
    int temp = nums[i1];
    nums[i1] = nums[i2];
    nums[i2] = temp;
}

// when swapping a, b in array, call this to add it to process que 
void add_process(int left, int right) {
    // write custom processes here
    process* p = MY_ALLOC(sizeof(process));
    p->lefti = left;
    p->righti = right;
    p->done = false;
    vector_add(&processes, p);
}

// animates the process at the top of the list
void do_processes() {
    if(processes.size == 0) return;

    process current = *(process *)processes.arr[0];
    if(!current.done) {
        current.done = animate(current.lefti, current.righti);
    }

    if(current.done) {
        vector_pop(&processes);
    }
}

// TODO: extract sorting to different file 
void selection_sort() {
    int sorted_len = 0;
    while(sorted_len != DESIRED_COUNT) {
        int min = 0x7FFFFFFF;
        int min_idx = 0;
        for(int i = sorted_len; i < DESIRED_COUNT; i++) {
            if(nums[i] < min) {
                min = nums[i];
                min_idx = i;
            }
        }
        add_process(sorted_len, min_idx);
        swap(sorted_len, min_idx);

        sorted_len++;
    }
}

void bubble_sort() {
    int sorted_len = 0;
    while(sorted_len != DESIRED_COUNT) {
        for(int i = 0; i < DESIRED_COUNT - sorted_len - 1; i++) {
            if(nums[i] > nums[i+1]) {
                add_process(i+1, i);
                swap(i, i+1);
            }
        }
        sorted_len++;
    }
}

void insertion_sort() {
    for(int i = 1; i < DESIRED_COUNT; i++) {
        int element = nums[i];
        int j = i - 1;
        while(j >= 0 && nums[j] > element) {
            add_process(j, j+1);
            swap(j , j+1);
            j--;
        }
    }
}

int main(void) {
    SetTargetFPS(30);
    SetTraceLogLevel(LOG_WARNING);

    blocks = init_vector(5);
    processes = init_vector(5);

    nums = MY_CALLOC(DESIRED_COUNT, sizeof(int));
    generate_nums(nums, DESIRED_COUNT, 10, false);
    
    init_blocks();
    bubble_sort();

    STARTING_PT.y = 10*BASE_HEIGHT;
    InitWindow(WIDTH * DESIRED_COUNT, STARTING_PT.y, "DSAV");

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        do_processes();
        draw(BLUE);
        EndDrawing();
    }

    CloseWindow();
    MY_FREE(nums);
    free_vector(&blocks);
    free_vector(&processes);
    return 0;
}
