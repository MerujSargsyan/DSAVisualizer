#include <raylib.h>
#include <stdio.h>

#define len(A) (int)(sizeof((A)) / sizeof((A)[0]))

bool animating = true;

struct block {
    int val;
    float ofst;
};

typedef struct process {
    int lefti;
    int righti;
    bool done;
} process;

const int WIDTH = 50; 
const int BASE_HEIGHT = 50; 

struct block values[] = {{.val = 1, .ofst = 0.0f}, {.val = 2, .ofst = 0.0f}, {.val = 5, .ofst = 0.0f}, {.val = 3, .ofst = 0.0f}, {.val = 4, .ofst = 0.0f},{.val = 9, .ofst = 0.0f} };
process order[] = {{.lefti = 1, .righti = 2, .done = false}, {.lefti = 2, .righti = 3, .done = false}, {.lefti = 3, .righti = 4, .done = false}, {.lefti = 0, .righti = 4, .done = false}};
int curr_process = 0;

const Vector2 STARTING_PT = {.x = len(values)*WIDTH/2, .y = 500};

void draw(Color c) {
    float curr_x = STARTING_PT.x;
    for(int i = 0; i < len(values); i++) {
        int height = values[i].val * BASE_HEIGHT;
        DrawRectangle(curr_x + values[i].ofst, STARTING_PT.y - height, WIDTH, height, c);
        curr_x += WIDTH;
    }
}

bool animate(int left, int right) {
    struct block* b1 = values + left;
    struct block* b2 = values + right;
    int scale = right-left;
    if(b1->ofst != WIDTH * scale) {
        b1->ofst += 1.0f * scale;
        b2->ofst -= 1.0f * scale;     
        return false;
    } else {
        int temp = b1->val;
        values[left] = (struct block){b2->val, 0.0f};
        values[right] = (struct block){temp, 0.0f};
        return true;
    }
}

void take_input() {
    if(IsKeyPressed(KEY_SPACE)) {
        animating = !animating;
        if(curr_process >= len(order)) curr_process = 0;
    }
}

void do_process() {
    if(curr_process >= len(order)) return;
    process current = order[curr_process];
    if(animating && !current.done) {
        current.done = animate(current.lefti, current.righti);
    }

    if(current.done) {
        curr_process++;
    }
}

int main(void) {
    SetTargetFPS(30);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(500, 500, "DSAV");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        take_input();
        do_process();
        draw(BLUE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
