#include <raylib.h>
#include <stdio.h>

#define len(A) (int)(sizeof((A)) / sizeof((A)[0]))

struct block {
    int val;
    float ofst;
};

const int WIDTH = 100; 
const int BASE_HEIGHT = 50; 
struct block values[] = {{.val = 1, .ofst = 0.0f}, {.val = 2, .ofst = 0.0f}, {.val = 5, .ofst = 0.0f}, {.val = 3, .ofst = 0.0f}, {.val = 4, .ofst = 0.0f}};

const Vector2 STARTING_PT = {.x = 0, .y = 500};

void draw(Color c) {
    float curr_x = STARTING_PT.x;
    for(int i = 0; i < len(values); i++) {
        int height = values[i].val * BASE_HEIGHT;
        DrawRectangle(curr_x + values[i].ofst, STARTING_PT.y - height, WIDTH, height, c);
        curr_x += WIDTH;
    }
}

void animate(int left, int right) {
    struct block* b1 = values + left;
    struct block* b2 = values + right;
    int scale = right-left;
    if(b1->ofst != WIDTH * scale) {
        b1->ofst += 1.0f * scale;
        b2->ofst -= 1.0f * scale;     
    } else {
        int temp = b1->val;
        values[left] = (struct block){b2->val, 0.0f};
        values[right] = (struct block){temp, 0.0f};
    }
    draw(BLUE);
}

int main(void) {
    SetTargetFPS(30);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(500, 500, "DSAV");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        animate(1, 4);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
