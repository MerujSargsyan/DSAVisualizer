#include <raylib.h>

#define len(A) (int)(sizeof((A)) / sizeof((A)[0]))

const int WIDTH = 100; 
const int BASE_HEIGHT = 50; 
int values[] = {1, 8, 4, 6, 5};

const Vector2 STARTING_PT = {.x = 0, .y = 500};

void draw(Color c) {
    int curr_x = STARTING_PT.x;
    for(int i = 0; i < len(values); i++) {
        int height = values[i] * BASE_HEIGHT;
        DrawRectangle(curr_x, STARTING_PT.y - height, WIDTH, height, c);
        curr_x += WIDTH;
    }
}

int main(void) {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(500, 500, "DSAV");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw(BLUE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
