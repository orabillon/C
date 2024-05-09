#include "raylib.h"


int main()
{
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
   

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();                  // Close window and OpenGL context
    
    return 0;
}
