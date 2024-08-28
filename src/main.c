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
        printf("val: %d, offset: %f\n", values[i].val, values[i].ofst);
        DrawRectangle(curr_x + values[i].ofst, STARTING_PT.y - height, WIDTH, height, c);
        curr_x += WIDTH;
    }
}

void animate(int small, int large) {
    struct block* b1 = values + small;
    struct block* b2 = values + large;
    for(int i = 0; i < 10; i++) {
        b1->ofst += 1.0f;
        b2->ofst -= 1.0f;
        draw(BLUE);
    }

    b1->ofst = 0.0f;
    b2->ofst = 0.0f;

    values[small] = *b2;
    values[large] = *b1;

}

int main(void) {
    SetTargetFPS(10);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(500, 500, "DSAV");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        animate(1, 2);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
