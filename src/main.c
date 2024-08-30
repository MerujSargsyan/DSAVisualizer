#include <raylib.h>
#include <animlib.h>

bool animating = true;

vector blocks;
vector processes;

int nums[] = {1, 2, 3, 4, 5};

const int WIDTH = 100; 
const int BASE_HEIGHT = 50; 

const Vector2 STARTING_PT = {.x = 0, .y = 500};

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
        b1->offset += 1.0f * scale;
        b2->offset -= 1.0f * scale;     
        return false;
    } else {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;

        //vector_swap(&blocks, left, right); messes up drawing
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
    process* p = MY_ALLOC(sizeof(process));
    p->lefti = 0;
    p->righti= 1;
    p->done = false;
    vector_add(&processes, p);
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

    InitWindow(500, 500, "DSAV");
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
