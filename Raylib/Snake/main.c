#include "raylib.h"
#include "src/game.h"
#include <stdlib.h>

int main()
{
   // Initialisation gestion mémoire
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Projet 1 : SNAKE  v1.0 05/2024");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
   
    Load();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      Update();
      Draw();
    }

    UnLoad();

    CloseWindow();                  // Close window and OpenGL context

    
    
    return EXIT_SUCCESS;
}
