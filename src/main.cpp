#include "raylib.h"

int main() {
    // Virtual resolution (fixed resolution for the game)
    const int virtualWidth = 800;
    const int virtualHeight = 600;

    // Load the character texture
    Texture2D character = LoadTexture("character.png");

    // Initialize the window with resizable flag
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(virtualWidth, virtualHeight, "Viney");

    // Create a RenderTexture2D to handle the texture rendering and scaling
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

    // Main game loop
    while (!WindowShouldClose()) {
        // Get the current window size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the scale factor
        float scaleX = (float)screenWidth / virtualWidth;
        float scaleY = (float)screenHeight / virtualHeight;
        float scale = (scaleX < scaleY) ? scaleX : scaleY; // To maintain the aspect ratio

        // Start drawing to the RenderTexture (virtual resolution)
        BeginTextureMode(target); 
        ClearBackground(RAYWHITE);

        // TODO: Draw your game elements here (scaled to virtual resolution)
        

        // End drawing to the RenderTexture
        EndTextureMode();

        // Begin drawing to the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Scale the RenderTexture to fit the window while maintaining the aspect ratio
        DrawTexturePro(target.texture, 
                       (Rectangle){0, 0, virtualWidth, virtualHeight}, 
                       (Rectangle){0, 0, screenWidth, screenHeight}, 
                       (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    // Unload resources and close the window
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
