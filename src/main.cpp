#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    Texture2D texture;
    float speed;
    float health;
    char PlayerUsername[16];
    bool isRotatedToTheLeft;
    bool isJumping;
    bool isSneaking;
    bool isRunning;
    bool isAttacking;
    bool isWalking;
} Player;

typedef struct Block
{
    Vector2 position;
    Texture2D texture;
    char blockName[35];
    bool isSolid;
    bool isResistantToExplosion;
    bool isBreakable;
    bool isDamaging;
    float damage;
    float durability;
} Block;

int main()
{
    // Virtual resolution (fixed resolution for the game)
    const int virtualWidth = 800;
    const int virtualHeight = 600;

    // Initialize the window with resizable flag
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(virtualWidth, virtualHeight, "Viney");

    // Create a RenderTexture2D to handle the texture rendering and scaling
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

    Font gameFont = LoadFont("assets/fonts/inter.ttf", 20);
    Font 
    Music bgMusic = LoadMusicStream("asssets/audio/bgMusic.mp3");

    // Load the music
    PlayMusicStream(bgMusic);

    // Main game loop
    while (!WindowShouldClose())
    {
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

        // Draw your game elements here (scaled to virtual resolution)
        DrawText(gameFont, "Viney's Universe", 300, 420, 20, BLACK); // Adjusted coordinates

        // End drawing to the RenderTexture
        EndTextureMode();

        // Begin drawing to the screen
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the RenderTexture (virtual resolution) to the screen (screen resolution) so everything is scaled and responsive.
        DrawTexturePro(target.texture,
                       (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height},
                       (Rectangle){(screenWidth - ((float)virtualWidth * scale)) * 0.5f, (screenHeight - ((float)virtualHeight * scale)) * 0.5f,
                                   (float)virtualWidth * scale, (float)virtualHeight * scale},
                       (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    // Unload resources and close the window
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}